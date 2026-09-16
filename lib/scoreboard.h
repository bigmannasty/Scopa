#ifndef scoreboard_h
#define scoreboard_h

#include <stdio.h>
#include "game.h"
#include "player.h"

class scoreboard {

public:
	int scores[4]{}; //scores per player index
	int golds[4]{}; //golds per player
	int cards[4]{}; //cards per player
	game* thisGame; //game link
	
	//set scores to zero when instantiated
	scoreboard();

	//set golds and cards arrs to zeroes
	void setGoldsAndCards();

	//set the link to the current game getting scored
	void setGame(game* thisGame);
	
	//print scoreboard
	void printScores();

	//get player with highest cards
	int getMaxCards();

	//get player with highest golds
	int getMaxGolds();

	//get scoring info for current player and score for sweeps and K/7 of Gold
	void countPlayerScore(int playerNum);

	//convert a card's value into primera value
	int cardValToPrimera(int cardVal);

	//calculate the primeras of each player and return the player with the highest
	int primera();

	//overall scoring funciton
	void scoring();

};

#endif
