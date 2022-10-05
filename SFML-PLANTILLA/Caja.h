#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Bloque.h"

class Caja 
	: public Bloque
{
private:
	sf::Vector2f _ultima_posicion;
	float _movement_speed;
	
public:
	Caja(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = { 200.f, 200.f });
	
	//getters
	sf::Vector2f getUltimaPosicion();

	//setters
	void move(float x, float y);
};


