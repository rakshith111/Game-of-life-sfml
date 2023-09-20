#include<iostream>
#include "gameStuff.h"

int gg() {
	gameOfLife myGame;

	// Game loop
	while (myGame.running()) {
	
	
		// Update
		myGame.update();
		// Render
		myGame.render();

		// Draw game objects
		
	}
	return 0;
}