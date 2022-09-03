#include "Animacion.h"
#include <iostream>

Animacion::Animacion(std::string image, sf::Vector2u imageCount)
{
	_texture.loadFromFile(image);
	this->imageCount = imageCount;
	currentImage.x = 0;

	uvRect.width = _texture.getSize().x / float(imageCount.x);
	uvRect.height = _texture.getSize().y / float(imageCount.y);
}

Animacion::~Animacion()
{
}

void Animacion::update()
{
	if (currentImage.x >= imageCount.x) 
		currentImage.x = imageCount.x - 1;
	
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}
sf::Vector2u Animacion::getCurrentImage()
{
	return currentImage;
}

void Animacion::setCurrentImage(sf::Vector2u imageCurrent)
{
	currentImage = imageCurrent;
}