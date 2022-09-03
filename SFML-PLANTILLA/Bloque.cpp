#include "Bloque.h"

void Bloque::_initTexture(std::string image, sf::Vector2u imageCount)
{
	//Load Texture
	if (!_texture.loadFromFile(image))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

void Bloque::_initSprite()
{
	_sprite.setTexture(_texture);
}

Bloque::Bloque() : _animacion("Texture/treeGreen_large.png", sf::Vector2u(1, 1))
{
	_initTexture("Texture/treeGreen_large.png", sf::Vector2u(1, 1));
	_initSprite();
}

Bloque::Bloque(std::string image, sf::Vector2u imageCount) : _animacion(image, imageCount)
{
	_initTexture(image, imageCount);
	_initSprite();
	_life = imageCount.x;
	_max_life = imageCount.x;
}

sf::FloatRect Bloque::getBounds()
{
	return _sprite.getGlobalBounds();
}

sf::Sprite& Bloque::getSprite()
{
	return _sprite;
}

int Bloque::getLife()
{
	return _life;
}

Collider Bloque::getCollider()
{
	return Collider(_sprite);
}


sf::Vector2f Bloque::getPosition()
{
	return _sprite.getPosition();
}

void Bloque::setPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void Bloque::setScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Bloque::set_life(int life)
{
	_life = life;
}

void Bloque::setAngle(float deg)
{
	_sprite.rotate(deg);
}


void Bloque::update()
{
	// Update animacion con la vida que le queda al objeto
	if (_life <= 0)
		_life = 0;
	sf::Vector2u currentImage = _animacion.getCurrentImage();
	currentImage.x = _max_life - _life; 
	_animacion.setCurrentImage(currentImage);
	_sprite.setTextureRect(_animacion.uvRect);
	_sprite.setOrigin(_animacion.uvRect.width / 2, _animacion.uvRect.height / 2); //Cambia el origen segun el sprite
	_animacion.update();
}

void Bloque::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
}