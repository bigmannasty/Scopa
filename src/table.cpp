#include "table.h"

table::table() {}

void table::firstRoundCards(deck* theDeck) {
	for (int i = 0; i < 4; i++) { //errbody drawin cards
		cardsOnTable[i] = theDeck->drawCard();
	}
	totalCards = 4;
}

card* table::take(int tableIndex) {
	printf("TAKE CALL");
	card* cardTaken = cardsOnTable[tableIndex]; //set the taken card to the current table index
	cardsOnTable[tableIndex] = NULL; //set the table index to null
	totalCards -= 1; //drop the total cards on the table
	return cardTaken; //send out the card that was taken
}

void table::aceTake(player* takingPlayer) {
	for (int i = 0; i < 10; i++) { //take all the cards on the table
		if (cardsOnTable[i] != NULL) { takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(i); takingPlayer->topCollectedIndex++; }
	}
	totalCards = 0;
}

int table::takeWith(card* takingCard, player* takingPlayer) {
	printf("\nTAKE WITH CALL\n");
	int takeVal = takingCard->getNum(); //value of the taking card 
	for (int i = 0; cardsOnTable[i] != NULL; i++) { //for all the cards on the table
		printf("\nSEARCH LOOP 1 %i\n", i);
		if (cardsOnTable[i] != NULL && cardsOnTable[i]->getNum() == takeVal) { //if the card in the current index is not null and the values are same
			takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(i); //take it!!!
			takingPlayer->topCollectedIndex++; //bump up that topcollected
			printf("\nTake %c%d  With %c%d\n", cardsOnTable[i]->getSuit(), takeVal, takingCard->getSuit(), takeVal); //print for debug
			return 1;
		}
	}
	
	if (takeVal == 1) { //take everything if you have an ace
		printf("\nACE TAKE\n");
		aceTake(takingPlayer);
		return 1;
	}

	/*for (int add1 = 0; cardsOnTable[add1] != NULL; add1++) { //for every card on the table
		card* add1Card = cardsOnTable[add1];
		int add1Val = add1Card->getNum(); //get value of the current index card
		for (int add2 = 0; cardsOnTable[add2] != NULL; add2++) { //for every other card on the table
			card* add2Card = cardsOnTable[add2];
			int add2Val = add2Card->getNum(); 
			if (add1 != add2 && takeVal == (add1Val + add2Val)) { //if they add together then take propabley
				printf("\nTake %c%d and %c%d With %c%d\n", add1Card->getSuit(), add1Val, add2Card->getSuit(), add2Val, takingCard->getSuit(), takeVal); //print for debug
				takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(add1); 
				takingPlayer->topCollectedIndex++; 
				takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(add2); 
				takingPlayer->topCollectedIndex++; 
				return 1;
			}
				
		}

	}*/
	
	printf("\ntake with done\n");

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
	for (int i = 0; i < 10; i++) { //print for every index
		if (cardsOnTable[i] != NULL) cardsOnTable[i]->printCard();
	}
}
