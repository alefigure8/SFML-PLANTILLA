#include "Caja.h"

Caja::Caja(std::string image, sf::Vector2u imageCount, sf::Vector2f posicion) : Bloque(image, imageCount) {
	_movement_speed = 5.f;
}


sf::Vector2f Caja::getUltimaPosicion() {
	return _ultima_posicion;
}

void Caja::move(float x, float y) {
	_ultima_posicion = getPosition();
	getSprite().move(x * _movement_speed, y * _movement_speed);
}

