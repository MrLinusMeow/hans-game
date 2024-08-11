#include <stdlib.h>
#include <assert.h>

int main(){
	volatile short const maze = 0x1554; // maze: 0001 0101 0101 0100
	short hans = 0x0008; // position of hans: 0000 0000 0000 1000
	short prev = hans; // remember hans's state
	short state = ((maze ^ hans) == maze) ? -1 : maze ^ hans; // checks if hans and maze will collide
	assert(state != -1); // then it will assert()
	volatile char Y = 1; // up
	volatile char X = 1; // right
	volatile char moveDir = 0; // 0: move direction Y , 1: move direction X , else do nothing
	do{
		asm("nop"); // does nothing
		state = ((state - maze) == hans) ? state : state^prev; // removes previous hans if present in state
		prev = hans; // previous hans is now hans
		if(moveDir == 0){ // vertical direction
			Y = Y ? (hans <<= 4) : (hans >>= 4); // go up else go down
			assert((Y & maze) != 0); // assert when hans is colliding with wall
			hans = Y; // hans is moved
		}else if(moveDir == 1){ // horizontal direction
			X = X ? (hans >>= 1) : (hans <<= 1); // go right else go left
			assert((X & maze) != 0); // assert when hans is colliding with wall
			hans = X; // hans is moved
		}else continue; // do not move
	}while(state != 0x1555);
	return 0;
}
