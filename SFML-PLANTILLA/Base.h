#pragma once
#include "Bloque.h"

class Base :
	public Bloque
{
public:
	Base(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion = { 300.f, 300.f });
};

