#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class Arma
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;

	void initSprite();
	void initTexture();

public:
	//Constructir
	Arma();

	//Gets
	sf::Vector2f getPosition();
	const sf::FloatRect getBounds() const;
	sf::Sprite getArma();
	float getRotationArma();
	sf::Vector2f getOriginArma();

	//Sets
	void setPosition(const float x, const float y);
	void setRotation(float degree);

	void move(float x, float y);

	void update();

	void render(sf::RenderWindow& window);
};

