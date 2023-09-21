//
//// constructor
//
//
////pvt func

//void gameOfLife::initWindow()
//{
//	
//
//}
//
//void gameOfLife::pollEvents()
//{
//	while (this->mainWindow->pollEvent(this->eventHandler)) {
//		switch (this->eventHandler.type) {
//
//		case sf::Event::Closed:
//			this->mainWindow->close();
//			break;
//
//		case sf::Event::Resized:
//			std::cout << "New window width: " << this->eventHandler.size.width << " New window height: " << this->eventHandler.size.height << std::endl;
//			break;
//
//		case sf::Event::TextEntered:
//			if (this->eventHandler.text.unicode < 128) {
//				printf("%c", this->eventHandler.text.unicode);
//			}
//			break;
//
//	
//
//		case sf::Event::MouseMoved:
//			if (drawModeBtn->isMouseOver(*this->mainWindow)) {
//				drawModeBtn->setBackColor(sf::Color::Magenta);
//			}
//			else {
//				drawModeBtn->setBackColor(sf::Color::Green);
//			}
//			break;
//
//		}
//	}
//}
//
//void gameOfLife::addBtns()
//{
//	std::cout << "Add btns  \n";
//	// Font
//	sf::Font font;
//	if (!font.loadFromFile("arial.ttf"))
//		std::cout << "Font not found!\n";
//	else
//		std::cout << "Font  found!\n";
//		font.loadFromFile("arial.ttf");
//	
//	
//
//
//}
//
//
//

//
//// functions
//void gameOfLife::update()
//{
//	
//}
//
//void gameOfLife::render()
//{
//	
//	// Draw game objs here
//	/*this->drawModeBtn->drawTo(this->mainWindow);*/
//	if (drawModeBtn) {	
//		
//		
//	}
//	
