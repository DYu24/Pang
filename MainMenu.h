#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>

class MainMenu
{
public:
	enum MenuResult { Nothing, Exit, Play };

	struct MenuItem {
	public:
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult show(sf::RenderWindow& renderWindow);

private:
	MenuResult getMenuResponse(sf::RenderWindow& renderWindow);
	MenuResult handleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};

