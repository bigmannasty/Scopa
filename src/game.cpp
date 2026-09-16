#include "game.h"

game::game(int gameNum) {
	this->gameNum = gameNum;
	this->roundNum = 1;
	deck1.initDeck();
	for (int i = 0; i < 4; i++) {
		players[i] = new player(i); //set stuff for each player or whatever
	}
}

void game::turn(player* player) {
	if (DEBUG == 1) printf("\nTURN CALL\n");
	//first try to take
	for (int i = 0; i < 10; i++) { //going through each prio
		for (int j = 0; j < 3; j++) { //going through each card in the hand 
			//printf("  PRIO %i HANDPOS %i  ", i, j);
			if (player->hand[j] != NULL && player->hand[j]->getNum() == cardPrio[i]) {
				int takeWithRet = tab.takeWith(player->hand[j], player); //save return value for sweep tracking
				if (takeWithRet > 0) { //if took card
					player->collectedCards[player->topCollectedIndex] = player->hand[j]; //transfer from hand to collected pile
					player->topCollectedIndex += 1; //increment topcollected : was a bug until i gained sentience 
					player->hand[j] = NULL; 
					lastToTake = player;
					if (takeWithRet == 1 && tab.totalCards == 0) player->numOfSweeps += 1; //if was a regular take and no cards left, sweep!
					return; 
				}
			}
		}
	}
	if (DEBUG == 1) printf("\nNO TAKE\n");
	
	//if cant take, play the "least valuable card"
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < 3; j++) { //going through each card in the hand 
			if (player->hand[j] != NULL && player->hand[j]->getNum() == cardPrio[i]) { 
				tab.playCard(player->hand[j]);
				player->hand[j] = NULL;
				player->cardsInHand -= 1;
				return;
			}
		}
	}
	
}


void game::round() {
	
	for (int i = 0; i < 4; i++) { //each player draw cards
		players[i]->drawCards(&deck1);
		if (DEBUG == 1) printf("\nPLAYER %i DREW\n", i);
	}
	
	if (roundNum == 1) { //deal cards onto table if itgs tthe first round of the game
		tab.firstRoundCards(&deck1);
	}
	
	for (int turnNo = 0; turnNo < 3; turnNo++) {
		if (DEBUG == 1) tab.printTable();
		
		for (int i = 0; i < 4; i++) { //go thorugh each players turn
			if (DEBUG == 1) { printf("\nPlayer %d Hand:", i); players[i]->printHand(); }
			turn(players[i]);
			if (DEBUG == 1) printf("\nTURN PLAYER %i DONE\n", i);
			tab.sortTable();
		}
	}
	
	if (DEBUG == 1) tab.printTable();
	if (roundNum == 3) {	
		for (int i = 0; i < 10; i++) {
			if (tab.cardsOnTable[i] != NULL) {
				lastToTake->collectedCards[lastToTake->topCollectedIndex] = tab.cardsOnTable[i];
				lastToTake->topCollectedIndex++;
				tab.cardsOnTable[i] = NULL;
			}
		}
	}
	if (DEBUG == 1) { tab.printTable(); printf("\nEND ROUND\n"); }
	roundNum++;
}
