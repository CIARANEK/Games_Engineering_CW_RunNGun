//Games Engineering Coursework
//SET09121
//Run N Gun
//Ciaran McMahon
//main.cpp

#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include"SFML\System.hpp"
#include<cstdlib>
#include "Menu.h"

#include<vector>

using namespace sf;

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(VideoMode(640, 480), "Run N Gun");
	window.setFramerateLimit(60);

	sf::RenderWindow window(sf::VideoMode(600, 600), "Run N Gun Main Menu");
	Menu menu(window.getSize().x, window.getSize().y);

	//Shapes- Will become sprites
	CircleShape bullet;
	bullet.setFillColor(Color::Red);
	bullet.setRadius(5.f);

	RectangleShape enemy;
	enemy.setFillColor(Color::Magenta);
	enemy.setSize(Vector2f(50.f, 50.f));

	CircleShape player;
	player.setFillColor(Color::White);
	player.setRadius(50.f);
	player.setPosition(window.getSize().x / 2 - player.getRadius(), window.getSize().y - player.getRadius() * 2 - 10.f);
	Vector2f playerCenter;
	int shootTimer = 0;

	std::vector<CircleShape> bullets;
	bullets.push_back(CircleShape(bullet));

	std::vector<RectangleShape> enemies;
	enemies.push_back(RectangleShape(enemy));
	int enemySpawnTimer = 0;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			//Main Menu
			sf::Event event;

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "Play button has been pressed" << std::endl;
							break;
						case 1:
							std::cout << "Option button has been pressed" << std::endl;
							break;
						case 2:
							window.close();
							break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					window.close();

					break;

				}

			}
			window.clear();

			menu.draw(window);

			window.display();
		}


		//Player
		playerCenter = Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());

		player.setPosition(Mouse::getPosition(window).x, player.getPosition().y);

		//Bullets
		if (shootTimer < 5)
			shootTimer++;

		//Shoot
		if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 5)
		{
			bullet.setPosition(playerCenter);
			bullets.push_back(CircleShape(bullet));

			shootTimer = 0;
		}

		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].move(0.f, -10.f);

			if (bullets[i].getPosition().y <= 0)
				bullets.erase(bullets.begin() + i);


			//Enemies
			if (enemySpawnTimer < 20)
				enemySpawnTimer++;

			if (enemySpawnTimer >= 20)
			{
				enemy.setPosition((rand() % int(window.getSize().x - enemy.getSize().x)), 0.f);
				enemies.push_back(RectangleShape(enemy));

				enemySpawnTimer = 0;
			}

			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].move(0.f, 5.f);

				if (enemies[i].getPosition().y > window.getSize().y)
					enemies.erase(enemies.begin() + i);
			}

			//Collision
			if (!enemies.empty() && !bullets.empty())
			{
				for (size_t i = 0; i < bullets.size(); i++)
				{
					for (size_t k = 0; k < enemies.size(); k++)
					{
						if (bullets[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
						{
							bullets.erase(bullets.begin() + i);
							enemies.erase(enemies.begin() + k);
							break;
						}
					}
				}
			}

			//Draw
			window.clear();

			window.draw(player);

			for (size_t i = 0; i < enemies.size(); i++)
			{
				window.draw(enemies[i]);
			}

			for (size_t i = 0; i < bullets.size(); i++)
			{
				window.draw(bullets[i]);
			}

			window.display();
		}

		return 0;
	}