#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "game.h"
#include "scoreboard.h"

int main() {
	srand(1000);

	scoreboard SB;	

	game game1(1);

	SB.setGame(&game1);

	SB.printScores();

	for (int roundNum = 0; roundNum < 3; roundNum++) {
		game1.round();
	}

	for (int i = 0; i < 4; i++) {
		printf("\nPLAYER %i", i);
		game1.players[i]->printCollected();
		printf("\n");
	}

	SB.scoring();

	SB.printScores();
	
	return 0;


}
