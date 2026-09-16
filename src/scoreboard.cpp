#include "scoreboard.h"
#include <assert.h>


scoreboard::scoreboard() {}

void scoreboard::setGoldsAndCards() {
	for (int i = 0; i < 4; i++) {
		this->golds[i] = 0;
		this->cards[i] = 0;
	}
}

void scoreboard::setGame(game* thisGame) {
	setGoldsAndCards();
	this->thisGame = thisGame;
	return;
}

void scoreboard::printScores() {
	printf("\n");
	for (int i = 0; i < 4; i++) { //print scores[i] for each player
		printf("Player %i : %i\t", (i+1), scores[i]);
	}
	printf("\n");
	return;
}

void scoreboard::countPlayerScore(int playerNum) {
	player* currPlayer = thisGame->players[playerNum];
	scores[playerNum] += currPlayer->numOfSweeps; //add sweeps to score
	cards[playerNum] = currPlayer->topCollectedIndex; //get max cards for this playr
	//count golds, and k/7 of gold
	for (int i = 0; i < currPlayer->topCollectedIndex; i++) {
		card* currCard = currPlayer->collectedCards[i]; //get current card
		if (currCard->getSuit() == 'G') { //if gold
			golds[playerNum] += 1; //add to golds tally
			if (currCard->getNum() == 7 || currCard->getNum() == 10) { //if 7 or king of gold
				scores[playerNum] += 1;
			}
		}
	}
	return;
}

int scoreboard::getMaxCards() {
	int maxCard[] = {0, 0}; //[0] is player index and [1] is how many cards
	int tie = 0; // if tie then no points
	for (int i = 0; i < 4; i++) {
		if (cards[i] > maxCard[1]) { //if currplayer's cards higher than current max then update and reset tie flag
			maxCard[0] = i;
			maxCard[1] = cards[i];
			tie = 0;
		}

		else if (cards[i] == maxCard[1]) { //if curreplayer's cards equal to current max then tie flag set
			tie = 1;
		}
	}
	if (tie == 0) return maxCard[0]; //if no tie all good
	else if (tie == 1) return 5; //if tie give 5, arbitrary
	else return 99; //bug - no tie but no max either
}

int scoreboard::getMaxGolds() {
	int maxGold[] = {0, 0}; //[0] is player index and [1] is how many golds
	int tie = 0; // if tie then no points
	for (int i = 0; i < 4; i++) {
		if (golds[i] > maxGold[1]) { //if currplayer's golds higher than current max then update and reset tie flag
			maxGold[0] = i;
			maxGold[1] = golds[i];
			tie = 0;
		}

		else if (golds[i] == maxGold[1]) { //if curreplayer's golds equal to current max then tie flag set
			tie = 1;
		}
	}
	if (tie == 0) return maxGold[0]; //if no tie all good
	else if (tie == 1) return 5; //if tie give 5, arbitrary
	else return 99; //bug - no tie but no max either
}

int scoreboard::cardValToPrimera(int cardVal) {
	assert(cardVal > 0 && cardVal < 11); //make sure cardVal is within range
	switch(cardVal) { //switch for all values 1-10
		case 7:
			return 21;
		case 6:
			return 18;
		case 1:
			return 16;
		case 8:
		case 9:
		case 10:
			return 10; //return 10 if 8,9,10
		default:
			return (cardVal + 10); //return sum of cardVal and 10 when 2-5
	}
}


int scoreboard::primera() {
	int primeraPlayer = 0; //player index with primera
	int highestPrimera = 0; //current highest primera
	int tie = 0;
	for (int playerNo = 0; playerNo < 4; playerNo++) { //for each player
		player* currPlayer = thisGame->players[playerNo]; //get player pointer
		int playerPrimera[] = {0, 0, 0, 0}; //array of each primera slot for current player
		for (int currCard = 0; currCard < currPlayer->topCollectedIndex; currCard++) { //go thorugh player's collected
			int suitIndex = 0;
			switch (currPlayer->collectedCards[currCard]->getSuit()) {
				case 'G':
					break;

				case 'S':
					suitIndex = 1;
					break;

				case 'B':
					suitIndex = 2;
					break;

				case 'C':
					suitIndex = 3;
					break;
			}
			int primeraVal = cardValToPrimera(currPlayer->collectedCards[currCard]->getNum()); //get value of card's primera
			if (primeraVal > playerPrimera[suitIndex]) {
				playerPrimera[suitIndex] = primeraVal; //set value of card's primera in the primera for current player
		
			}
		}
		int primeraTotal = 0;
		for (int i = 0; i < 4; i++) {
			primeraTotal += playerPrimera[i]; //tally up all current player's primera
		}
		assert(primeraTotal >= 0 && primeraTotal < 85); //make sure primera isn't negative and not higher than whats possible
		
		if (primeraTotal > highestPrimera) { //if this player's primera is higher than the current champ, switch em out
			primeraPlayer = playerNo;
			tie = 0;
		}
		else if (primeraTotal == highestPrimera) {
			tie = 1;
		}
	}


	if (tie == 0) { return primeraPlayer; } // if no tie return number of the player with highest primera
	else if (tie == 1) { return 5; } // if tie return 5
	else { return 99; } //if something wrong then return 99
}

void scoreboard::scoring() {
	for (int i = 0; i < 4; i++) { //call player scorings for each
		countPlayerScore(i);
	}
	
	int maxCardPlayer = getMaxCards(); //get them cards right quick
	assert(maxCardPlayer < 6);
	if (maxCardPlayer != 5) {
		scores[maxCardPlayer] += 1;
	}

	int maxGoldPlayer = getMaxGolds(); //get me some ducats
	assert(maxGoldPlayer < 6);
	if (maxGoldPlayer != 5) {
		scores[maxGoldPlayer] += 1;
	}

	int primeraPlayer = primera();
	assert(primeraPlayer < 6);
	if (primeraPlayer != 5) {
		scores[primeraPlayer] += 1;
	}
	
	return;
}
