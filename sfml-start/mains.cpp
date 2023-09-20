#include <iostream>
#include "button.h"



int main() {
	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(900, 900), "SFML Textbox", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";

	/*Textbox text1(20, sf::Color::White, true);
	text1.setPosition({200, 100 });
	text1.setLimit(true, 30);
	text1.setFont(font);*/

	Button btn1("Enter", { 100, 100 }, 30, sf::Color::Green, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition({ 10, 10 });



	//Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		//	text1.setSelected(true);
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		//	text1.setSelected(false);
		//}

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
	
			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(window)) {
					btn1.setBackColor(sf::Color::Magenta);
				}
				else {
					btn1.setBackColor(sf::Color::Green);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (btn1.isMouseOver(window)) {
					std::cout << "Hello " << "\n";
				}
			}
		}
		window.clear();
		
		btn1.drawTo(window);
		window.display();
	}
}