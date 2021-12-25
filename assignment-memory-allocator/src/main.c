#include "mem_internals.h"
#include "mem.h"
#include "util.h"

static struct block_header* block_get_header(void* contents) {
    return (struct block_header*) (((uint8_t*)contents)-offsetof(struct block_header, contents));
}
void debug(const char* fmt, ... );


struct void* heap;
struct void* block1;
struct void* block2;
void test1() {
	debug("Test 1: STARTED...\n");
	struct void* heap = heap_init(1000);
	if (heap == NULL){
        err("Test 1 failed. Heap allocator broken");
    }
    debug_heap(stdout, heap);
    debug("Test 1 passed");

}

void test2() {
	debug("Test 2: STARTED...\n");
	struct void* block1 = _malloc(100);
    if (!block1) err("Test 2 failed. Can not allocate single block");
    debug_heap(stdout, heap);
    debug("Test 2 passed");
}

void test3(){
	debug("Test 3: STARTED...\n");
    _free(block1);
    struct block_header* header = block_get_header(block1);
    if (!(header -> is_free)) err("Test 3 failed. Block was not freed");
    debug_heap(stdout, heap);
    debug("Test 3 passed");
}

void test4(){
	debug("Test 4: STARTED...\n");
    block1 = _malloc(100);
    block2 = _malloc(200);
    _free(block1);
    struct block_header* header1 = block_get_header(block1);
    struct block_header* header2 = block_get_header(block2);
    if (!header1 -> is_free || header2 -> is_free) err("Test 4 failed. Allocation and freeing failed");
    debug_heap(stdout, heap);
    debug("Test 4 passed");
}

void test5(){
	debug("Test 5: STARTED...\n");
    block1 = _malloc(2000);
    if (!block1) err("Test 5 failed. heap grown failed");
    debug_heap(stdout, heap);
    debug("Test 5 passed");
}



int main() {
	test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}