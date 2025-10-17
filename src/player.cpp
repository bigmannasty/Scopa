#include "player.h"

player::player(int playerNum) {
	this->playerNum = playerNum;
}
	
void player::drawCards(deck* theDeck) {
	for (int i = 0; i < 3; i++) {
		hand[i] = theDeck->drawCard();
	}
	cardsInHand = 3;
}
	
void player::printHand() {
	for (int i = 0; i < 3; i++) {
		if (hand[i] != NULL) hand[i]->printCard();
	}
}
