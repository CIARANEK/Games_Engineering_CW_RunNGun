// RunNGun.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"
#include<list>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<list>
#include<tchar.h>

using namespace sf;

//Splash Screen Class
class SplashScreen
{
	public:
		void Show(sf::RenderWindow& window);
};

//Main Menu class
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

//Game class
class Game
{
	public:
		static void Start();
		static sf::RenderWindow& getWindow();

	private:
		static bool IsExiting();
		static void GameLoop();

		static void ShowSplashScreen();
		static void ShowMenu();

		enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

		static GameState _gameState;
		static sf::RenderWindow window;

	};

//Bullet class
class Bullet
{
public:
	Sprite shape;

	Bullet(Texture *texture, Vector2f pos)
	{
		this->shape.setTexture(*texture);

		this->shape.setScale(0.07f, 0.07f);

		this->shape.setPosition(pos);
	}

	~Bullet() {}
};

//Player class
class Player
{
public:
	Sprite shape;
	Texture *texture;

	int HP;
	int HPMax;

	std::vector<Bullet> bullets;

	Player(Texture *texture)
	{
		this->HPMax = 10;
		this->HP = this->HPMax;

		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setScale(0.1f, 0.1f);
	}

	~Player() {}

};

//Enemy class
class Enemy
{
public:
	Sprite shape;

	int HP;
	int HPMax;

	Enemy(Texture *texture, Vector2u windowSize)
	{
		this->HPMax = rand() % 3 + 1;
		this->HP = this->HPMax;

		this->shape.setTexture(*texture);

		this->shape.setScale(0.1f, 0.1f);

		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
	}

	~Enemy() {}
};

//Splash Screen image set & clickable
void SplashScreen::Show(sf::RenderWindow & renderwindow)
{

sf::Texture image;
if (image.loadFromFile("SplashScreen.png") != true)
{
	return;
}

sf::Sprite sprite(image);

renderwindow.draw(sprite);
renderwindow.display();

sf::Event event;
while(true)
{
	while (renderwindow.pollEvent(event))
	{
		if (event.type == sf::Event::EventType::KeyPressed
			|| event.type == sf::Event::EventType::MouseButtonPressed
			|| event.type == sf::Event::EventType::Closed)
		{
			return;
		}
	}
}
}

//Main Menu image set & clickable position
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

//Handle click on main menu
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

//Respond to main menu click
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

//Start game loop
void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	window.create(VideoMode(1024, 768), "Run N Gun", Style::Default);

	window.setFramerateLimit(60);

	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	window.close();
}

//Exiting game state
bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

//Main game loop
void Game::GameLoop()
{
	sf::Event currentEvent;
	window.pollEvent(currentEvent);

	switch (_gameState)
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
		srand(time(NULL));

		RenderWindow window(VideoMode(800, 600), "Run N Gun", Style::Default);
		window.setFramerateLimit(60);

		////Sounds////
		//Player shooting sound effect
		sf::SoundBuffer sbuffer;
		sbuffer.loadFromFile("shot.wav");
		sf::Sound shooting(sbuffer);
		shooting.setVolume(5);

		//Zombie death sound effect
		sf::SoundBuffer zbuffer;
		zbuffer.loadFromFile("zombiedeath.wav");
		sf::Sound Zdeath(zbuffer);
		Zdeath.setVolume(5);

		//Zombie spawn/generic sound effect
		sf::SoundBuffer zgen;
		zgen.loadFromFile("zombiespawn.wav");
		sf::Sound Zspawn(zgen);
		Zspawn.setVolume(5);

		//Player hit sound effect
		sf::SoundBuffer phit;
		phit.loadFromFile("playerhit.wav");
		sf::Sound PlayerHit(phit);
		PlayerHit.setVolume(5);

		//Player death sound effect
		sf::SoundBuffer pdeath;
		pdeath.loadFromFile("playerdeath.wav");
		sf::Sound PlayDeath(pdeath);
		PlayDeath.setVolume(5);

		//Background music
		sf::Music theme;
		theme.openFromFile("backgroundaudio.wav");
		theme.setLoop(true);
		theme.setVolume(5);
		theme.play();
		//// ////

		////Fonts & Textures////
		//Game font
		Font font;
		font.loadFromFile("Dosis-Light.ttf");

		//Game textures
		//Player image
		Texture playerImage;
		playerImage.loadFromFile("player.png");

		//Enemy image
		Texture enemyImage;
		enemyImage.loadFromFile("enemy.png");

		//Bullet image
		Texture bulletImage;
		bulletImage.loadFromFile("bullet.png");

		//Overlay text
		//Score text
		Text scoreText;
		scoreText.setFont(font);
		scoreText.setCharacterSize(20);
		scoreText.setFillColor(Color::White);
		scoreText.setPosition(10.f, 10.f);

		//Game over text
		Text gameOverText;
		gameOverText.setFont(font);
		gameOverText.setCharacterSize(30);
		gameOverText.setFillColor(Color::Red);
		gameOverText.setPosition(100.f, window.getSize().y / 2);
		gameOverText.setString("GAME OVER!");
		//// ////

		////Player annd enemy set up////
		//Player set up
		int score = 0;
		Player player(&playerImage);
		int shootTimer = 20;
		Text hpText;
		hpText.setFont(font);
		hpText.setCharacterSize(12);
		hpText.setFillColor(Color::White);

		//Enemy set up
		int enemySpawnTimer = 0;
		std::vector<Enemy> enemies;

		//Enemy health points
		Text eHpText;
		eHpText.setFont(font);
		eHpText.setCharacterSize(12);
		eHpText.setFillColor(Color::White);
		//// ////

		//Close game pressing Escape or the X. Both take you back to the main menu
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
					window.close();
				_gameState = Game::Exiting;
				_gameState = Game::ShowingMenu;
			}

			if (player.HP > 0)
			{
				//Player input
				//Movement
				if (Keyboard::isKeyPressed(Keyboard::W))
					player.shape.move(0.f, -10.f);
				if (Keyboard::isKeyPressed(Keyboard::A))
					player.shape.move(-10.f, 0.f);
				if (Keyboard::isKeyPressed(Keyboard::S))
					player.shape.move(0.f, 10.f);
				if (Keyboard::isKeyPressed(Keyboard::D))
					player.shape.move(10.f, 0.f);

				//Player HP text
				hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
				hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));

				//Collision with bordersof the window
				//Left side of the window
				if (player.shape.getPosition().x <= 0)
					player.shape.setPosition(0.f, player.shape.getPosition().y);
				//Right side of window
				if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
					player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
				//Top of the window
				if (player.shape.getPosition().y <= 0)
					player.shape.setPosition(player.shape.getPosition().x, 0.f);
				//Bottom of the window
				if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height)
					player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

				//Update Controls
				if (shootTimer < 15)
					shootTimer++;

				//Shooting input and timer + sound effect
				if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 20)
				{
					shooting.play();
					player.bullets.push_back(Bullet(&bulletImage, player.shape.getPosition()));
					shootTimer = 0; //reset timer
				}

				//Bullets
				for (size_t i = 0; i < player.bullets.size(); i++)
				{
					//Moving the bullet
					player.bullets[i].shape.move(20.f, 0.f);

					//Erase bullets once it hits border
					if (player.bullets[i].shape.getPosition().x > window.getSize().x)
					{
						player.bullets.erase(player.bullets.begin() + i);
						break;
					}

					//Enemy collision
					for (size_t k = 0; k < enemies.size(); k++)
					{
						if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
						{
							if (enemies[k].HP <= 1)
							{
								score += enemies[k].HPMax;
								Zdeath.play();
								//Remove enemy after death
								enemies.erase(enemies.begin() + k);
							}
							else
								//Enemy health deplete after hit
								enemies[k].HP--;

							player.bullets.erase(player.bullets.begin() + i);
							break;
						}
					}
				}

				//Enemy
				if (enemySpawnTimer < 25)
					enemySpawnTimer++;

				//Enemy spawn timer
				if (enemySpawnTimer >= 25)
				{
					//Spawn sounde effect
					Zspawn.play();
					enemies.push_back(Enemy(&enemyImage, window.getSize()));
					enemySpawnTimer = 0; //reset timer
				}

				for (size_t i = 0; i < enemies.size(); i++)
				{
					enemies[i].shape.move(-6.f, 0.f);

					if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width)
					{
						enemies.erase(enemies.begin() + i);
						break;
					}

					//Erase if spwaned out of bounds
					if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
					{

						enemies.erase(enemies.begin() + i);
						PlayerHit.play();

						//Player takes damage
						player.HP--;

						break;
					}
				}

				//Update score
				scoreText.setString("Score: " + std::to_string(score));
			}

			window.clear();

			//Background image
			sf::Texture backImage;
			backImage.loadFromFile("background.png");

			sf::Sprite background(backImage);
			window.draw(background);

			//Draw Player
			window.draw(player.shape);

			//Draw Bullets
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				window.draw(player.bullets[i].shape);
			}

			//Draw Enemy
			for (size_t i = 0; i < enemies.size(); i++)
			{
				eHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
				eHpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - eHpText.getGlobalBounds().height);
				window.draw(eHpText);
				window.draw(enemies[i].shape);
			}

			//Draw Score and HP
			window.draw(scoreText);
			window.draw(hpText);

			if (player.HP <= 0)
				window.draw(gameOverText);
			PlayDeath.play();

			window.display();
		}

		return;
	}
	}
}

//Splash Screen game state
void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(window);
	_gameState = Game::ShowingMenu;
}

//Show menu game state
void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuSelect result = mainMenu.Show(window);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

int main(int argc, TCHAR* argv[])
{
	Game::Start();
	return 0;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::window;