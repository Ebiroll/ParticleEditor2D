#pragma once

#include "rt_types.h"
#include "hash.h"
#include <assert.h>
#include "allocators.h"

#ifndef ASSERT
#define ASSERT assert
#endif

namespace vis
{
	enum : uint8_t
	{
		VSD_NULL,
		VSD_INT,
		VSD_FLOAT,
		VSD_STRING,
		VSD_INT_ARRAY,
		VSD_FLOAT_ARRAY,
		VSD_CONTAINER = 0xFF,
	};

	template<typename T_allocator>
	struct TVSD_container
	{
    private:
        
        struct Node
        {
            Node* next;
            Hash_key key;
            uint32_t type:8;
            uint32_t size:24;
            void* data;
            
            Node(const Hash_key& key, uint8_t type, const void* data, uint32_t size);
            Node(const Node& src);
            
            ~Node();
            
            void set(uint8_t type, const void* data, uint32_t size);
            
            void internal_set(uint8_t type, const void* data, uint32_t size);
            void internal_assign(const Node& src);
        };
        
        struct Node_map
        {
            Node* head;
            
            Node_map();
            Node_map(const Node_map&);
            
            ~Node_map();
            
            void remove(const Hash_key& key);
            Node* insert(const Hash_key& key, uint8_t type, const void* data, uint32_t size);
            Node* find(const Hash_key& key);
            const Node* find(const Hash_key& key) const;
            
            uint32_t node_count() const;
        };
        
        Node_map _map;
        static T_allocator allocator;
    public:
		struct Value
		{
			void set(int32_t val);
			void set(float val);
			void set(const char* val, uint32_t size);
			void set(const int32_t* val, uint32_t size);
			void set(const float* val, uint32_t size);

			operator int32_t&();
			operator const int32_t&() const;
			operator float&();
			operator const float&() const;
			operator char*();
			operator const char*() const;
			operator int32_t*();
			operator const int32_t*() const;
			operator float*();
			operator const float*() const;

			void* data();
			const void* data() const;

			uint8_t type() const;
			uint32_t size() const;

			Value() = delete;
			~Value() = delete;
		};

		TVSD_container();
		TVSD_container(const TVSD_container&);

		~TVSD_container();

		operator bool() const;

		void set(const Hash_key& key, int32_t val);
		void set(const Hash_key& key, float val);
		void set(const Hash_key& key, const char* val, uint32_t size);
		void set(const Hash_key& key, const int32_t* val, uint32_t * size);
		void set(const Hash_key& key, const float* val, uint32_t size);
		void set(const Hash_key& key, uint8_t type, const void* data, uint32_t size);
		void set(const Hash_key& key, const TVSD_container& con);

		bool value(const Hash_key& key, int32_t &val) const;
		bool value(const Hash_key& key, float &val) const;
		bool value(const Hash_key& key, const char*& val, uint32_t * size = 0) const;
		bool value(const Hash_key& key, const int32_t*& val, uint32_t * size = 0) const;
		bool value(const Hash_key& key, const float*& val, uint32_t * size = 0) const;

		Value& value(const Hash_key& key);
		const Value& value(const Hash_key& key) const;

		TVSD_container& container(const Hash_key& key);
		const TVSD_container& container(const Hash_key& key) const;

		Value& add_value(const Hash_key& key);
		TVSD_container& add_container(const Hash_key& key);

		void clear();
		void remove(const Hash_key& key);

		TVSD_container& operator=(const TVSD_container&);

		struct iter
		{
			iter();
			iter(const iter &src);

			iter& operator=(const iter &src);
			bool operator==(const iter &src) const;
			bool operator!=(const iter &src) const;
			iter& operator++();
			iter operator++(int);
			const Hash_key& key() const;
			uint8_t type() const;
			Value& value();
			TVSD_container& container();

		protected:
		  typedef struct TVSD_container::Node* ptr_type;
			iter(ptr_type node) : node(node) {}
			mutable ptr_type node;
			friend struct TVSD_container<T_allocator>;
		};

		struct const_iter
		{
			const_iter();
			const_iter(const const_iter &src);

			const_iter& operator=(const const_iter &src);
			bool operator==(const const_iter &src) const;
			bool operator!=(const const_iter &src) const;
			const_iter& operator++();
			const_iter operator++(int);
			const Hash_key& key() const;
			uint8_t type() const;
			const Value& value() const;
			const TVSD_container& container() const;

		protected:
		  typedef struct TVSD_container::Node* ptr_type;
			const_iter(ptr_type node) : node(node) {}
			mutable ptr_type node;
			friend struct TVSD_container<T_allocator>;
		};

		iter begin() { return iter(_map.head); }
		iter end() { return iter(0); }

		const_iter begin() const { return const_iter(_map.head); }
		const_iter end() const { return const_iter(0); }

		uint32_t size() const;

	
	};

	template<typename T_allocator>
	T_allocator TVSD_container<T_allocator>::allocator;

	typedef TVSD_container<Crt_allocator> VSD_container_rw;
	typedef TVSD_container<Block_allocator<>> VSD_container;




	////////////////////////////////////////////////////////////////

	template<typename T_allocator>
	TVSD_container<T_allocator>::TVSD_container()
	{
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::TVSD_container(const TVSD_container& src)
		:_map(src._map)
	{
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::~TVSD_container()
	{
	}

	template<typename T_allocator>
	TVSD_container<T_allocator>::operator bool() const
	{
		return _map.head != 0;
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::set(const Hash_key& key, int32_t val)
	{
		_map.insert(key, VSD_INT, (const void*)&val, 0);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::set(const Hash_key& key, float val)
	{
		_map.insert(key, VSD_FLOAT, (const void*)&val, 0);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::set(const Hash_key& key, const char* val, uint32_t size)
	{
		_map.insert(key, VSD_STRING, val, size);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::set(const Hash_key& key, const int32_t* val, uint32_t * size)
	{
		_map.insert(key, VSD_INT_ARRAY, val, size);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::set(const Hash_key& key, const float* val, uint32_t size)
	{
		_map.insert(key, VSD_FLOAT_ARRAY, val, size);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::set(const Hash_key& key, uint8_t type, const void* data, uint32_t size)
	{
		_map.insert(key, type, data, size);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::set(const Hash_key& key, const TVSD_container& con)
	{
		_map.insert(key, 0xFF, &con._map, 0);
	}


	template<typename T_allocator>
	bool TVSD_container<T_allocator>::value(const Hash_key& key, int32_t &val) const
	{
		const Node *node = _map.find(key);
		if (node && node->type == VSD_INT) {
			val = *(int32_t*)(&node->data);
			return true;
		}
		return false;
	}
	

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::value(const Hash_key& key, float &val) const
	{
		const Node *node = _map.find(key);
		if (node && node->type == VSD_FLOAT) {
			val = *(float*)(&node->data);
			return true;
		}
		return false;
	}

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::value(const Hash_key& key, const char*& val, uint32_t * size) const
	{
		const Node *node = _map.find(key);
		if (node && node->type == VSD_STRING) {
			val = (const char*)(node->data);
			if (size) { *size = node->size;  }
			return true;
		}
		return false;
	}

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::value(const Hash_key& key, const int32_t*& val, uint32_t * size) const
	{
		const Node *node = _map.find(key);
		if (node && node->type == VSD_STRING) {
			val = (const int32_t*)(node->data);
			if (size) { *size = node->size / 4; }
			return true;
		}
		return false;
	}

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::value(const Hash_key& key, const float*& val, uint32_t * size) const
	{
		const Node *node = _map.find(key);
		if (node && node->type == VSD_STRING) {
			val = (const float*)(node->data);
			if (size) { *size = node->size / 4; }
			return true;
		}
		return false;
	}
	

	template<typename T_allocator>
	typename TVSD_container<T_allocator>::Value& TVSD_container<T_allocator>::value(const Hash_key& key)
	{
		return const_cast<Value&>(((const TVSD_container<T_allocator>*)this)->value(key));
	}

	template<typename T_allocator>
	const typename TVSD_container<T_allocator>::Value& TVSD_container<T_allocator>::value(const Hash_key& key) const
	{
		const Node* node = _map.find(key);
		if (node && node->type != 0xFF) { return *(Value*)(node); }
		return *(Value*)(0);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>& TVSD_container<T_allocator>::container(const Hash_key& key)
	{
		return const_cast<TVSD_container<T_allocator>&>(((const TVSD_container<T_allocator>*)this)->container(key));
	}


	template<typename T_allocator>
	const TVSD_container<T_allocator>& TVSD_container<T_allocator>::container(const Hash_key& key) const
	{
		const Node* node = _map.find(key);
		if (node && node->type == 0xFF) { return *(TVSD_container<T_allocator>*)(&node->data); }
		return *(TVSD_container<T_allocator>*)(0);
	}


	template<typename T_allocator>
	typename TVSD_container<T_allocator>::Value& TVSD_container<T_allocator>::add_value(const Hash_key& key)
	{
		return *(Value*)(_map.insert(key, VSD_NULL, 0, 0));
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>& TVSD_container<T_allocator>::add_container(const Hash_key& key)
	{
		return *(TVSD_container<T_allocator>*)(&_map.insert(key, 0xFF, 0, 0)->data);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::clear()
	{
		_map.~Map_node();
		_map.head = 0;
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::remove(const Hash_key& key)
	{
		_map.remove(key);
	}

	template<typename T_allocator>
	TVSD_container<T_allocator>& TVSD_container<T_allocator>::operator=(const TVSD_container<T_allocator>& src)
	{
		_map.~Node_map();
		_map.Node_map(src);
	}


	template<typename T_allocator>
	uint32_t TVSD_container<T_allocator>::size() const
	{
		return _map.node_count();
	}

	template<typename T_allocator>
	void TVSD_container<T_allocator>::Value::set(int32_t val)
	{
		((Node*)this)->set(VSD_INT, (const void*)&val, 0);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::Value::set(float val)
	{
		((Node*)this)->set(VSD_FLOAT, (const void*)&val, 0);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::Value::set(const char* val, uint32_t size)
	{
                ASSERT(size <= 0x0FFF);
		((Node*)this)->set(VSD_STRING, val, size);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::Value::set(const int32_t* val, uint32_t size)
	{
                ASSERT(size <= 0x0FFF);
		((Node*)this)->set(VSD_INT_ARRAY, val, size * 4);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::Value::set(const float* val, uint32_t size)
	{
                ASSERT(size <= 0x0FFF);
		((Node*)this)->set(VSD_FLOAT_ARRAY, val, size * 4);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator int32_t&()
	{
                ASSERT(((Node*)this)->type == VSD_INT);
		return *(int32_t*)(&((Node*)this)->data);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator const int32_t&() const
	{
		ASSERT(((Node*)this)->type == VSD_INT);
		return *(int32_t*)(&((Node*)this)->data);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator float&()
	{
		ASSERT(((Node*)this)->type == VSD_FLOAT);
		return *(float*)(&((Node*)this)->data);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator const float&() const
	{
		ASSERT(((Node*)this)->type == VSD_FLOAT);
		return *(float*)(&((Node*)this)->data);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator char*()
	{
		ASSERT(((Node*)this)->type == VSD_STRING);
		return (char*)((Node*)this)->data;
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator const char*() const
	{
		ASSERT(((Node*)this)->type == VSD_STRING);
		return (char*)((Node*)this)->data;
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator int32_t*()
	{
		ASSERT(((Node*)this)->type == VSD_INT_ARRAY);
		return (int32_t*)((Node*)this)->data;
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator const int32_t*() const
	{
		ASSERT(((Node*)this)->type == VSD_INT_ARRAY);
		return (int32_t*)((Node*)this)->data;
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator float*()
	{
		ASSERT(((Node*)this)->type == VSD_FLOAT_ARRAY);
		return (float*)((Node*)this)->data;
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Value::operator const float*() const
	{
		ASSERT(((Node*)this)->type == VSD_FLOAT_ARRAY);
		return (float*)((Node*)this)->data;
	}


	template<typename T_allocator>
	void* TVSD_container<T_allocator>::Value::data()
	{
		return ((Node*)this)->data;
	}


	template<typename T_allocator>
	const void* TVSD_container<T_allocator>::Value::data() const
	{
		return ((Node*)this)->data;
	}


	template<typename T_allocator>
	uint8_t TVSD_container<T_allocator>::Value::type() const
	{
		return ((Node*)this)->type;
	}


	template<typename T_allocator>
	uint32_t TVSD_container<T_allocator>::Value::size() const
	{
		static uint8_t sz[] = { 1, 1, 1, 1, 4, 4 };
		return ((Node*)this)->size / sz[((Node*)this)->type];
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::iter::iter()
	{
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::iter::iter(const iter &src) : node(src.node)
	{
	}

	template<typename T_allocator>
	typename TVSD_container<T_allocator>::iter& TVSD_container<T_allocator>::iter::operator=(const iter &src)
	{
		node = src.node; return *this;
	}

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::iter::operator==(const iter &src) const
	{
		return node == src.node;
	}

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::iter::operator!=(const iter &src) const
	{
		return !(*this == src.node);
	}
	
	template<typename T_allocator>
	typename TVSD_container<T_allocator>::iter& TVSD_container<T_allocator>::iter::operator++()
	{
		node = node->next; return *this;
	}
	
	template<typename T_allocator>
	typename TVSD_container<T_allocator>::iter TVSD_container<T_allocator>::iter::operator++(int)
	{
		iter t(*this); ++(*this); return t;
	}
	
	template<typename T_allocator>
	const Hash_key& TVSD_container<T_allocator>::iter::key() const
	{
		return node->key;
	}
	
	template<typename T_allocator>
	uint8_t TVSD_container<T_allocator>::iter::type() const
	{
		return node->type;
	}
	
	template<typename T_allocator>
	typename TVSD_container<T_allocator>::Value& TVSD_container<T_allocator>::iter::value()
	{
		ASSERT(node->type != VSD_CONTAINER);  return *(Value*)node;
	}
	
	template<typename T_allocator>
	TVSD_container<T_allocator>& TVSD_container<T_allocator>::iter::container()
	{
		ASSERT(node->type == VSD_CONTAINER); return *(TVSD_container*)(&node->data);
	}



	template<typename T_allocator>
	TVSD_container<T_allocator>::const_iter::const_iter()
	{
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::const_iter::const_iter(const const_iter &src) : node(src.node)
	{
	}

	template<typename T_allocator>
	typename TVSD_container<T_allocator>::const_iter& TVSD_container<T_allocator>::const_iter::operator=(const const_iter &src)
	{
		node = src.node; return *this;
	}

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::const_iter::operator==(const const_iter &src) const
	{
		return node == src.node;
	}

	template<typename T_allocator>
	bool TVSD_container<T_allocator>::const_iter::operator!=(const const_iter &src) const
	{
		return !(*this == src.node);
	}

	template<typename T_allocator>
	typename TVSD_container<T_allocator>::const_iter& TVSD_container<T_allocator>::const_iter::operator++()
	{
		node = node->next; return *this;
	}

	template<typename T_allocator>
	typename TVSD_container<T_allocator>::const_iter TVSD_container<T_allocator>::const_iter::operator++(int)
	{
		iter t(*this); ++(*this); return t;
	}

	template<typename T_allocator>
	const Hash_key& TVSD_container<T_allocator>::const_iter::key() const
	{
		return node->key;
	}

	template<typename T_allocator>
	uint8_t TVSD_container<T_allocator>::const_iter::type() const
	{
		return node->type;
	}

	template<typename T_allocator>
	const typename TVSD_container<T_allocator>::Value& TVSD_container<T_allocator>::const_iter::value() const
	{
		ASSERT(node->type != VSD_CONTAINER);  return *(Value*)node;
	}

	template<typename T_allocator>
	const TVSD_container<T_allocator>& TVSD_container<T_allocator>::const_iter::container() const
	{
		ASSERT(node->type == VSD_CONTAINER); return *(TVSD_container*)(&node->data);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Node::Node(const Hash_key& key, uint8_t type, const void* data, uint32_t size)
		: next(0), key(key)
	{
		internal_set(type, data, size);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Node::Node(const Node& src)
		: next(0), key(src.key)
	{
		internal_assign(src);
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Node::~Node()
	{
		if (type == 0xFF) {
			((Node_map*)&data)->~Node_map();
		}
		else if (type == VSD_STRING || type == VSD_INT_ARRAY || type == VSD_FLOAT_ARRAY) {
			allocator.free(data);
		}
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::Node::set(uint8_t type, const void* data, uint32_t size)
	{
		this->~Node();
		internal_set(type, data, size);
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::Node::internal_set(uint8_t type, const void* data, uint32_t size)
	{
		this->type = type;
		this->size = size;

		if (!data) {
			this->data = 0;
			return;
		}

		switch (type) {
		case VSD_INT:
		case VSD_FLOAT:
			memcpy(&this->data, data, 4);
			break;
		case VSD_STRING:
			this->data = allocator.alloc(size + 1);
			memcpy(this->data, data, size);
			((char*)this->data)[size] = 0;
			break;
		case VSD_INT_ARRAY:
		case VSD_FLOAT_ARRAY:
			this->data = allocator.alloc(size);
			memcpy(this->data, data, size);
			break;
		case 0xFF:
			this->size = 0;
			new(&this->data) Node_map(*(Node_map*)(data));
		}
	}

	template<typename T_allocator>
	void TVSD_container<T_allocator>::Node::internal_assign(const Node& src)
	{
		key = src.key;
		type = src.type;
		size = src.size;

		switch (type) {
		case VSD_NULL:
			data = 0;
			break;
		case VSD_INT:
		case VSD_FLOAT:
			memcpy(&data, &src.data, 4);
			break;
		case VSD_STRING:
			data = allocator.alloc(size + 1);
			memcpy(data, src.data, size + 1);
			break;
		case VSD_INT_ARRAY:
		case VSD_FLOAT_ARRAY:
			data = allocator.alloc(size);
			memcpy(data, src.data, size);
			break;
		case 0xFF:
			new(&data) Node_map(*(Node_map*)(&src.data));
			break;
		}
	}

	template<typename T_allocator>
	TVSD_container<T_allocator>::Node_map::Node_map() :head(0)
	{
	}

	template<typename T_allocator>
	TVSD_container<T_allocator>::Node_map::Node_map(const Node_map& src)
	{
		Node* prev = 0;
		Node* src_node = src.head;
		while (src_node) {
			Node *new_node = (Node*)allocator.alloc(sizeof(Node));
			new(new_node) Node(*src_node);
			if (prev) { prev->next = new_node; }
			else { head = new_node; }
			prev = new_node;
			src_node = src_node->next;
		}
	}


	template<typename T_allocator>
	TVSD_container<T_allocator>::Node_map::~Node_map()
	{
		while (head) {
			Node* temp = head;
			head = head->next;
			temp->~Node();
			allocator.free(temp);
		}
	}


	template<typename T_allocator>
	void TVSD_container<T_allocator>::Node_map::remove(const Hash_key& key)
	{
		Node *prev = 0;
		Node* node = head;
		while (node) {
			if (node->key == key) {
				if (prev) {
					prev->next = node->next;
				}
				node->~Node();
				allocator.free(node);
				break;
			}
			prev = node;
			node = node->next;
		}
	}


	template<typename T_allocator>
	typename TVSD_container<T_allocator>::Node* TVSD_container<T_allocator>::Node_map::insert(const Hash_key& key, uint8_t type, const void* data, uint32_t size)
	{
		Node* node = head;
		while (node) {
			if (node->key == key) {
				node->set(type, data, size);
				return node;
			}
			if (node->next == 0) { break; }
			node = node->next;
		}

		Node* new_node = (Node*)allocator.alloc(sizeof(Node));
		new(new_node) Node(key, type, data, size);

		if (node) { node->next = new_node; }
		else { head = new_node; }

		return new_node;
	}

	template<typename T_allocator>
	typename TVSD_container<T_allocator>::Node* TVSD_container<T_allocator>::Node_map::find(const Hash_key& key)
	{
		return const_cast<Node*>(((const Node_map*)this)->find(key));
	}


	template<typename T_allocator>
	const typename TVSD_container<T_allocator>::Node* TVSD_container<T_allocator>::Node_map::find(const Hash_key& key) const
	{
		const Node* node = head;
		while (node) {
			if (node->key == key) { return node; }
			node = node->next;
		}
		return 0;
	}


	template<typename T_allocator>
	uint32_t TVSD_container<T_allocator>::Node_map::node_count() const
	{
		uint32_t count = 0;
		const Node* node = head;
		while (node) {
			++count;
			node = node->next;
		}
		return count;
	}

}
