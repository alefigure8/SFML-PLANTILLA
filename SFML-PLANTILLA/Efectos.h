#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class Efectos
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	float _timeMax;
	float _time;
	bool _estado;

	void initTexture(std::string texture);
	void initSprite();



public:
	Efectos(std::string texture);

	//getter
	float getTime();
	float getTimeMax();
	sf::Vector2f getPosition();
	bool getEstado();
	float getRotation();

	//setter
	void setTime(float time);
	void setTimeMax(float time);
	void setPosition(sf::Vector2f);
	void setEstado(bool estado);
	void setRotation(float deg);

	//update
	void update();

	//render
	void render(sf::RenderWindow& window);
};