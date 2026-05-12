#ifndef table_h
#define table_h

#include <stdio.h>
#include <stdlib.h>

class table {
 public:
	card* cardsOnTable[10] = {};
	int totalCards = 0;
	
	//deal the cards onto the table at the start of the round
	void firstRoundCards(deck* theDeck);
	
	//take a card at some index in the table and remove it from the table
	card* take(int tableIndex);
	
	//sweep all cards on the table with an ace
	void aceTake(player* takingPlayer);
	
	//take with some card by going through all the cards on the table and finding a match
	//return 1 if a card is taken, return 0 if there's no match
	int takeWith(card* takingCard, player* takingPlayer);
	
	//add a card to the table
	void playCard(card* playedCard);
	
	//print all the cards currently on the table
	void printTable();
	
};


#endif