#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "game.h"
#include "scoreboard.h"

int main() {
		
	int startSeed = 1000;
	int endSeed = 1000;

	for (int ranseed = startSeed; ranseed <= endSeed; ranseed += 100) {
		srand(ranseed);

		scoreboard SB;	

		for (int gameNum = 0; gameNum < 100; gameNum++) {
			game game1(gameNum);
			SB.setGame(&game1);
			if (DEBUG == 1) SB.printScores();

			for (int roundNum = 0; roundNum < 3; roundNum++) {
				game1.round();
			}

			if (DEBUG == 1) {
				for (int i = 0; i < 4; i++) {
					printf("\nPLAYER %i", i);
					game1.players[i]->printCollected();
					printf("\n");
				}
			}
		

			SB.scoring();
			if (DEBUG==1) SB.printScores();
		}

		SB.printScores();
	}

	
	return 0;

}
