#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include "table.h"
#include "deck.h"
#include "player.h"

class game {
	
 public:
	int gameNum;
	player* players[4];
	table tab;
	deck deck1;
	int roundNum;
	int cardPrio[10] = {7, 6, 5, 4, 3, 2, 10, 9, 8, 1};
	player* lastToTake;
	
	game(int gameNum);

	//function covering the turn for a given player
	//first tries to take from the table
	//if not possible then just play the least valuable card
	void turn(player* player);
	
	//funciton handling each round of the game
	void round();
};


#endif
