#pragma once
#include "SFML/Graphics.hpp"
#include "Arma.h"
#include "Collider.h"
#include <iostream>
#include <cmath>

class Player
{
private:
	Arma* _arma;
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _ultima_posicion;
	float _movement_speed;
	float _attack;
	float _attack_max;

	//Private Functions
	void initSprite();
	void initTexture();

public:
	//Constructor
	Player();

	//Gets
	sf::Vector2f getPosition();
	const sf::FloatRect getBounds() const;
	sf::Vector2f getUltimaPosicion();
	Arma* getArma();

	//Sets
	void setPosition(const float x, const float y);
	void setRotation(float degree);

	//Collider
	Collider getCollider();

	//Updates
	void updateAtacar();
	void updateArma(sf::RenderWindow & window);
	void update(sf::RenderWindow& window);

	//Render
	void render(sf::RenderWindow& window);
	
	//Funciones
	bool puedeAtacar();
	void move(float x, float y);
};

