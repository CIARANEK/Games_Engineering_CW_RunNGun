#include "SFML/sfml.h"
#include "GameObjects.h"

GameObject::GameObject()
	:isLoaded(false)
{
	
}

GameObject::~GameObject()
{

}

void GameObject::load(std::string filename)
{
	if (pimage.loadFromFile(filename) == false)
	{
		pfilename = "";
		isLoaded = false;
	}
	else
	{
		pfilename = filename;
		psprite.setTexture(pimage);
		isLoaded = true;
	}
}

void GameObject::draw(sf::RenderWindow & renderWindow)
{
	if (isLoaded)
	{
		renderWindow.draw(psprite);
	}
}

void GameObject::update(float time)
{

}

void GameObject::SetPosition(float x, float y)
{
	if (isLoaded)
	{
		psprite.setPosition(x, y);
	}
}

sf::Vector2f GameObject::getPostion() const
{
	if (isLoaded)
	{
		return psprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& GameObject::getSprite()
{
	return psprite;
}

bool GameObject::IsLoaded() const
{
	return isLoaded;
}