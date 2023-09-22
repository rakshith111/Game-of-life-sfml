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
	void addInfoText();
	sf::Color bgColor;
	sf::Vector2i mousePosition; // get global mouse position

	btnStore::Button* drawModeBtn; // Declare a pointer to Button
	btnStore::Button* startEvolutionBtn;

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
	sf::View gridView;
	sf::Text title;

	std::unordered_map<btnStore::Button*, boolBtnData> buttonMap; // Map to store buttons and their names

	short baseTextSize; // Store the original text size
	//funcs
	void initVars();
	void initWindow();
	void pollEvents();
};
