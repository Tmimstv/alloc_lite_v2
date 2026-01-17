#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include "arena.h"
#include "alloc_lite.h"


static Arena global_arena;
static BlockHeader* free_list_head = NULL;



void* al_alloc(size_t size){
//how much memory? header + user size
	size_t total_size = sizeof(BlockHeader) + size;

// check if free_list is not null
//then check if its size is greater than or equals the request
	if(free_list_head && (free_list_head->size >= size)){
		//save to temp ptr 
		BlockHeader* temp_ptr = free_list_head;
		//move flhead to next
		free_list_head = free_list_head->next;

		temp_ptr->next = NULL;
		return (void* )(temp_ptr + 1);
	}



//call arena_alloc

	void* raw_mem = arena_alloc(&global_arena, total_size);
	if(raw_mem == NULL){
		return NULL;
	}
//init header fields(store the size?)
	BlockHeader* header = (BlockHeader*)raw_mem;

//header metadata
	header->size = size;
	header->next = NULL;

//return pointer to memory directly after the header
	return (void*)(header + 1);

}

void al_free(void* ptr){
//check ptr
	if(!ptr) return;

	BlockHeader* header = (BlockHeader*)ptr -1;
	header->next = free_list_head;
	free_list_head = header;
}


void al_init(size_t size_in_pages){
	if(arena_init(&global_arena, size_in_pages)) printf("arena initialized\n");
}
