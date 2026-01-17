#ifndef ALLOC_LITE_H
#define ALLOC_LITE_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include "arena.h"



typedef struct BlockHeader {
	size_t size;
	struct BlockHeader* next;
} BlockHeader;


void al_init(size_t size_in_pages);
void* al_alloc(size_t size);
void al_free(void* ptr);

#endif //ALLOC_LITE_H


