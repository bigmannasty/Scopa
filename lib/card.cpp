#include "card.h"

card(char suit, int num) {
 this->suit = suit;
 this->num = num;
}

char getSuit() {
 return this->suit;
}

int getNum() {
return this->num;
}

void printCard() {
 printf("\t%c%d", this->suit, this->num);
}
