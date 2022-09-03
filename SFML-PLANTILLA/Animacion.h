#pragma once
#include <SFML/Graphics.hpp>
class Animacion
{
public:
	sf::IntRect uvRect;
	sf::Texture _texture;
	Animacion(std::string image, sf::Vector2u imageCount);
	~Animacion();
	void update();
	sf::Vector2u getCurrentImage();
	void setCurrentImage(sf::Vector2u imageCurrent);
	
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
};

