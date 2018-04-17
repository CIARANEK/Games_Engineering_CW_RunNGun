#pragma once
#include "GameObjects.h"

class player :
	public GameObject
{
public:
	player();
	~player();

	void update(float time);
	void draw(sf::RenderWindow& rw);

	float getVelocity() const;

private:
	//left + right
	float velocity;  
	float maxVelocity;
};