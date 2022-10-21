#include "Bala.h"

void Bala::initSprite()
{
	_shape.setTexture(_texture);
	_shape.setOrigin(_shape.getLocalBounds().width/2, _shape.getLocalBounds().top);
}

void Bala::initTexture()
{
	if (!_texture.loadFromFile("Texture/bulletGreen1.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

Bala::Bala(float pos_x, float pos_y, float x, float y, float degree)
{
	initTexture();
	initSprite();

	_distncia_max = 120.f;
	_shape.setPosition(pos_x, pos_y);
	_shape.setScale(0.5f, 0.5f);
	_shape.setRotation(degree);
	_direction.x = x;
	_direction.y = y;
	_movement_speed = 0.05f;
}

Bala::~Bala()
{

}

const sf::FloatRect Bala::getBounds() const
{
	return _shape.getGlobalBounds();
}

sf::Vector2f Bala::getPosition()
{
	return _shape.getPosition();
}

float Bala::getDistanciaMax()
{
	return _distncia_max;
}

void Bala::update()
{
	_shape.move(_movement_speed * _direction);
}

void Bala::render(sf::RenderWindow& window)
{
	window.draw(_shape);
}
