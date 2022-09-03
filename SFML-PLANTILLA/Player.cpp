#include "Player.h"

void Player::initSprite()
{
	_sprite.setTexture(_texture);
	_sprite.setScale(1.0f, 1.0f);
	_sprite.setPosition(200, 200);
	_sprite.setOrigin(_sprite.getLocalBounds().width/2, _sprite.getLocalBounds().height/2);
}

void Player::initTexture()
{
	//Load Texture
	if (!_texture.loadFromFile("Texture/tank1_body.png"))
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture." << std::endl;
}

// Constructor
Player::Player()
{
	// Inicar sprite
	initTexture();
	initSprite();

	// Iniciar Arma
	_arma = new Arma;
	_arma->setPosition(_sprite.getPosition().x, _sprite.getPosition().y);

	// Propiedades
	_movement_speed = 3.f;
	_attack_max = 5.f;
	_attack = _attack_max;

}

// Functions
sf::Vector2f Player::getPosition()
{
	return _sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return _sprite.getGlobalBounds();
}

sf::Vector2f Player::getUltimaPosicion()
{
	return _ultima_posicion;
}

Arma* Player::getArma()
{
	return _arma;
}

void Player::move(float x, float y)
{
	_ultima_posicion = _sprite.getPosition();
	_sprite.move(_movement_speed * x, _movement_speed * y);
	_arma->setPosition(_sprite.getPosition().x, _sprite.getPosition().y);
}

void Player::setPosition(const float x, const float y)
{
	_sprite.setPosition(x, y);
}

void Player::setRotation(float degree)
{
	_sprite.setRotation(degree);
}

Collider Player::getCollider()
{
	return Collider(_sprite);
}


void Player::updateAtacar()
{
	if (_attack < _attack_max)
		_attack += 0.2f;
}

bool Player::puedeAtacar()
{
	if (_attack >= _attack_max)
	{
		_attack = 0.f;
		return true;
	}

	return false;
}

void Player::updateArma(sf::RenderWindow& window)
{
	float armaCenterX = _arma->getPosition().x;
	float armaCenterY = _arma->getPosition().y;
	float mousePosX = sf::Mouse::getPosition(window).x;
	float mousePosY = sf::Mouse::getPosition(window).y;
	float atan = atan2( armaCenterX - mousePosX, mousePosY - armaCenterY);
	float deg = (atan / 3.14159265358979323846 * 180) + (atan > 0 ? 0 : 360);
	_arma->setRotation(abs(deg));
}

void Player::update(sf::RenderWindow& window)
{
	updateArma(window);
	_arma->update();
	updateAtacar();
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(_sprite);
	window.draw(_arma -> getArma());
}