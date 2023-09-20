#include<iostream>
#include "gameStuff.h"

int main() {
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