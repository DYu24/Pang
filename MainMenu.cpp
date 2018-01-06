#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MenuResult MainMenu::show(sf::RenderWindow& renderWindow) {
	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("images/MainMenu.png");
	sf::Sprite sprite(texture);

	//Set up clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect = sf::Rect<int>(0, 145, 1023, 235);
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect = sf::Rect<int>(0, 383, 1023, 177);
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	renderWindow.draw(sprite);
	renderWindow.display();

	return getMenuResponse(renderWindow);
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y) {
	std::list<MenuItem>::iterator itr;

	for (itr = _menuItems.begin(); itr != _menuItems.end(); itr++) {
		sf::Rect<int> menuItemRect = itr->rect;
		if (menuItemRect.contains(x, y))
			return itr->action;
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& renderWindow) {
	sf::Event menuEvent;

	while (true) {
		while (renderWindow.pollEvent(menuEvent)) {
			if (menuEvent.type == sf::Event::MouseButtonPressed)
				return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			if (menuEvent.type == sf::Event::Closed)
				return Exit;
		}
	}
}