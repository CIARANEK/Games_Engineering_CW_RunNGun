#pragma once
#include <SFML/sfml.h>
#include "Player.h"
#include "ObjManager.h"


class Game
{
public:
	static void Start();
	static sf::RenderWindow& getWindow();
	const static sf::Keyboard& getInput();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static ObjManager gameObjectsM;
};