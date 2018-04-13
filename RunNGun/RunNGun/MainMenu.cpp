#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuSelect MainMenu::Show(sf::RenderWindow& window)
{
	//Load Main menu image
	sf::Image image;
	image.LoadFromFile("images/Mainmenu.png");
	sf::Sprite sprite(image);

	//Set clickable areas of main menu image

	//Play clickable menu area
	MenuItem playButton;
	playButton.rect.Top = 145;
	playButton.rect.Bottom = 380;
	playButton.rect.Left = 0;
	playButton.rect.Right = 1023;
	playButton.action = Play;

	//Exit clickable menu area
	MenuItem exitButton;
	exitButton.rect.Left = 0;
	exitButton.rect.Right = 1023;
	exitButton.rect.Top = 383;
	exitButton.rect.Bottom = 560;
	exitButton.action = Exit;

	menuItems.push_back(playButton);
	menuItems.push_back(exitButton);

	window.Draw(sprite);
	window.Display();

	return GetMenuResponse(window);
}

MainMenu::MenuSelect MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = menuItems.begin(); it != menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.Bottom > y
			&& menuItemRect.Top < y
			&& menuItemRect.Left < x
			&& menuItemRect.Right > x)
		{
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuSelect MainMenu::GetMenuResponse(sf::RenderWindow& window)
{

}