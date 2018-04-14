#include "MainMenu.h"
#include <SFML/sfml.h>

MainMenu::MenuSelect MainMenu::Show(sf::RenderWindow& window)
{
	//Load Main menu image
	sf::Texture image;
	image.loadFromFile("MainMenu.png");
	sf::Sprite sprite(image);

	//Set clickable areas of main menu image

	//Play clickable menu area
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.height = 380;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.action = Play;

	//Exit clickable menu area
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.rect.top = 383;
	exitButton.rect.height = 560;
	exitButton.action = Exit;

	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuSelect MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = menuItems.begin(); it != menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.height > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width > x)
		{
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuSelect MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}
