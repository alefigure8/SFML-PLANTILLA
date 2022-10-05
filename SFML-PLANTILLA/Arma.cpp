#include "Arma.h"

void Arma::initTexture()
{
	//Load Texture
	if (!_texture.loadFromFile("Texture/tank1_gun.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

void Arma::initSprite()
{
	_sprite.setTexture(_texture);
	_sprite.setScale(1.0f, -1.0f);
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
}

Arma::Arma()
{
	initTexture();
	initSprite();
}

// Functions
sf::Vector2f Arma::getPosition()
{
	return _sprite.getPosition();
}

const sf::FloatRect Arma::getBounds() const
{
	return _sprite.getGlobalBounds();
}

sf::Sprite Arma::getArma()
{
	return _sprite;
}

float Arma::getRotationArma()
{
	return _sprite.getRotation();
}

sf::Vector2f Arma::getOriginArma()
{
	return _sprite.getOrigin();
}

void Arma::setPosition(const float x, const float y)
{
	_sprite.setPosition(x, y);
}

void Arma::setRotation(float degree)
{
	_sprite.setRotation(degree);
}

void Arma::move(float x, float y)
{
	_sprite.rotate(x);
}

void Arma::update()
{

}

void Arma::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
}