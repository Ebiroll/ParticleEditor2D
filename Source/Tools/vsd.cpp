#include "vsd.h"
#include "hash.h"
//#include "trace.h"
#include <string.h>


namespace vis
{
	/*
	const uint32_t& VSD_container::get_int(const char* key, const uint32_t& def) const
	{
		uint32_t i = find_node(hash_32(key, strlen(key)));
		if (i != ~0) {
			const Node& node = node_ref(i);
			return *(uint32_t*)(node.data.buffer);
		}
		return def;
	}

	const uint32_t* VSD_container::get_int_array(const char* key, uint32_t& size) const
	{

	}

	uint32_t VSD_container::find_node(uint32_t key) const
	{
		return ~0;
	}

	const VSD_container::Node& VSD_container::node_ref(uint32_t i) const
	{
		ASSERT(i < _node.data.size);
		return *(const Node*)(_node.data.buffer)[i];
	}
	*/
}
