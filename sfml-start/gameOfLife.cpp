#include"gameOfLife.h"
#include <iostream>
#include "btn.h"

//constructor
gameOfLife::gameOfLife()
{
	std::cout << "Base constructor \n";
	this->initVars();
	this->initWindow();
	this->addBtns();


}
//destructor
gameOfLife::~gameOfLife()
{
	std::cout << "Close window \n";
	delete this->mainWindow;
	delete drawModeBtn;
	delete drawMode;
	delete startEvolutionBtn;
	delete stopEvolutionBtn;
	delete evoRunningMode;

}
//accessor
const bool gameOfLife::running() const
{
	return this->mainWindow->isOpen();
}
//pvt funcs
void gameOfLife::initVars()
{
	std::cout << "Init vars \n";
	this->mainWindow = nullptr;
	this->drawModeBtn = nullptr;
	this->drawMode = nullptr;
	this->startEvolutionBtn = nullptr;
	this->stopEvolutionBtn = nullptr;
	this->evoRunningMode = nullptr;
	this->mousePosition = sf::Mouse::getPosition();
	originalTextSize = { 25 };

}

void gameOfLife::initWindow()
{
	std::cout << "Init window \n";
	this->vMode.height = {720};
	this->vMode.width = { 1280 };
	this->mainWindow = new sf::RenderWindow(this->vMode, "Game of Life", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	// position to center
	this->mainWindow->setPosition(
		sf::Vector2i(
			(sf::VideoMode::getDesktopMode().width / 2) - 445,
			(sf::VideoMode::getDesktopMode().height / 2) - 480
		)

	);

	this->mainWindow->setKeyRepeatEnabled(true);
}



void gameOfLife::pollEvents()
{
	while (this->mainWindow->pollEvent(this->eventHandler)) {

		switch (this->eventHandler.type) {


		case sf::Event::Closed:
			this->mainWindow->close();
			break;

		case sf::Event::Resized:
			std::cout << "New window width: " << this->eventHandler.size.width << " New window height: " << this->eventHandler.size.height << std::endl;
			break;

		case sf::Event::MouseMoved:
			for (auto& pair : buttonMap) {
				if (pair.first->isMouseOver(*this->mainWindow)) {
					pair.first->setBackColor(sf::Color::Magenta);
				}
				else {
					pair.first->setBackColor(sf::Color::Green);
				}
			}
	
			break;
		case sf::Event::MouseButtonPressed:
			if (this->eventHandler.mouseButton.button == sf::Mouse::Left) {

				this->mousePosition = sf::Mouse::getPosition(*this->mainWindow);

				// Print the mouse position
				std::cout << "Mouse Position: x = " << this->mousePosition.x << ", y = " << this->mousePosition.y << std::endl;
			}
			for (auto& pair : buttonMap) {
				if (pair.first->isMouseOver(*this->mainWindow)) {
					std::cout << "Button pressed: " << pair.second << "\n";
				
				}
			}
		}
		break;

		
	}
}





// public funcs
void gameOfLife::update()
{
	this->pollEvents();
}

void gameOfLife::render()
{
	this->mainWindow->clear(sf::Color(255, 255, 255));

	drawModeBtn->drawTo(*this->mainWindow);
	startEvolutionBtn->drawTo(*this->mainWindow);
	this->mainWindow->display();

}

void gameOfLife::addBtns()
{
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";
	else
		std::cout << "Font Loaded!\n";

	// draw mode btn
	drawModeBtn = new btnStore::Button("Draw", { 100, 100 }, originalTextSize , sf::Color::Green, sf::Color::Black);
	drawModeBtn->setFont(font);
	drawModeBtn->setPosition({ 20,20 });
	buttonMap[drawModeBtn] = "Draw";
	// lock items btn
	startEvolutionBtn = new btnStore::Button("Start", { 100, 100 }, originalTextSize, sf::Color::Green, sf::Color::Black);
	startEvolutionBtn->setFont(font);
	startEvolutionBtn->setPosition({ 140,20 });
	buttonMap[startEvolutionBtn] = "Start";

}

