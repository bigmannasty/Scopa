#ifndef player_h
#define player_h

#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "deck.h"

class player {
 public:
	int playerNum;
	card* hand[3] = {};
	int cardsInHand = 0;
	card* collectedCards[40] = {};
	int topCollectedIndex = 0;
	int numOfSweeps = 0;
	
	player(int playerNum);

	//draw 3 cards from the given deck
	void drawCards(deck* theDeck);
	
	//display the cards in the given player's hand
	void printHand();
};

#endif
