#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include "arena.h"



int main(){

	Arena my_arena;

	if(arena_init(&my_arena, 7)){
		printf("creation succesful\n");
	}

	return 0;

}
