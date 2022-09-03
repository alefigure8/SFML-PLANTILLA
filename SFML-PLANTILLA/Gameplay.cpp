#include "Gameplay.h"
#include <iostream>
#include<list> 
#include <string>
#include "SFML/Graphics.hpp"


// TODO enum con sprites


void Gameplay::_initWindow()
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game test", sf::Style::Close | sf::Style::Titlebar);
	_window->setFramerateLimit(60);
	_window->setVerticalSyncEnabled(false);
}

void Gameplay::_initPlayer()
{
	_player = new Player();
}

Bala* Gameplay::_initBalas()
{
	float PI = 3.14;
	float degree = _player->getArma()->getRotationArma();
	
	// Angulo de la bala
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion de la bala
	float armaPosicionx = _player->getArma()->getPosition().x + (_player->getArma()->getBounds().width / 2 * velx);
	float armaPosiciony = _player->getArma()->getPosition().y + (_player->getArma()->getBounds().height / 2 * vely);
	
	return new Bala(armaPosicionx, armaPosiciony, velx, vely, degree - 180);
}

void Gameplay::_initBloque() //Vectores
{
	//PAsar a Nivel. Crear clase Collider con checkCollision
	_mapa = new Mapa;
	_bloque_caja = new Caja("Texture/truck2b_destroyed.png", sf::Vector2u(1, 1));
	_bloque_caja->setPosition({ 200, 300 });
	_bloque_arbol = new Arbol("Texture/treeGreen_large.png", sf::Vector2u(1, 1));
	_bloque_arbol->setPosition({ 100, 150 });
}

void Gameplay::_initEfectos()
{
	_disparo = new Efectos("Texture/shotThin.png");
}

Gameplay::Gameplay()
{
	_initWindow();
	_initPlayer();
	_initBloque();
	_initEfectos();
}

Gameplay::~Gameplay()
{
	delete _window;

	delete _player;

	for (auto* i : _balas)
	{
		delete i;
	}

	delete _disparo;
}

void Gameplay::run()
{
	// Game Loop
	while (_window->isOpen())
	{
		updatePollevents();
		update();
		render();
	}
}

void Gameplay::updatePollevents()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
	}
}

void Gameplay::updateInput()
{
	//Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_player->move(0.f, -0.4f);
		_player->setRotation(0);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_player->move(0.f, 0.4f);
		_player->setRotation(180);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_player->move(-0.4f, 0.f);
		_player->setRotation(-90);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_player->move(0.4f, 0.f);
		_player -> setRotation(90);
	}

	// Balas
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _player->puedeAtacar())
	{
		_balas.push_back(_initBalas());
		
		// Posicion desde la que disparo el tanque
		ultima_posicion_disparo = {_player->getArma()->getPosition().x, _player->getArma()->getPosition().y};

		//Iniciar efecto
		_disparo->setEstado(true);
	}
}

void Gameplay::updateBalas()
{
	bool balaBorrada = false;
	
	for (int j = 0; j < _mapa->getHeight(); j++) // cada Casa
	{
		for(int h = 0; h < _mapa->getWidth(); h++)
		{
			for (int i = 0; i < _balas.size(); i++) //cada Bala
			{
				// Movimiento bala
				_balas[i]->update();

				//Distancia de la bala
				float balaX = _balas[i]->getPosition().x; //Posicion X de la bala
				float balaY = _balas[i]->getPosition().y; //Posicion Y de la bala
				float distx = ultima_posicion_disparo.x - balaX;
				float disty = ultima_posicion_disparo.y - balaY;
				float distx2 = distx * distx;
				float disty2 = disty * disty;
				float dxy2 = distx2 + disty2;
				float dxy = sqrt(dxy2);

				if (
					_balas[i]->getBounds().intersects(_mapa->getTile(j, h)->getBounds()) &&
					!balaBorrada && 
					_mapa->getTile(j, h)->getLife() > 0
					) // Colision Edificios
				{
					std::cout << "Disparo" << std::endl;
					delete _balas.at(i);
					_balas.erase(_balas.begin() + i);
					balaBorrada = true;

					_mapa->getTile(j, h)->set_life(_mapa->getTile(j, h)->getLife() - 1);
				}
				else if (_balas[i]->getBounds().intersects(_bloque_caja->getBounds()) && !balaBorrada) // Colision con caja
				{
					delete _balas.at(i);
					_balas.erase(_balas.begin() + i);
					balaBorrada = true;

					_bloque_caja->set_life(_bloque_caja->getLife() - 1);
				}
				else if (_balas[i]->getBounds().top > _window->getSize().y ||
					_balas[i]->getBounds().top + _balas[i]->getBounds().height < 0.f ||
					_balas[i]->getBounds().left + _balas[i]->getBounds().width > _window->getSize().x ||
					_balas[i]->getBounds().left + _balas[i]->getBounds().width < 0.f ||
					dxy > _balas[i]->getDistanciaMax()
					&& !balaBorrada)
				{
					delete _balas.at(i);
					_balas.erase(_balas.begin() + i);
					balaBorrada = true;
				}

			}
		}
	}
}


//Collider bloque
void Gameplay::updateColliders()
{
	Collider c = _player->getCollider();
	Collider c2 = _bloque_caja->getCollider();
	
	for (int i = 0; i < _mapa->getHeight(); i++)
	{
		for (int j = 0; j < _mapa->getWidth(); j++)
		{
			if (_mapa->getTile(i, j)->getLife() > 0)
			{
				//Si la casa tiene vida, detiene al camion y a nosotros
				_mapa->getTile(i, j)->getCollider().CheckCollision(c, 1.f);

				if (_mapa->getTile(i, j)->getCollider().CheckCollision(c2, 1.f))
				{
					_bloque_caja->getCollider().CheckCollision(c, 1.f);
				}
				else
				{
					_bloque_caja->getCollider().CheckCollision(c, 0.5f);
				}
			}
			else
			{
				//Si la casa no tiene vida, podemos seguir moviendonos y al camion
				_bloque_caja->getCollider().CheckCollision(c, 0.5f);
			}
		}
	}
	
}

void Gameplay::updateEfectos()
{
	// Manejar tiempo de efecto
	float _disparo_tiempo = _disparo->getTime();

	if (_disparo->getTime() < _disparo->getTimeMax())
	{
		_disparo_tiempo += 1.f;
		_disparo->setTime(_disparo_tiempo);
	}
		
	if (_disparo->getTime() >= _disparo->getTimeMax())
	{
		_disparo->setTime(0.f);
		_disparo->setEstado(false);
	}
	
	float PI = 3.14;
	float degree = _player->getArma()->getRotationArma();

	// Angulo del arma
	float velx = sin((PI / 180) * -degree);
	float vely = cos((PI / 180) * -degree);

	// Posicion del arma
	float armaPosicionx = _player->getArma()->getPosition().x + (_player->getArma()->getBounds().width / 2 * velx);
	float armaPosiciony = _player->getArma()->getPosition().y + (_player->getArma()->getBounds().height / 2 * vely);

	_disparo->setPosition({ armaPosicionx, armaPosiciony});
	_disparo->setRotation(degree);
}

void Gameplay::update()
{
	//Inputs
	updateInput();

	//Balas
	updateBalas();
	
	//Player
	_player->update(*_window);	

	//Bloque
	_bloque_caja->update();
	_bloque_arbol->update();

	//Colliders
	updateColliders();
	
	//Efectos
	updateEfectos();

	_mapa->update();
}

void Gameplay::render()
{
	// Clear
	_window->clear();

	//Mapa
	_mapa->render(*_window);

	//Bloque Caja
	if (_bloque_caja->getLife() > 0) // PROVISORIO. TODO VECTOR CAJAS Y BORRAR OBJETOS
	{
		_bloque_caja->render(*_window);
	}

	//Player
	_player->render(*_window);

	//Bullets
	for (auto* bala : _balas)
	{
		bala->render(*_window);
	}
	
	//Efectos
	if (_disparo->getEstado())
	{
		_disparo->render(*_window);
	}
	
	//Bloque Arbol
	_bloque_arbol->render(*_window);

	//Display
	_window->display();
}