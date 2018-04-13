#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{
public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState
	{
		Unitialized, ShowSplash, Paused, ShowingMenu, Playing, Exiting
	};

	static GameState gameState;
	static sf::RenderWindow mainWindow;
};

