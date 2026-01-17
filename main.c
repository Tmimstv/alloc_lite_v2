#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include "arena.h"
#include "alloc_lite.h"


int main(){
	printf("Hello, World\n");
	al_init(1);

	void* a = al_alloc(64);
	printf("allocated A at: %p\n", a);


	al_free(a);
	printf("Freed A\n");

	void* b = al_alloc(64);
	printf("Allocated B at: %p\n", b);

	if(a == b){
		printf("Success: memory recycled\n");
	} else {
		printf("Failure: B got a new address\n");
	}
	return 0;
}
