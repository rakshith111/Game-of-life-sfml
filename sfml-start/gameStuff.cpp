#include "gameStuff.h"
#include <iostream>

// constructor
gameOfLife::gameOfLife()
{
	this->initVars();
	this->initWindow();
}
//destructor
gameOfLife::~gameOfLife()
{
	std::cout << "closed \n";
	delete this->mainWindow;
}

//pvt func
void gameOfLife::initVars()
{
	this->mainWindow = nullptr;
	this->mousePosition = sf::Mouse::getPosition();
}

void gameOfLife::initWindow()
{
	std::cout << "init \n";
	this->vMode.height = 720;
	this->vMode.width = 1280;
	this->mainWindow = new sf::RenderWindow(this->vMode, "My window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

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
		case sf::Event::TextEntered:
			if (this->eventHandler.text.unicode < 128) {
				printf("%c", this->eventHandler.text.unicode);
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (this->eventHandler.mouseButton.button == sf::Mouse::Left) {

				this->mousePosition = sf::Mouse::getPosition(*this->mainWindow);

				// Print the mouse position
				std::cout << "Mouse Position: x = " << this->mousePosition.x << ", y = " << this->mousePosition.y << std::endl;
			}
			break;


		}
	}
}



const bool gameOfLife::running() const
{
	return this->mainWindow->isOpen();
}

// functions
void gameOfLife::update()
{
	this->pollEvents();
}

void gameOfLife::render()
{
	this->mainWindow->clear(sf::Color(0, 0, 0));
	// Draw game objs here
	this->mainWindow->display();
}
