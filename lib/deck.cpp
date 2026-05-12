#include "deck.h"

deck() {}

//initialise the deck by randomly generating the cards within ranges
void initDeck() {
	//cards = {};
	int suitsGend[4] = {};
	char suit;
	for (int i = 0; i < 4; i++) {
		//printf("\nLOOP1");
		int suitIndex = rand() % 4;
		//printf("\n %d", suitIndex);
		while (suitsGend[suitIndex] != 0) {
			suitIndex = rand() % 4;
		}
		suitsGend[suitIndex] = 1;
		switch(suitIndex)
		{
			case 0:
				suit = 'G';break;
				
			case 1:
				suit = 'B';break;
				
			case 2:
				suit = 'S';break;
				
			case 3:
				suit = 'C';break;
			default:
				printf("fuck off");break;
		}
		int numsGend[10] = {};
		for (int j = 0; j < 10; j++) {	
			//printf("\nLOOP2");
			int numIndex = rand() % 10;
			while (numsGend[numIndex] != 0) {
				numIndex = rand() % 10;
			}
			numsGend[numIndex] = 1;
			int deckIndex = rand() % 40;
			while (indexFilled[deckIndex] != 0) {
				deckIndex = rand() % 40;
			}
			indexFilled[deckIndex] = 1;
			//printf("\n%c %d		%d", suit, numIndex, deckIndex);
			cards[deckIndex] = new card(suit, numIndex+1);
		}
	}
}
 
//return a card from the top of the deck
	card* drawCard() {
	card* drawnCard = cards[topCard];
	topCard++;
	return drawnCard;
}

//print the top card; only used it in debugging, dont think its useful for anything else
	void peekTop() {
	cards[topCard]->printCard();
	return;
}

//print the cards currently in the deck
void printCards() {
	printf("PRINT CARDS");
	for (int i = topCard; i < 40; i++) {
		cards[i]->printCard();
	}
	return;
}