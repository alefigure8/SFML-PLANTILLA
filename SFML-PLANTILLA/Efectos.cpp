#include "Efectos.h"

void Efectos::initSprite()
{
	_sprite.setTexture(_texture);
	_sprite.setScale(0.2f, 0.2f);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().top);
}

void Efectos::initTexture(std::string texture)
{
	//Load Texture
	if (!_texture.loadFromFile(texture))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Efectos::Efectos(std::string texture) {
	_timeMax = 10.f;
	_time = _timeMax;
	_estado = false;
	initTexture(texture);
	initSprite();
}

sf::Vector2f Efectos::getPosition()
{
	return _sprite.getPosition();
}

bool Efectos::getEstado()
{
	return _estado;
}

float Efectos::getRotation()
{
	return _sprite.getRotation();
}

float Efectos::getTime()
{
	return _time;
}

float Efectos::getTimeMax()
{
	return _timeMax;
}

void Efectos::setTime(float time)
{
	_time = time;
}

void Efectos::setTimeMax(float timeMax)
{
	_timeMax = timeMax;
}

void Efectos::setRotation(float deg)
{
	_sprite.setRotation(deg);
}

void Efectos::setEstado(bool estado)
{
	_estado = estado;
}

void Efectos::setPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void Efectos::update()
{

}

void Efectos::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
}