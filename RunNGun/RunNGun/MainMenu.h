#pragma once
#include <SFML/sfml.h>
#include <list>

class MainMenu
{
public:
	enum MenuSelect { Nothing, Exit, Play };

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		MenuSelect action;
	};

	MenuSelect Show(sf::RenderWindow& window);

private:
	MenuSelect GetMenuResponse(sf::RenderWindow& window);
	MenuSelect HandleClick(int x, int y);
	std::list<MenuItem> menuItems;
};