#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Bloque.h"

class Ladrillo 
	: public Bloque
{
public:
	Ladrillo(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = {200.f, 200.f});
};