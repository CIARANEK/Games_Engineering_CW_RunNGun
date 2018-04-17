#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow & window);
	virtual void update(float time);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f getPostion() const;
	virtual bool IsLoaded() const;

protected:
	sf::Sprite& getSprite();

private:
	sf::Sprite psprite;
	sf::Texture pimage;
	std::string pfilename;
	bool isLoaded;

};