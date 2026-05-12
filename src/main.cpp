#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "game.h"

int main() {
	srand(1000);
	
	game game1(1);
	for (int roundNum = 0; roundNum < 3; roundNum++) {
		game1.round();
	}
	
	return 0;


}