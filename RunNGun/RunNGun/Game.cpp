#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

void Game::Start(void)
{
	if (gameState != Unitialized)
		return;

	mainWindow.create(sf::VideoMode(1024, 768, 32), "Run N Gun");
	gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	mainWindow.close();
}

bool Game::IsExiting()
{
	if (gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	switch (gameState)
	{
	case Game::ShowingMenu:
	{
		ShowMenu();
		break;
	}
	case Game::ShowingSplash:
	{
		ShowSplashScreen();
		break;
	}
	case Game::Playing:
	{
		sf::Event currentEvent;
		while (mainWindow.pollEvent(currentEvent))
		{
			mainWindow.clear(sf::Color(255, 0, 0));
			mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) gameState =
				gameState = Game::Exiting;
			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
			}
		}
		break;
	}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(mainWindow);
	gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuSelect result = mainMenu.Show(mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		gameState = Game::Playing;
		break;
	}
}
