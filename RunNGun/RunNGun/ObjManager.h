#pragma once
#include "GameObjects.h"	

class ObjManager
{
public:
	ObjManager();
	~ObjManager();

	void add(std::string name, GameObject* gameObject);
	void remove(std::string name);
	int getObjCount() const;
	GameObject* get(std::string name) const;

	void drawAll(sf::RenderWindow& renderWindow);
	void updateAll();

private:
	std::map<std::string, GameObject*> gameObjects;

	struct GameObjDeallo
	{
		void operator()(const std::pair<std::string, GameObject*> & p) const
		{
			delete p.second;
		}
	};
};