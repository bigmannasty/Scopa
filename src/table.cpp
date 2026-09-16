#include "table.h"
#include <assert.h>

table::table() {}

void table::firstRoundCards(deck* theDeck) {
	for (int i = 0; i < 4; i++) { //errbody drawin cards
		cardsOnTable[i] = theDeck->drawCard();
	}
	totalCards = 4;
}

card* table::take(int tableIndex) {
	card* cardTaken = cardsOnTable[tableIndex]; //set the taken card to the current table index
	cardsOnTable[tableIndex] = NULL; //set the table index to null
	totalCards -= 1; //drop the total cards on the table
	assert(totalCards >= 0);
	return cardTaken; //send out the card that was taken
}

void table::aceTake(player* takingPlayer) {
	for (int i = 0; i < 10; i++) { //take all the cards on the table
		if (cardsOnTable[i] != NULL) { takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(i); takingPlayer->topCollectedIndex++; }
	}
	totalCards = 0;
}

int table::takeWith(card* takingCard, player* takingPlayer) {
	//checking for direct single value
	int takeVal = takingCard->getNum(); //value of the taking card 
	for (int i = 0; cardsOnTable[i] != NULL; i++) { //for all the cards on the table
		if (DEBUG == 1) printf("\nSEARCH LOOP 1 INDEX %i\n", i);
		if (cardsOnTable[i]->getNum() == takeVal) { //if the card in the current index is not null and the values are same
			if (DEBUG == 1) printf("\nTake %c%d  With %c%d\n", cardsOnTable[i]->getSuit(), takeVal, takingCard->getSuit(), takeVal); //print for debug
			takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(i); //take it!!!
			takingPlayer->topCollectedIndex++; //bump up that topcollected
			return 1;
		}
	}
	
	//checking for an ace take
	if (takeVal == 1) { //take everything if you have an ace
		if (DEBUG == 1) printf("\nACE TAKE\n");
		aceTake(takingPlayer);
		return 2; //to know to differentiate between ace sweep and regular sweep 
	}
	
	if (totalCards < 2) { return 0; } //if theres less than 3 cards on the table then the rest of this is useless

	//checking for a possible combo of 2 cards
	for (int add1 = 0; cardsOnTable[add1] != NULL; add1++) { //for every card on the table
		card* add1Card = cardsOnTable[add1];
		int add1Val = add1Card->getNum(); //get value of the current index card
		for (int add2 = add1 + 1; cardsOnTable[add2] != NULL; add2++) { //for every other card on the table
			card* add2Card = cardsOnTable[add2];
			int add2Val = add2Card->getNum(); 
			if (add1 != add2 && takeVal == (add1Val + add2Val)) { //if they add together then take propabley
				if (DEBUG == 1) printf("\nTake %c%d and %c%d With %c%d\n", add1Card->getSuit(), add1Val, add2Card->getSuit(), add2Val, takingCard->getSuit(), takeVal); //print for debug
				takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(add1); //take the first 
				takingPlayer->topCollectedIndex++;
				takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(add2); //take the second
				takingPlayer->topCollectedIndex++; 
				return 1;
			}		
		}
	}

	if (totalCards < 2) { return 0; } //if theres less than 3 cards on the table then the rest of this is useless
	
	//checking for a combo of 3 cards
	for (int add1 = 0; cardsOnTable[add1] != NULL; add1++) {
		card* add1Card = cardsOnTable[add1];
		int add1Val = add1Card->getNum(); //get value of the current index card
		for (int add2 = add1 + 1; cardsOnTable[add2] != NULL; add2++) { //for every other card on the table
			card* add2Card = cardsOnTable[add2];
			int add2Val = add2Card->getNum(); 
			int total12 = add1Val + add2Val;
			for (int add3 = add2 + 1; cardsOnTable[add3] != NULL; add3++) { //for every other card on the table
				card* add3Card = cardsOnTable[add3];
				int add3Val = add3Card->getNum();
				if (takeVal == (total12 + add3Val)) {
					if (DEBUG == 1) printf("\nTake %c%d and %c%d and %c%d With %c%d\n", add1Card->getSuit(), add1Val, add2Card->getSuit(), add2Val, add3Card->getSuit(), add3Val, takingCard->getSuit(), takeVal); //print for debug
					takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(add1); //take the first 
					takingPlayer->topCollectedIndex++;
					takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(add2); //take the second
					takingPlayer->topCollectedIndex++; 
					takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(add3); //take the third
					takingPlayer->topCollectedIndex++; 
					return 1;
				}
			}

		}
	}


	if (DEBUG == 1) printf("\nTOOK NONE\n");

	return 0;

}


void table::playCard(card* playedCard) {
	for (int i = 0; i < 10; i++) { //place a card on the table at the next empty index
		if (cardsOnTable[i] == NULL) { cardsOnTable[i] = playedCard; totalCards += 1; return; }
	}
}


void table::sortTable() {
	int emptySpace = 0;
	int pointingIndex = 9;
	while (emptySpace < pointingIndex) { //while there's still space between the search
		if (cardsOnTable[emptySpace] != NULL) { emptySpace += 1; } //if the current space is occupied move up one
		
		else if (cardsOnTable[pointingIndex] == NULL) { pointingIndex -= 1; } //if the current index is empty move down one

		else if (cardsOnTable[emptySpace] == NULL && cardsOnTable[pointingIndex] != NULL) { //if empty and pointy then swap
			cardsOnTable[emptySpace] = cardsOnTable[pointingIndex];
 			cardsOnTable[pointingIndex] = NULL;
		}
	}
}


void table::printTable() {
	if (cardsOnTable[0] == NULL) { printf("\nEMPTY TABLE\n"); return; } //if the table empty
	printf("\n\nTABLE :\t");
	for (int i = 0; i < 10; i++) { //print for every index
		if (cardsOnTable[i] != NULL) cardsOnTable[i]->printCard();
	}
	printf("\n");
}
