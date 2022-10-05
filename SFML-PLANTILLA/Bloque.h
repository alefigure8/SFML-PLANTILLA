#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Animacion.h"

class Bloque
{
private:
	Animacion _animacion;
	sf::Sprite _sprite;
	sf::Texture _texture;
	int _life;
	void _initTexture(std::string image, sf::Vector2u imageCount);
	void _initSprite();

public:
	Bloque();
	Bloque(std::string image, sf::Vector2u imageCount);

	//getter
	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
	sf::Sprite& getSprite();
	int getLife();
	
	//setter
	void setPosition(sf::Vector2f position);
	void setScale(sf::Vector2f scale);
	void set_life(int life);

	//Funciones
	void update();

	void render(sf::RenderWindow& window);
};