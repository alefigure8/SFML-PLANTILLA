#include "Arbol.h"

Arbol::Arbol(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion) : Bloque(image, imageCount)
{
	this->set_life(0);
}
