#include "SFML/sfml.h"
#include "Player.h"
#include "Game.h"

player::player() :
	velocity(0),
	maxVelocity(600.0f)
{
	load("Player.png");
	assert(IsLoaded());

	getSprite().setOrigin(getSprite().getScale().x / 2, getSprite().getScale().y / 2);
}

player::~player()
{

}

void player::draw(sf::RenderWindow & rw)
{
	GameObject::draw(rw);
}

float player::getVelocity() const
{
	return velocity;
}

void player::update(float time)
{ 
	if (Game::getInput().isKeyPressed(sf::Keyboard::Left))
	{
		velocity -= 3.0f;
	}
	if (Game::getInput().isKeyPressed(sf::Keyboard::Right))
	{
		velocity += 3.0f;
	}
	if (Game::getInput().isKeyPressed(sf::Keyboard::Down))
	{
		velocity = 0.0f;
	}
	if (velocity > maxVelocity)
		velocity = maxVelocity;

	if (velocity < -maxVelocity)
		velocity = -maxVelocity;

	sf::Vector2f pos = this->getPostion();

	if (pos.x < getSprite().getScale().x / 2
		|| pos.x >(Game::SCREEN_WIDTH - getSprite().getScale().x / 2))
	{
		velocity = -velocity;
	}
	getSprite().move(velocity * time, 0);
}