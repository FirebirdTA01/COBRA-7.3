#include <malloc.h>
#include <lv2/memory.h>

void *malloc(size_t size)
{
	void *ptr = alloc(size, 0x27);
	uint64_t value = (uint64_t)ptr;
	uint32_t low = (uint32_t)value;

	if ((value == (uint64_t)(int32_t)low || value == low) &&
		(low & 0xFFFF0000) == 0x80010000)
		return NULL;

	return ptr;
}

void free(void *ptr)
{
	dealloc(ptr, 0x27);
}

