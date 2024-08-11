#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

char* map(uint16_t state, uint16_t hans){
	static char str[21];
	for(int i = 19; i >= 0; --i){
		if( ((i % 5) == 0) ){
			str[i] = '\n';
		}
		else if(hans == 1){
			str[i] = 'H';
			state = state >> 1;
			hans >>= 1;
		}
		else if(state % 2){
			str[i] = '1';
			state = state >> 1;
			hans >>= 1;
		}
		else {
			str[i] = '0';
			state = state >> 1;
			hans >>= 1;
		}
	}
	str[20] = '\0';
	return str;
}

int main(void){
	printf("\e[95mGet Hans to the end using commands but do not touch the lava.\nUsage: only valid input is a natural number e.g. 0, 1, 2...\nEverything above 1 is same as 1.\e[0m\n");
	volatile uint16_t maze = 0x1554;
	volatile uint16_t hans = 0x0008;
	volatile uint16_t prev = hans;
	volatile uint16_t state = maze ^ hans;
	uint16_t Y = 1;
	uint16_t X = 1;
	uint8_t moveDir = 2;
	do{
		asm("nop");
		printf("\e[33;1m%s\e[0m", map(state, hans));
		printf("\n\e[31;1m0: North or South\t1: West or East\e[0m\n");
		assert(scanf("%hhd", &moveDir));
		if(moveDir == 0){
			printf("\e[31;1m(North: 1, South: 0)\e[0m\n");
			assert(scanf("%hd", &Y));
			hans = Y ? (hans << 4) : (hans >> 4);
			state ^= prev;
		}else{
			printf("\e[31;1m(West: 1, East: 0)\e[0m\n");
			assert(scanf("%hd", &X));
			hans = X ? (hans << 1) : (hans >> 1);
			state ^= prev;
		}
		if(( hans == 0 )||( (state & (~hans)) != maze )) {
				printf("\e[97;1mYou fell to the lava.\n- Game Over -\e[0m\n");
				exit(0);
		}
		state ^= hans;
		prev = hans;
	}while(state != 0x1555);
	printf("\e[97;1mSuccess!\e[0m\n");
	return 0;
}
