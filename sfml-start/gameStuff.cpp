#include "gameStuff.h"
#include <iostream>
#include "button.h"
// constructor
gameOfLife::gameOfLife()
{
	this->initVars();
	this->initWindow();
	this->addBtns();
}
//destructor
gameOfLife::~gameOfLife()
{
	std::cout << "closed \n";
	delete this->mainWindow;
	delete drawModeBtn;
}

//pvt func
void gameOfLife::initVars()
{
	this->mainWindow = nullptr;
	this->drawModeBtn = nullptr;
	this->mousePosition = sf::Mouse::getPosition();
}

void gameOfLife::initWindow()
{
	std::cout << "init \n";
	this->vMode.height = 720;
	this->vMode.width = 1280;
	this->mainWindow = new sf::RenderWindow(this->vMode, "My window", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
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
			if (drawModeBtn->isMouseOver(*this->mainWindow)) {
				std::cout << "test " << "\n";
			}
			break;

		case sf::Event::MouseMoved:
			if (drawModeBtn->isMouseOver(*this->mainWindow)) {
				drawModeBtn->setBackColor(sf::Color::Magenta);
			}
			else {
				drawModeBtn->setBackColor(sf::Color::Green);
			}
			break;

		}
	}
}

void gameOfLife::addBtns()
{
	// Font
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";
	drawModeBtn = new Button("Enter", { 100, 100 }, 30, sf::Color::Green, sf::Color::Black);
	drawModeBtn->setFont(font);
	drawModeBtn->setPosition({ 10, 10 });
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
	/*this->drawModeBtn->drawTo(this->mainWindow);*/
	if (drawModeBtn) {
		drawModeBtn->drawTo(*this->mainWindow);
	}
	this->mainWindow->display();
}
