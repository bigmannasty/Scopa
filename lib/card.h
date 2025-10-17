#ifndef card_h
#define card_h

#include <stdio.h>

class card {

public:
	char suit;
	int num;

	card(char suit, int num);

	//return the suit of the given card; i wrote the below comment first so refer to that for additional info
	char getSuit();

	//return the value of the given card; originally the values were private instead of public, 
	//but i got lazy after a while and it was way too much effort to keep going with that system
	int getNum();

	//print the card
	void printCard();
 
};

#endif
