#pragma once

#include <vector>

#include "vsd.h"
//#include "memory_stream.h"

namespace vis
{
	struct VSD_read_handler
	{
		virtual void container_start(const Hash_key& key) = 0;
		virtual void container_end() = 0;
		virtual void value(const Hash_key& key, uint8_t type, const void* data, uint32_t size) = 0;
	};

	void read_vsd(const char* data, VSD_read_handler *handler);
	void read_vsd_binary(void* data, uint32_t size, VSD_read_handler *handler);

	template<typename T_container>
	void read_vsd_container(const char* data, T_container& container);

	template<typename T_container>
	void read_vsd_binary_container(void* data, uint32_t size, T_container& container);


	enum
	{
		WSTYLE_NICE,
		WSTYLE_COMPACT,
	};

	struct VSD_writer
	{
		VSD_writer(std::vector<char> &buffer, uint8_t style = WSTYLE_NICE, uint8_t tabsp = 4);

		void container_start(const Hash_key& key);
		void container_end();
		void value(const Hash_key& key, uint8_t type, const void* data, uint32_t size);

	private:
		void write_key(const Hash_key& key);
		void write_int(int32_t i);
		void write_float(float f);
		void write_indent();
		void write(char c);
		void write(const char *str, uint32_t size);

		uint32_t _style : 8;
		uint32_t _tabsp : 8;
		uint32_t _level : 16;
		std::vector<char> &_buffer;
	};


	template<typename T_container>
	void dump_vsd_container(std::vector<char>& data, const T_container& container);

	template<typename T_container>
	void dump_vsd_binary_container(std::vector<uint8_t>& data, const T_container& container);

	
	////////////////////////////////////////////////////////////////
	template<typename T_container>
	struct Read_handler : VSD_read_handler
	{
		std::vector<T_container*> stack;
		Read_handler(T_container* root) { stack.reserve(16); stack.push_back(root); }
		void container_start(const Hash_key& key) { stack.push_back(&(stack.back()->add_container(key))); }
		void container_end() { stack.pop_back(); }
		void value(const Hash_key& key, uint8_t type, const void* data, uint32_t size) { stack.back()->set(key, type, data, size); }
	};


	template<typename T_container>
	inline void read_vsd_container(const char* data, T_container& container)
	{
		Read_handler<T_container> handler(&container);
		read_vsd(data, &handler);
	}

	template<typename T_container>
	inline void read_vsd_binary_container(void* data, uint32_t size, T_container& container)
	{
		Read_handler<T_container> handler(&container);
		read_vsd_binary(data, size, &handler);
	}


	template<typename T_container>
	inline void write_vsd_container(VSD_writer& writer, const T_container& container)
	{
		for (auto it = container.begin(); it != container.end(); ++it) {
			if (it.type() == VSD_CONTAINER) {
				writer.container_start(it.key());
				write_vsd_container(writer, it.container());
				writer.container_end();
			}
			else {
				writer.value(it.key(), it.type(), it.value().data(), it.value().size());
			}
		}
	}


	template<typename T_container>
	inline void dump_vsd_container(std::vector<char>& data, const T_container& container)
	{
		VSD_writer writer(data);
		write_vsd_container(writer, container);
		data.push_back(0);
	}

	struct Node_header
	{
		uint32_t key;
		uint32_t type : 8;
		uint32_t size : 24;
	};
	
	template<typename T_container>
	inline void write_binary_container(std::vector<uint8_t>& buffer, const T_container& container)
	{
		for (auto it = container.begin(); it != container.end(); ++it) {
			if (it.type() == VSD_CONTAINER) {
				Node_header n = { it.key(), it.type(), container.size() };
				buffer.insert(buffer.end(), (uint8_t*)&n, (uint8_t*)&n + 8);
				write_binary_container(buffer, it.container());
			}
			else {
				Node_header n = { it.key(), it.type(), it.value().size() };
				buffer.insert(buffer.end(), (uint8_t*)&n, (uint8_t*)&n + 8);
				buffer.insert(buffer.end(), (const uint8_t*)it.value().data(), (const uint8_t*)it.value().data() + n.size);
			}
		}
	}

	template<typename T_container>
	inline void dump_vsd_binary_container(std::vector<uint8_t>& buffer, const T_container& container)
	{
		uint32_t size = container.size();
		buffer.insert(buffer.end(), (uint8_t*)&size, (uint8_t*)&size + 4);
		write_binary_container(buffer, container);
	}
}
