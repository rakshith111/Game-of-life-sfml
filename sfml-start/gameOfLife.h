#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>
#include <unordered_map>
#include "btn.h"

class gameOfLife
{
public:
	gameOfLife();
	~gameOfLife();

	//accessors 
	const bool running() const;
	//funcs
	void update();
	void render();
	void addBtns();

	sf::Vector2i mousePosition; // get global mouse position
	btnStore::Button* drawModeBtn; // Declare a pointer to Button

	bool* drawMode;
	btnStore::Button* startEvolutionBtn;
	bool* evoRunningMode;
	btnStore::Button* stopEvolutionBtn;



private:
	//vars
	sf::RenderWindow* mainWindow;
	sf::VideoMode vMode;
	sf::Event eventHandler;
	sf::Font font;     // Declare a font

	std::unordered_map<btnStore::Button*, std::string> buttonMap; // Map to store buttons and their names
	int originalTextSize; // Store the original text size
	//funcs
	void initVars();
	void initWindow();
	void pollEvents();
};