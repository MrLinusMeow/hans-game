#include <stdlib.h>
#include <assert.h>

int main(){
	short const maze = 0x1554; // 0001 0101 0101 0100
	short hans = 0x0008; // 0000 0000 0000 1000
	short temp = hans;
	short state = ((maze ^ hans) == maze) ? -1 : maze ^ hans;
	do{
		volatile char y = 1;
		volatile char x = 1;
		hans = (temp == hans) ? hans : 0;
		if(hans == 0) abort();
		state = ((state - maze) == hans) ? state : state^temp;
		temp = hans;
		y = y ? (hans <<= 4) : (hans >>= 4);
		if( ((y & maze) == 0) ) abort();
		else { temp = hans; hans = y; continue; }
		x = x ? (hans >>= 1) : (hans <<= 1);
		if( ((x & maze) == 0) ) abort();
		else { temp = hans; hans = x; continue; }
	}while(state != 0x1555);
	return 0;
}
