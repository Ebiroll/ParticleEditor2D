#pragma once

#include "rt_types.h"
//#include "trace.h"

#include <memory>
#include <stdlib.h>
#include <assert.h>

namespace vis
{
	struct Crt_allocator
	{
        void* alloc(size_t size) { return size ? malloc(size) : 0; }
        void free(void *ptr) { if (ptr) { free(ptr); } }
	};

	template<uint32_t T_block_size = 1024 * 16>
	struct Block_allocator
	{
		Block_allocator() : _blocks(0) {}
		~Block_allocator()
		{
			while (_blocks) {
				Block *next = _blocks->next;
                free(_blocks);
				_blocks = next;
			}
		}

		void* alloc(size_t size)
		{
			if (!size) { return 0; }

			assert(size <= T_block_size - sizeof(Block));
			if (_blocks == 0 || _blocks->offset + size > T_block_size) {
                Block* block = (Block*)malloc(T_block_size);
				block->next = _blocks;
				block->count = 0;
				block->offset = sizeof(Block);
				_blocks = block;
			}
			void *ptr = (uint8_t*)_blocks + _blocks->offset;
			++_blocks->count;
			_blocks->offset += size;
			return ptr;
		}

		void free(void *ptr)
		{
			if (!ptr) { return; }

			Block* prev = 0;
			Block* block = _blocks;
			while (block) {
				uint8_t* mem = (uint8_t*)block + sizeof(Block);
				if (ptr >= mem && ptr < mem + T_block_size) {
					--block->count;
					if (block->count == 0) {
						if (prev) { prev->next = block->next; }
						else { _blocks = block->next; }
                        free(block);
					}
					break;
				}
				prev = block;
				block = block->next;
			}
			
		}

	private:
		struct Block
		{
			Block *next;
			uint16_t count;
			uint16_t offset;
		} *_blocks;
	};
}
