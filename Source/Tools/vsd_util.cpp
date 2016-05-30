//#include "trace.h"
#include "vsd_util.h"
#include "rt_core.h"
#include <algorithm>

//#define NUMERIC_LIMITS

#define ws_char(c) ((c)==' '||(c)=='\t'||(c)=='\n'||(c)=='\r')

namespace vis
{
	namespace
	{
		static const double e10[] = { // 1e-0...1e308: 309 * 8 bytes = 2472 bytes
			  1e+0,   1e+1,   1e+2,  1e+3,   1e+4,   1e+5,   1e+6,   1e+7,   1e+8,   1e+9,
			 1e+10,  1e+11,  1e+12,	1e+13,	1e+14,	1e+15,	1e+16,	1e+17,	1e+18,	1e+19,
			 1e+20,  1e+21,  1e+22,	1e+23,	1e+24,	1e+25,	1e+26,	1e+27,	1e+28,	1e+29,
			 1e+30,  1e+31,  1e+32,	1e+33,	1e+34,	1e+35,	1e+36,	1e+37,	1e+38,	1e+39,
			 1e+40,  1e+41,  1e+42,	1e+43,	1e+44,	1e+45,	1e+46,	1e+47,	1e+48,	1e+49,
			 1e+50,  1e+51,  1e+52,	1e+53,	1e+54,	1e+55,	1e+56,	1e+57,	1e+58,	1e+59,
			 1e+60,  1e+61,  1e+62,	1e+63,	1e+64,	1e+65,	1e+66,	1e+67,	1e+68,	1e+69,
			 1e+70,  1e+71,  1e+72,	1e+73,	1e+74,	1e+75,	1e+76,	1e+77,	1e+78,	1e+79,
			 1e+80,  1e+81,  1e+82,	1e+83,	1e+84,	1e+85,	1e+86,	1e+87,	1e+88,	1e+89,
			 1e+90,  1e+91,  1e+92,	1e+93,	1e+94,	1e+95,	1e+96,	1e+97,	1e+98,	1e+99,
			1e+100, 1e+101, 1e+102, 1e+103, 1e+104, 1e+105, 1e+106, 1e+107, 1e+108, 1e+109,
			1e+110, 1e+111, 1e+112, 1e+113, 1e+114, 1e+115, 1e+116, 1e+117, 1e+118, 1e+119,
			1e+120, 1e+121, 1e+122, 1e+123, 1e+124, 1e+125, 1e+126, 1e+127, 1e+128, 1e+129,
			1e+130, 1e+131, 1e+132, 1e+133, 1e+134, 1e+135, 1e+136, 1e+137, 1e+138, 1e+139,
			1e+140,	1e+141, 1e+142, 1e+143, 1e+144, 1e+145, 1e+146, 1e+147, 1e+148, 1e+149,
			1e+150, 1e+151, 1e+152, 1e+153, 1e+154, 1e+155, 1e+156, 1e+157, 1e+158, 1e+159,
			1e+160,	1e+161, 1e+162, 1e+163, 1e+164, 1e+165, 1e+166, 1e+167, 1e+168, 1e+169,
			1e+170, 1e+171, 1e+172, 1e+173, 1e+174, 1e+175, 1e+176, 1e+177, 1e+178, 1e+179,
			1e+180,	1e+181, 1e+182, 1e+183, 1e+184, 1e+185, 1e+186, 1e+187, 1e+188, 1e+189,
			1e+190, 1e+191, 1e+192, 1e+193, 1e+194, 1e+195, 1e+196, 1e+197, 1e+198, 1e+199,
			1e+200,	1e+201, 1e+202, 1e+203, 1e+204, 1e+205, 1e+206, 1e+207, 1e+208, 1e+209,
			1e+210, 1e+211, 1e+212, 1e+213, 1e+214, 1e+215, 1e+216, 1e+217, 1e+218, 1e+219,
			1e+220,	1e+221, 1e+222, 1e+223, 1e+224, 1e+225, 1e+226, 1e+227, 1e+228, 1e+229,
			1e+230, 1e+231, 1e+232, 1e+233, 1e+234, 1e+235, 1e+236, 1e+237, 1e+238, 1e+239,
			1e+240,	1e+241, 1e+242, 1e+243, 1e+244, 1e+245, 1e+246, 1e+247, 1e+248, 1e+249,
			1e+250, 1e+251, 1e+252, 1e+253, 1e+254, 1e+255, 1e+256, 1e+257, 1e+258, 1e+259,
			1e+260,	1e+261, 1e+262, 1e+263, 1e+264, 1e+265, 1e+266, 1e+267, 1e+268, 1e+269,
			1e+270, 1e+271, 1e+272, 1e+273, 1e+274, 1e+275, 1e+276, 1e+277, 1e+278, 1e+279,
			1e+280, 1e+281, 1e+282, 1e+283, 1e+284, 1e+285, 1e+286, 1e+287, 1e+288, 1e+289,
			1e+290, 1e+291, 1e+292, 1e+293, 1e+294, 1e+295, 1e+296, 1e+297, 1e+298, 1e+299,
			1e+300, 1e+301, 1e+302, 1e+303, 1e+304, 1e+305, 1e+306, 1e+307, 1e+308
		};
		
		struct Char_stream
		{
			uint32_t _pos;
			const char *_data;

			inline Char_stream(const char *data = 0) : _pos(0), _data(data) {}
			inline Char_stream(const Char_stream& src) : _pos(src._pos), _data(src._data) {}

			inline bool end() const { return _data[_pos] == 0; }
			inline Char_stream& next() { while (is_ws()) { ++(*this); } return *this; }

			inline operator char() const { return _data[_pos]; }
			inline operator const char*() const { return &_data[_pos]; }

			inline Char_stream& operator++() { ++_pos; return *this; };
			inline Char_stream operator++(int) { Char_stream tmp(*this); ++(*this); return tmp; };

			bool is_ws() const { return ws_char(*this); }
		};

		struct Reader
		{
			Reader(const char* data, VSD_read_handler *handler) : cs(data), handler(handler)
			{
				value_data.reserve(1024 * 16);
			}

			bool convert_int(int32_t& x)
			{
				x = 0;

				bool neg = 0;
				if (cs.next() == '-') {
					neg = 1;
					++cs;
				}

				uint32_t digits = 0;
				while (cs >= '0' && cs <= '9') {
#ifdef NUMERIC_LIMITS
					if (x >= 214748364) { // 2^31 = 2147483648
						if (x != 214748364 || cs > '8') {
							// error, numeric limit
							return false;
						}
					}
#endif
					x = x * 10 + (cs++ - '0');
					++digits;
				}
				if (neg) { x = -x; }
				if (digits > 0) { return true; }

				// error, invalid int
				return false;
			}

			bool convert_uint(uint32_t& x)
			{
				x = 0;

				uint32_t digits = 0;
				while (cs >= '0' && cs <= '9') {
#ifdef NUMERIC_LIMITS
					if (x >= 429496729) { // 2^32 - 1 = 4294967295
						if (x != 429496729 || cs > '5') {
							// error, numeric limit
							return false;
						}
					}
#endif
					x = x * 10 + (cs++ - '0');
					++digits;
				}
				if (digits > 0) { return true; }

				// error, invalid int
				return false;
			}


			bool convert_float(float& x)
			{
				x = 0;

				bool neg = 0;
				if (cs.next() == '-') {
					neg = 1;
					++cs;
				}

				uint32_t digits = 0;
				while (cs >= '0' && cs <= '9') {
#ifdef NUMERIC_LIMITS
					if (x >= 1.7976931348623157e+307) { // double
						// error, numeric limit
						return false;
					}
					if (x >= 3.402823466e+37f) { // float
						// error, numeric limit
						return false;
					}
#endif
					x = (x * 10.0f) + (cs++ - '0');
					++digits;
				}

				int fracexp = 0;
				if (cs == '.') {
					++cs;
					while (cs >= '0' && cs <= '9') {
						if (digits < 9) { // 17 double
							x = (x * 10.0f) + (cs++ - '0');
							--fracexp;
							if (x > 0) { ++digits; }
						}
						else { ++cs; } // ignore or error ?
					}
				}

				int exp = 0;
				if (cs == 'e' || cs == 'E') {
					++cs;

					bool negexp = 0;
					if (cs == '+') { ++cs; }
					else if (cs == '-') {
						negexp = 1;
						++cs;
					}

					while (cs >= '0' && cs <= '9') {
						exp = exp * 10 + (cs++ - '0');
						if (negexp && fracexp - exp < -38) {
							// error, numeric limit
							return false;
						}
						else if (exp > 38 - fracexp) {
							// error, numeric limit
							return false;
						}
						
					}
					if (negexp) { exp = -exp; }
				}

				exp += fracexp;

				if (exp < -38) {
					x /= (float)e10[38];
					x /= (float)e10[-38 - exp];
				}
				else if (exp >= 0) {
					x *= (float)e10[exp];
				}
				else {
					x /= (float)e10[-exp];
				}

				if (neg) { x = -x; }
				if (digits > 0) { return true; }

				// error, invalid float
				return false;
			}


			bool parse()
			{
				while (cs.next() && parse_key() && parse_node());
				return true;
			}

			bool parse_key()
			{
				uint8_t i = 0;
				while (!cs.is_ws() && cs != '=') {
					key_data[i++] = cs++;
				}
				key_data[i] = 0;
				return true;
			}

			bool parse_node()
			{
				if (cs.next() != '=') {
					// error, missing '='
					return false;
				}
				(++cs).next();
				if (cs == '{') {
					++cs;
					return parse_container();
				}
				if (cs == 'f') {
					if ((++cs).next() == '[') {
						++cs;
						return parse_float_array();
					}
					return parse_float();
				}
				if (cs == '\'') {
					++cs;
					return parse_string();
				}
				if (cs == 'i') { ++cs; }
				if ((cs).next() == '[') {
					++cs;
					return parse_int_array();
				}
				return parse_int();
			}

			bool parse_container()
			{
				handler->container_start(key_data);
				while (cs.next()) {
					if (cs == '}') {
						++cs;
						handler->container_end();
						return true;
					}
					if (!(parse_key() && parse_node())) {
						return false;
					}
				}
				// error, missing '}'
				return false;
			}

			bool parse_int()
			{
				cs.next();
				int32_t val;
				if (!convert_int(val)) { return false; }
				handler->value(key_data, VSD_INT, &val, 0);
				return true;
			}

			bool parse_int_array()
			{
				value_data.clear();
				int32_t val;
				while (cs.next()) {
					if (!convert_int(val)) { return false; }
					value_data.insert(value_data.end(), (uint8_t*)(&val), (uint8_t*)(&val) + 4);
					switch (cs.next()) {
						case ',': ++cs; break;
						case ']':
							++cs;
							handler->value(key_data, VSD_INT_ARRAY, &value_data[0], value_data.size());
							return true;
						default: break;
					}
				}
				return false;
			}

			bool parse_float()
			{
				cs.next();
				float val;
				if (!convert_float(val)) { return false; }
				handler->value(key_data, VSD_FLOAT, &val, 0);
				return true;
			}

			bool parse_float_array()
			{
				value_data.clear();
				float val;
				while (cs.next()) {
					if (!convert_float(val)) { return false; }
					value_data.insert(value_data.end(), (uint8_t*)(&val), (uint8_t*)(&val) + 4);
					switch (cs.next()) {
					case ',': ++cs; break;
					case ']':
						++cs;
						handler->value(key_data, VSD_FLOAT_ARRAY, &value_data[0], value_data.size());
						return true;
					default: break;
					}
				}
				return false;
			}

			bool parse_string()
			{
				value_data.clear();
				while (cs) {
					if (cs == '\'') {
						++cs;
						value_data.push_back(0);
						handler->value(key_data, VSD_STRING, &value_data[0], value_data.size() - 1);
						return true;
					}
					if (cs == '\\') {
						switch (++cs) {
						case 'b': value_data.push_back('\b'); break;
						case 'f': value_data.push_back('\f'); break;
						case 't': value_data.push_back('\t'); break;
						case 'n': value_data.push_back('\n'); break;
						case 'r': value_data.push_back('\r'); break;
						case '/': 
						case '\\':
						case '\"': value_data.push_back(cs); break;
						default:
							// error, unknown escape char
							return false;
						}
					}
					else { value_data.push_back(cs); }
					++cs;
				}
				// error, unexpected end
				return false;
			}

			Char_stream cs;
			VSD_read_handler *handler;
			char key_data[32];
			std::vector<uint8_t> value_data;
		};
	}

	

	void read_vsd(const char* data, VSD_read_handler *handler)
	{
		uint32_t n = strlen(data);

		Reader reader(data, handler);
		reader.parse();
	}
	
	void read_binary_container(Memory_stream &ms, uint32_t size, VSD_read_handler *handler)
	{
		for (uint32_t i = 0; i < size; ++i) {
			Node_header n;
			ms.read(&n, 1);
			if (n.type == VSD_CONTAINER) {
				handler->container_start(n.key);
				read_binary_container(ms, n.size, handler);
				handler->container_end();
			}
			else {
				handler->value(n.key, n.type, ms.data(), n.size);
				ms.seek(ms.offset() + n.size);
			}
		}
	}
	
	void read_vsd_binary(void* data, uint32_t size, VSD_read_handler *handler)
	{
		Memory_stream ms(data, size);
		uint32_t cont_size;
		ms.read(&cont_size, 1);
		read_binary_container(ms, cont_size, handler);
	}

	
	
	VSD_writer::VSD_writer(std::vector<char> &buffer, uint8_t style, uint8_t tabsp)
		: _style(style), _tabsp(tabsp), _level(0), _buffer(buffer)
	{}

	void VSD_writer::container_start(const Hash_key& key)
	{
		if (_style == WSTYLE_NICE) {
			write_indent();
			write_key(key);
			write(" = {\n", 5);
		}
		else {
			write_key(key);
			write("={", 2);
		}
		++_level;
	}

	void VSD_writer::container_end()
	{
		--_level;
		if (_style == WSTYLE_NICE) {
			write_indent();
			write("}\n", 2);
		}
		else {
			write("}", 1);
		}
	}

	void VSD_writer::value(const Hash_key& key, uint8_t type, const void* data, uint32_t size)
	{
		if (_style == WSTYLE_NICE) {
			write_indent();
			write_key(key);
			write(" = ", 3);
		}
		else {
			write_key(key);
			write("=", 1);
		}
		switch (type)
		{
		case VSD_INT:
			write('i');
			write_int(*((int32_t*)&data));
			if (_style == WSTYLE_NICE) { write('\n'); }
			else { write(' '); }
			break;
		case VSD_FLOAT:
			write('f');
			write_float(*((float*)&data));
			if (_style == WSTYLE_NICE) { write('\n'); }
			else { write(' '); }
			break;
		case VSD_STRING:
			write('\'');
			write((const char*)data, size);
			if (_style == WSTYLE_NICE) { write("\'\n", 2); }
			else { write('\''); }
			break;
		case VSD_INT_ARRAY:
			write('i');
			write('[');
			for (uint32_t i = 0, n = size; i < n; ++i) {
				write_int(((int32_t*)data)[i]);
				if (i < n - 1) {
					if (_style == WSTYLE_NICE) { write(", ", 2); }
					else { write(','); }
				}
			}
			if (_style == WSTYLE_NICE) { write("]\n", 2); }
			else { write(']'); }
			break;
		case VSD_FLOAT_ARRAY:
			write('f');
			write('[');
			for (uint32_t i = 0, n = size; i < n; ++i) {
				write_float(((float*)data)[i]);
				if (i < n - 1) {
					if (_style == WSTYLE_NICE) { write(", ", 2); }
					else { write(','); }
				}
			}
			if (_style == WSTYLE_NICE) { write("]\n", 2); }
			else { write(']'); }
			break;
		}
	}

	void VSD_writer::write_int(int32_t i)
	{
		char tmp[32];
		int n = sprintf(tmp, "%d", i);
		write(tmp, n);
	}

	void VSD_writer::write_key(const Hash_key& key)
	{
#ifndef FINAL
		if ((const char*)(key)[0]) {
			write((const char*)key, strlen((const char*)key));
			return;
		}
#endif
		char tmp[32];
		int n = sprintf(tmp, "%u", (uint32_t)key);
		write(tmp, n);

	}

	void VSD_writer::write_float(float f)
	{
		char tmp[32];
		int n = sprintf(tmp, "%.7g", f);
		write(tmp, n);
	}

	void VSD_writer::write_indent()
	{
		for (uint32_t i = 0, n = _level * _tabsp; i < n; ++i) {
			_buffer.push_back(' ');
		}
	}

	void VSD_writer::write(char c)
	{
		_buffer.push_back(c);
	}

	void VSD_writer::write(const char *str, uint32_t size)
	{
		_buffer.insert(_buffer.end(), str, str + size);
	}
}
