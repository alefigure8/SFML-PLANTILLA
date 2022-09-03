#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bala
{
	sf::Sprite _shape;
	sf::Texture _texture;
	sf::Vector2f _direction;
	float _movement_speed;
	float _distncia_max;
	
	//Private functions
	void initSprite();
	void initTexture();

public:
	//Constructor
	Bala();
	Bala(float pos_x, float pos_y, float x, float y, float degree);
	virtual ~Bala();

	//Functions
	const sf::FloatRect getBounds() const;
	sf::Vector2f getPosition();
	float getDistanciaMax();
	void update();
	void render(sf::RenderWindow& window);
};

