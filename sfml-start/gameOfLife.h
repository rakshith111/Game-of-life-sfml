#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>
#include<string>
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
	sf::Color bgColor;
	sf::Vector2i mousePosition; // get global mouse position
	btnStore::Button* drawModeBtn; // Declare a pointer to Button


	btnStore::Button* startEvolutionBtn;
	btnStore::Button* stopEvolutionBtn;

	struct boolBtnData {
		bool state;
		std::string btnName;
	};

private:
	//vars
	sf::RenderWindow* mainWindow;
	sf::VideoMode vMode;
	sf::Event eventHandler;
	sf::Font font;     // Declare a font

	std::unordered_map<btnStore::Button*, boolBtnData> buttonMap; // Map to store buttons and their names

	short originalTextSize; // Store the original text size
	//funcs
	void initVars();
	void initWindow();
	void pollEvents();
};
