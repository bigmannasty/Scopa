#include "table.h"

table::table() {}

void table::firstRoundCards(deck* theDeck) {
	for (int i = 0; i < 4; i++) {
		cardsOnTable[i] = theDeck->drawCard();
	}
	totalCards = 4;
}

card* table::take(int tableIndex) {
	card* cardTaken = cardsOnTable[tableIndex];
	cardsOnTable[tableIndex] = NULL;
	totalCards -= 1;
	return cardTaken;
}

void table::aceTake(player* takingPlayer) {
	for (int i = 0; i < 10; i++) {
		if (cardsOnTable[i] != NULL) { takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(i); takingPlayer->topCollectedIndex++; }
	}
	totalCards = 0;
}

int table::takeWith(card* takingCard, player* takingPlayer) {
	int takeVal = takingCard->num;
	for (int i = 0; i < 10; i++) {
		if (cardsOnTable[i] != NULL && cardsOnTable[i]->getNum() == takeVal) {
			takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(i); 
			takingPlayer->topCollectedIndex++;
			printf("\nTake With %c%d", takingCard->getSuit(), takeVal);
			return 1;
		}
	}
	
	if (takeVal == 1) {
		aceTake(takingPlayer);
		return 1;
	}
	return 0;
}

void table::playCard(card* playedCard) {
	for (int i = 0; i < 10; i++) {
		if (cardsOnTable[i] == NULL) { cardsOnTable[i] = playedCard; totalCards += 1; return; }
	}
}

void table::printTable() {
	for (int i = 0; i < 10; i++) {
		if (cardsOnTable[i] != NULL) cardsOnTable[i]->printCard();
	}
}
