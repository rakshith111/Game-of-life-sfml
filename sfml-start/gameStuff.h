#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>
#include "button.h"
class gameOfLife
{
private:
	//vars
	sf::RenderWindow* mainWindow;
	sf::VideoMode vMode;
	sf::Event eventHandler;
	Button* drawModeBtn; // Declare a pointer to Button
	void initVars();
	void initWindow();
	void pollEvents();
	
		
public:
	gameOfLife();
	~gameOfLife();
	
	//accessors 
	const bool running() const;

	void update();
	void render();
	void addBtns();
	// get global mouse position
	sf::Vector2i mousePosition;




};

