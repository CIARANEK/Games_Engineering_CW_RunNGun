#include "stdafx.h"
#include "Game.h"

void Game::Start(void)
{
	if (gameState != Unitialized)
		return;

	mainWindow.create(sf::VideoMode(1024, 768, 32), "Run N Gun");
	gameState = Game::Playing;

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
	sf::Event currentEvent;
	while (mainWindow.pollEvent(currentEvent))
	{
		switch (gameState)
		{
		case Game::Playing:
		{
			mainWindow.clear(sf::Color(255, 0, 0));
			mainWindow.display();

			if (currentEvent.type == sf::Event::Closed)
			{
				gameState = Game::Exiting;
			}
			break;
		}
		}
	}
}

Game::GameState Game::gameState = Unitialized;
sf::RenderWindow Game::mainWindow;