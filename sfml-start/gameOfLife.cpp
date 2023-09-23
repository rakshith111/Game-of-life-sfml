#include"gameOfLife.h"
#include "btn.h"
#include <iostream>
#include<sstream>

//constructor
gameOfLife::gameOfLife()
	: mainWindow(nullptr),
	drawModeBtn(nullptr),
	startEvolutionBtn(nullptr),
	stats(nullptr)
{
	std::cout << "Base constructor \n";
	this->initVars(); // Initialize the other variables in the constructor body
	this->initWindow();
	this->addBtns();
	this->addInfoText();
}

//destructor
gameOfLife::~gameOfLife()
{
	std::cout << "Close window \n";

	// Check if these objects are not nullptr before deleting them
	if (mainWindow) {
		delete this->mainWindow;
		this->mainWindow = nullptr;
	}

	if (stats) {
		delete this->stats;
		this->stats = nullptr;
	}

	if (drawModeBtn) {
		delete drawModeBtn;
		drawModeBtn = nullptr;
	}

	if (startEvolutionBtn) {
		delete startEvolutionBtn;
		startEvolutionBtn = nullptr;
	}
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


	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";
	else
		std::cout << "Font Loaded!\n";

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
				bool isMouseOver = pair.first->isMouseOver(*this->mainWindow, this->gridView);
				if (isMouseOver && !pair.second.hover) {
					pair.second.hover = true;
					pair.first->setBackColor(sf::Color::Magenta);
				}
				else if (!isMouseOver && pair.second.hover) {
					pair.second.hover = false;
					setButtonBackgroundColor(pair.first, pair.second.state);
				}
			}
			break;

		case sf::Event::MouseButtonPressed:
			if (this->eventHandler.mouseButton.button == sf::Mouse::Left) {
				// Print the mouse position
				std::cout << "Mouse Position: x = " << this->mousePosWindow.x << ", y = " << this->mousePosWindow.y << std::endl;
			}
			for (auto& pair : buttonMap) {
				if (pair.first->isMouseOver(*this->mainWindow, this->gridView)) {
					pair.second.state = !pair.second.state;
					std::cout << "Button pressed: " << pair.second.btnName << " State: " << pair.second.state << "\n";
				}
			}
			break;

		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Left
			{
				std::cout << "Left ";
				this->gridView.move(-viewSpeed * dt * 5, 0.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Right
			{
				this->gridView.move(viewSpeed * dt * 5, 0.f);
				std::cout << "Right ";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // UP
			{
				this->gridView.move(0.f, -viewSpeed * dt * 5);
				std::cout << "UP ";
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Down
			{
				this->gridView.move(0.f, viewSpeed * 5 * dt);
				std::cout << "Down ";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // Reset
			{
				std::cout << "\n Reset ";
				// Reset the gridView
				this->gridView.setSize(this->mainWindow->getSize().x, this->mainWindow->getSize().y);
				this->gridView.setCenter(this->mainWindow->getSize().x / 2.0f, this->mainWindow->getSize().y / 2.0f);
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
	this->mainWindow->setView(this->gridView);

	drawModeBtn->drawTo(*this->mainWindow);
	startEvolutionBtn->drawTo(*this->mainWindow);
	this->mainWindow->draw(title);


	this->mainWindow->setView(this->mainWindow->getDefaultView());
	// will add it to the screen than the windo usefull for pinning stuff to screen
	this->mainWindow->draw(*this->stats);


	this->mainWindow->display();

}

void gameOfLife::addBtns()
{


	// draw mode btn
	drawModeBtn = new btnStore::Button("Draw", { 150, 100 }, baseTextSize, sf::Color::Green, sf::Color::Black);
	drawModeBtn->setFont(font);
	drawModeBtn->setPosition({ 20,20 });
	buttonMap[drawModeBtn] = boolBtnData{ true,false,"Draw" };


	// lock items btn
	startEvolutionBtn = new btnStore::Button("Start", { 150, 100 }, baseTextSize, sf::Color::Green, sf::Color::Black);
	startEvolutionBtn->setFont(font);
	startEvolutionBtn->setPosition({ 190,20 });
	buttonMap[startEvolutionBtn] = boolBtnData{ false,false,"Start" };

	setButtonBackgroundColor(startEvolutionBtn, buttonMap[startEvolutionBtn].state);
	setButtonBackgroundColor(drawModeBtn, buttonMap[drawModeBtn].state);

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
	this->stats->setCharacterSize(this->baseTextSize);
	this->stats->setFillColor(sf::Color::Blue);
	this->stats->setPosition({ 50,500 });

}

void gameOfLife::setButtonBackgroundColor(btnStore::Button* button, bool state)
{
	sf::Color bgColor = state ? sf::Color::Green : sf::Color::Red;
	std::cout << "color set " << bgColor.toInteger() << "\n";
	button->setBackColor(bgColor);
}

