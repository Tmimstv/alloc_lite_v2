#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct {
	void* base;
	size_t capacity;
	size_t offset;
} Arena;


bool arena_init(Arena* a, size_t size);
void* arena_alloc(Arena* a, size_t size);
void arena_reset(Arena* a);
void arena_destroy(Arena* a);
size_t align_up(size_t ptr, size_t align);

#endif //ARENA_H
