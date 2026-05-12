#include "game.h"

game(int gameNum) {
	this->gameNum = gameNum;
	this->roundNum = 1;
	deck1.initDeck();
	for (int i = 0; i < 4; i++) {
		players[i] = new player(i);
	}
}

void turn(player* player) {
	//first try to take
	for (int i = 0; i < 10; i++) { //going through each prio
		for (int j = 0; j < 3; j++) { //going through each card in the hand 
			if (player->hand[j] != NULL && player->hand[j]->getNum() == cardPrio[i]) {
				if (tab.takeWith(player->hand[j], player) == 1) { 
					player->collectedCards[player->topCollectedIndex] = player->hand[j]; 
					player->hand[j] = NULL; 
					lastToTake = player; 
					return; 
				}
			}
		}
	}
	
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


void round() {
	
	for (int i = 0; i < 4; i++) { //each player draw cards
		players[i]->drawCards(&deck1);
		printf("PLAYERS DREW");
	}
	
	if (roundNum == 1) { //deal cards onto table if itgs tthe first round of the game
		tab.firstRoundCards(&deck1);
	}
	
	for (int turnNo = 0; turnNo < 3; turnNo++) {
		printf("\nTABLE:");
		tab.printTable();
		
		for (int i = 0; i < 4; i++) { //go thorugh each players turn
			printf("\nPlayer %d Hand:", i);
			players[i]->printHand();
			printf("\nthing1");
			turn(players[i]);
		}
	}
	
	printf("\nTABLE:");
	tab.printTable();
	if (roundNum == 3) {
		
		for (int i = 0; i < 10; i++) {
			if (tab.cardsOnTable[i] != NULL) {
				lastToTake->collectedCards[lastToTake->topCollectedIndex] = tab.cardsOnTable[i];
				lastToTake->topCollectedIndex++;
				tab.cardsOnTable[i] = NULL;
			}
		}
		//tab.cardsOnTable = {};
	}
	printf("\nTABLE:");
	tab.printTable();
	printf("\nEND ROUND");
	roundNum++;
}