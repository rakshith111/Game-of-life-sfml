#include"gameOfLife.h"
#include "btn.h"
#include <iostream>
#include<sstream>

//constructor
gameOfLife::gameOfLife()
{
	std::cout << "Base constructor \n";
	this->initVars();
	this->initWindow();
	this->addBtns();
	this->addInfoText();


}
//destructor
gameOfLife::~gameOfLife()
{
	std::cout << "Close window \n";
	delete this->mainWindow;

	delete drawModeBtn;
	delete startEvolutionBtn;


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
	this->startEvolutionBtn = nullptr;
	this->stats = nullptr;

	baseTextSize = { 25 };

}

void gameOfLife::initWindow()
{
	std::cout << "Init window \n";
	this->vMode.height = { 720 };
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
	gridView.setSize(this->mainWindow->getSize().x, this->mainWindow->getSize().y);
	gridView.setCenter(this->mainWindow->getSize().x / 2.0f, this->mainWindow->getSize().y / 2.0f);
	this->mainWindow->setView(gridView);
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
					switch (pair.second.state) {
					case true:
						bgColor = sf::Color::Green;
						break;
					case false:
						bgColor = sf::Color::Red;
						break;
					}
					pair.first->setBackColor(bgColor);
				}
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (this->eventHandler.mouseButton.button == sf::Mouse::Left) {
				// Print the mouse position
				std::cout << "Mouse Position: x = " << this->mousePosition.x << ", y = " << this->mousePosition.y << std::endl;
			}
			for (auto& pair : buttonMap) {


				if (pair.first->isMouseOver(*this->mainWindow)) {

					pair.second.state = !pair.second.state;
					std::cout << "Button pressed: " << pair.second.btnName << "State: " << pair.second.state << "\n";
				}
			}
			break;

		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
			{
				std::cout << "left";
				//gridView->move(-viewSpeed * dt, 0.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Left
			{
				//gridView->move(+viewSpeed * dt, 0.f);
				std::cout << "right";
			}

			break;

		}
	}
}


// public funcs
void gameOfLife::update()
{
	//update dt
	dt = dtClock.restart().asSeconds();

	//update mouse pos
	this->mousePosition = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->mainWindow);

	this->mousePosView = this->mainWindow->mapPixelToCoords(mousePosWindow);

	if (this->mousePosView.x >= 0.f)
		this->mousePosGrid.x = this->mousePosView.x / gridSizeU;

	if (this->mousePosView.y >= 0.f)
		this->mousePosGrid.y = this->mousePosView.y / gridSizeU;


	std::stringstream ss;
	ss << "Screen: " << mousePosition.x << " " << mousePosition.y << " \n"
		<< "Window: " << mousePosWindow.x << " " << mousePosWindow.y << " \n"
		<< "View: " << mousePosView.x << " " << mousePosView.y << " \n"
		<< "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << " \n";
	this->stats->setString(ss.str());


	//events
	this->pollEvents();
}

void gameOfLife::render()
{
	this->mainWindow->clear(sf::Color(255, 255, 255));
	this->mainWindow->setView(gridView);

	drawModeBtn->drawTo(*this->mainWindow);
	startEvolutionBtn->drawTo(*this->mainWindow);
	this->mainWindow->draw(title);
	this->mainWindow->draw(*this->stats);
	this->mainWindow->setView(this->mainWindow->getDefaultView());
	this->mainWindow->display();

}

void gameOfLife::addBtns()
{
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";
	else
		std::cout << "Font Loaded!\n";

	// draw mode btn
	drawModeBtn = new btnStore::Button("Draw", { 150, 100 }, baseTextSize, sf::Color::Green, sf::Color::Black);
	drawModeBtn->setFont(font);
	drawModeBtn->setPosition({ 20,20 });
	buttonMap[drawModeBtn] = boolBtnData{ true,"Draw" };


	// lock items btn
	startEvolutionBtn = new btnStore::Button("Start", { 150, 100 }, baseTextSize, sf::Color::Green, sf::Color::Black);
	startEvolutionBtn->setFont(font);
	startEvolutionBtn->setPosition({ 190,20 });
	buttonMap[startEvolutionBtn] = boolBtnData{ false,"Start" };

}

void gameOfLife::addInfoText()
{
	//title
	this->title.setFont(this->font);
	this->title.setString("GAME OF LIFE");
	this->title.setCharacterSize(this->baseTextSize + 40);
	this->title.setFillColor(sf::Color::Green);
	title.setPosition({ 460,30 });

	this->stats = new sf::Text;
	this->stats->setFont(this->font);
	this->stats->setCharacterSize(this->baseTextSize );
	this->stats->setFillColor(sf::Color::Blue);
	this->stats->setPosition({ 50,500 });

}

