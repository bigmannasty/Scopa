#ifndef deck_h
#define deck_h

#include <stdio.h>
#include <stdlib.h>

class deck {
	
public:
 card* cards[40];
 int indexFilled[40] = {};
 int topCard = 0;
 
 //initialise the deck by randomly generating the cards within ranges
 void initDeck();
 
 //return a card from the top of the deck
 card* drawCard();
 
 //print the top card; only used it in debugging, dont think its useful for anything else
 void peekTop();
 
 //print the cards currently in the deck
 void printCards();
	
};

#endif