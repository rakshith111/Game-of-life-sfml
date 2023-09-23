#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
namespace btnStore {

	class Button {
	public:
			Button(const std::string& btnText, const sf::Vector2f& buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) :

			button(buttonSize),
			btnWidth(static_cast<int>(buttonSize.x)),
			btnHeight(static_cast<int>(buttonSize.y)) 
		{
			button.setFillColor(bgColor);
			text.setString(btnText);
			text.setCharacterSize(charSize);
			text.setFillColor(textColor);
		}

		//render func
		void drawTo(sf::RenderWindow& window) {
			window.draw(button);
			window.draw(text);
		}
		// functions
		void setBackColor(sf::Color color) {
			button.setFillColor(color);
		}

		void setFont(const sf::Font& font) {
			std::cout << "Font set : " << font.getInfo().family << std::endl;
			text.setFont(font);
		}

		void setTextColor(sf::Color color) {
			text.setFillColor(color);
		}

		void setPosition(const sf::Vector2f& point) {
			button.setPosition(point);
			sf::FloatRect textBounds = text.getLocalBounds();
			float xPos = point.x + btnWidth / 2.0f - textBounds.width / 2.0f;
			float yPos = point.y + btnHeight / 2.2f - textBounds.height / 2.0f;
			text.setPosition(xPos, yPos);
		}
		// for mouse events
		bool isMouseOver(sf::RenderWindow& window, sf::View& view) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePosition, view);
			sf::Vector2f buttonPosition = button.getPosition();
			sf::Vector2f buttonSize = button.getSize();

			return (worldMousePos.x >= buttonPosition.x && worldMousePos.x <= buttonPosition.x + buttonSize.x &&
				worldMousePos.y >= buttonPosition.y && worldMousePos.y <= buttonPosition.y + buttonSize.y);
		}

	private:
		sf::RectangleShape button;
		sf::Text text;
		int btnWidth;
		int btnHeight;
	};
}