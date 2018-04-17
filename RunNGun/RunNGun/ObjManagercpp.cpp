#include "SFML/sfml.h"
#include "ObjManager.h"
#include "Game.h"

ObjManager::ObjManager()
{

}

ObjManager::~ObjManager()
{
	std::for_each(gameObjects.begin(), gameObjects.end(), GameObjDeallo());
}

void ObjManager::add(std::string name, GameObject* gameObject)
{
	gameObjects.insert(std::pair<std::string, GameObject*>(name, gameObject));
}

void ObjManager::remove(std::string name)
{
	std::map<std::string, GameObject*>::iterator res = gameObjects.find(name);
	if (res != gameObjects.end())
	{
		delete res->second;
		gameObjects.erase(res);
	}
}

GameObject* ObjManager::get(std::string name) const
{
	std::map<std::string, GameObject*>::const_iterator res = gameObjects.find(name);
	if (res == gameObjects.end())
		return NULL;
	return res->second;
}

int ObjManager::getObjCount() const
{
	return gameObjects.size();
}

void ObjManager::drawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, GameObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second->draw(renderWindow);
		itr++;
	}
}

void ObjManager::updateAll()
{
	std::map<std::string, GameObject*>::const_iterator itr = gameObjects.begin();
	sf::Time clock;
	float tDel = clock.asSeconds();

	while (itr != gameObjects.end())
	{
		itr->second->update(tDel);
		itr++;
	}
}