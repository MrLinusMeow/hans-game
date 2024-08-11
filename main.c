#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

int main(){
	uint16_t const maze = 0x1554; // maze: 0001 0101 0101 0100
	static uint16_t hans = 0x0008; // position of hans: 0000 0000 0000 1000
	uint16_t prev = hans; // remember hans's state
	static uint16_t state = maze; // checks if hans and maze will collide
	volatile uint16_t Y = 1; // 0: down , 1: up
	volatile uint16_t X = 1; // 0: left , 1: right
	volatile uint8_t moveDir = 2; // 0: move direction Y , 1: move direction X , else do nothing
	do{
		asm("nop"); // does nothing
		state += hans; // update hans' postion
		state = ((state - maze) == hans) ? state : state^prev; // removes previous hans if it's present in state
		prev = hans; // remember hans's state
		if(moveDir == 0){ // vertical direction
			hans = Y ? (hans << 4) : (hans >> 4); // move up or down
			assert(hans != 0); // assert() when hans is out of bounds
			assert((maze & hans) != maze); // assert() when hans collides with maze wall
		}else if(moveDir == 1){ // horizontal direction
			hans = X ? (hans >> 1) : (hans << 1); // move right or left
			assert(hans != 0); // assert() when hans is out of bounds
			assert((maze & hans) != maze); // assert() when hans collides with maze wall
		}else continue; // do not move
	}while(state != 0x1555); // check if hans' completed the maze
	return 0; // success
}
