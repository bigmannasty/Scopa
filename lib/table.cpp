#include "table.h"

table() {}

void firstRoundCards(deck* theDeck) {
	for (int i = 0; i < 4; i++) {
		cardsOnTable[i] = theDeck->drawCard();
	}
	totalCards = 4;
}

card* take(int tableIndex) {
	card* cardTaken = cardsOnTable[tableIndex];
	cardsOnTable[tableIndex] = NULL;
	totalCards -= 1;
	return cardTaken;
}

void aceTake(player* takingPlayer) {
	for (int i = 0; i < 10; i++) {
		if (cardsOnTable[i] != NULL) { takingPlayer->collectedCards[takingPlayer->topCollectedIndex] = take(i); takingPlayer->topCollectedIndex++; }
	}
	totalCards = 0;
}

int takeWith(card* takingCard, player* takingPlayer) {
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

void playCard(card* playedCard) {
	for (int i = 0; i < 10; i++) {
		if (cardsOnTable[i] == NULL) { cardsOnTable[i] = playedCard; totalCards += 1; return; }
	}
}

void printTable() {
	for (int i = 0; i < 10; i++) {
		if (cardsOnTable[i] != NULL) cardsOnTable[i]->printCard();
	}
}