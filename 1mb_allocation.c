#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define TOTAL_MEMSPACE  1024 //1048576 //1MB
#define BLOCK_SIZE 16 //16B
#define NUM_OF_BLOCKS (TOTAL_MEMSPACE / BLOCK_SIZE) //2^16 blocks
const int FREE_INDEXES[6] = { 7, 2, 15, 9, 22, 61};

uint64_t mem_block[NUM_OF_BLOCKS];
int head_index = -1; //index of free space linked list
int current_index = 0; //pointer to current free memory block

int alloc_new(void)
{
	/* Do I have room to grow ? */
	if (current_index < NUM_OF_BLOCKS) {
		current_index++;
		return current_index;
	}
	else {
		if (head_index == -1) {
			/* Array is really full. return -1 */
			return -1;
		} else {
			/* Array is "full" but I have free list. Return the first free index (head_index) */
			int prev_head_index = mem_block[head_index];
			if (prev_head_index == head_index){
				/* Array is really full. return -1 */
				head_index = -1;
			} else {
				mem_block[head_index] = mem_block[prev_head_index];
			}
			return prev_head_index;
		}
	}
}

void free_new(int index_to_free)
{
	if (head_index == -1) {
		/* First free element. set it as head */
		head_index = index_to_free;
	}
	/* Free indexes are appended to list head */	 
	mem_block[index_to_free] = mem_block[head_index]; //set the index listed inside the current head in the new index to free
	mem_block[head_index] = index_to_free; //set the new index to free as the index listed in the current head
}

int main()
{
	printf("program started with:\n");
	printf("TOTAL_MEMSPACE: %d, BLOCK_SIZE: %d, NUM_OF_BLOCKS: %d\n", TOTAL_MEMSPACE, BLOCK_SIZE, NUM_OF_BLOCKS);
	int received_index = 0;
	while (received_index != -1)
	{
		received_index = alloc_new();
		printf("Received index %d\n", received_index);
	}
	printf("memory full, freeing up some memory\n");
	for (int index_to_free = 0 ; index_to_free < (sizeof FREE_INDEXES / sizeof *FREE_INDEXES) ; index_to_free++)
	{
		printf("freeing index %d\n",FREE_INDEXES[index_to_free]);
		free_new(FREE_INDEXES[index_to_free]);
	}
	received_index = 0;
	while (received_index != -1)
	{
		received_index = alloc_new();
		printf("Received index %d\n", received_index);
	}

	return 0;
}