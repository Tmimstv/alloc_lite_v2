#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include "arena.h"


bool arena_init(Arena* a, size_t size){

	size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
	size_t total_size = page_size * size;
	a->base = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if(a->base == MAP_FAILED){
		printf("map failed\n"); //should probably use perror or something for that
		return 0;
	}

	a->offset = 0;
	//need to figure out what capacity/size is
	a->capacity = total_size;
	return 1;
}

void* arena_alloc(Arena* a, size_t size){

	//get aligned version of current offset
	size_t aligned_offset = align_up(a->offset, 16);

	//out of bounds check
	if(aligned_offset + size > a->capacity){
		return NULL;
	}

	//calc pointer to return
	void* ptr = (uint8_t*)a->base + aligned_offset;

	//move offset forward
	a->offset = aligned_offset + size;

	//return ptr 
	return ptr;

}


void arena_reset(Arena* a){
	a->offset = 0;
}

void arena_destroy(Arena *a){
munmap(a->base, a->capacity);
}

size_t align_up(size_t ptr, size_t align){
	size_t aligned_pointer = (ptr +(align -1)& ~(align - 1));
	return aligned_pointer;
}
