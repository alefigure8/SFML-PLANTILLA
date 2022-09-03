#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Bloque.h"

class Arbol
	: public Bloque
{
public:
	Arbol(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = {300.f, 300.f});
};