#include "card.h"

card::card(char suit, int num) {
	this->suit = suit;
	this->num = num;
}

char card::getSuit() {
	return this->suit;
}

int card::getNum() {
	return this->num;
}

void card::printCard() {
	printf("\t%c%d", this->suit, this->num);
}
