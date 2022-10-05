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

void Gameplay::_initBloque()
{
	//PAsar a Nivel. Crear clase Collider con checkCollision
	_bloque_ladrillo = new Ladrillo("Texture/house_1_x_4.png", sf::Vector2u(4, 1));
	_bloque_ladrillo->setPosition({ 400, 400 });
	_bloque_ladrillo->setScale({ 1.5f, 1.5f });
	_bloque_ladrillo_2 = new Ladrillo("Texture/house_3_x_4.png", sf::Vector2u(4, 1));
	_bloque_ladrillo_2->setPosition({ 500, 400 });
	_bloque_ladrillo_2->setScale({ 1.5f, 1.5f });
	_bloque_caja = new Caja("Texture/truck2b_destroyed.png", sf::Vector2u(1, 1));
	_bloque_caja->setPosition({ 200, 300 });
	_bloque_arbol = new Arbol("Texture/treeGreen_large.png", sf::Vector2u(1, 1));
	_bloque_arbol->setPosition({ 100, 150 });
	_bloque_arbol->setScale({ 0.5f, 0.5f });

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

	for (int i = 0; i < _balas.size(); i++)
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

		if (_balas[i]->getBounds().intersects(_bloque_caja -> getBounds()) && !balaBorrada) // Colision con caja
		{
			delete _balas.at(i);
			_balas.erase(_balas.begin() + i);
			balaBorrada = true;

			_bloque_caja->set_life(_bloque_caja->getLife() - 1);
		}
		else if (_balas[i]->getBounds().intersects(_bloque_ladrillo->getBounds()) && !balaBorrada) // Colision ladrillo
		{
			delete _balas.at(i);
			_balas.erase(_balas.begin() + i);
			_bloque_ladrillo->set_life(_bloque_ladrillo->getLife() - 1);
			balaBorrada = true;
		}
		else if (_balas[i]->getBounds().intersects(_bloque_ladrillo_2->getBounds()) && !balaBorrada) // Colision ladrillo
		{
			delete _balas.at(i);
			_balas.erase(_balas.begin() + i);
			_bloque_ladrillo_2->set_life(_bloque_ladrillo_2->getLife() - 1);

			balaBorrada = true;
		}
		else if (_balas[i]->getBounds().top  > _window->getSize().y || 
			_balas[i]->getBounds().top + _balas[i]->getBounds().height < 0.f || 
			_balas[i] -> getBounds().left + _balas[i]->getBounds().width > _window->getSize().x ||
			_balas[i]->getBounds().left + _balas[i]->getBounds().width < 0.f ||
			dxy > _balas[i] -> getDistanciaMax()
			&& !balaBorrada
			)
		{
			delete _balas.at(i);
			_balas.erase(_balas.begin() + i);
			balaBorrada = true;
		}
	}
}

void Gameplay::colliderBloqueLadrillo()
{
	//PLAYER  COLLIDER LADRILLO
	if (_player->getBounds().intersects(_bloque_ladrillo->getBounds()) && _bloque_ladrillo -> getLife() != 4) //Si la casa está rota pasa por encima
	{
		if (_player->getUltimaPosicion().y + (_player->getBounds().height / 2.f) <= _bloque_ladrillo->getBounds().top)
		{
			_player->setPosition(_player->getPosition().x, _bloque_ladrillo->getPosition().y - (_player->getBounds().height / 2));
		}

		else if (_player->getUltimaPosicion().y - (_player->getBounds().height / 2.f) >= _bloque_ladrillo->getBounds().top + _bloque_ladrillo->getBounds().height)
		{
			_player->setPosition(_player->getPosition().x, _bloque_ladrillo->getPosition().y + _bloque_ladrillo->getBounds().height + (_player->getBounds().height / 2));
		}

		else if (_player->getUltimaPosicion().x + (_player->getBounds().width / 2.f) <= _bloque_ladrillo->getBounds().left)
		{
			_player->setPosition(_bloque_ladrillo->getPosition().x - (_player->getBounds().width / 2.f), _player->getPosition().y);

		}

		else if (_player->getUltimaPosicion().x - (_player->getBounds().width / 2.f) >= _bloque_ladrillo->getBounds().left + _bloque_ladrillo->getBounds().width)
		{
			_player->setPosition((_bloque_ladrillo->getPosition().x + _bloque_ladrillo->getBounds().width) + (_player->getBounds().width / 2.f), _player->getPosition().y);

		}
	}

}

void Gameplay::colliderBloqueCaja()
{
	//PLAYER  COLLIDER CAJA
	if (_player->getBounds().intersects(_bloque_caja->getBounds()))
	{
		// PLAYER ARRIBA
		if (_player->getUltimaPosicion().y + (_player->getBounds().height / 2.f) < _bloque_caja->getBounds().top)
		{	
			_player->setPosition(_player->getPosition().x, _bloque_caja->getPosition().y - (_player->getBounds().height / 2));

			if (!_bloque_caja->getBounds().intersects(_bloque_ladrillo->getBounds()))
			{
				_bloque_caja->move(0.f, 0.5f);
			}
			else
			{
				// SI HAY COLISION CON LADRILLO Y TANQUE SE FREANAN TODOS // TODO MEJORAR!
				_bloque_caja->setPosition(_bloque_caja->getUltimaPosicion() - sf::Vector2f(0.f, 0.5f));
				_player->move(0.f, -1.5f);
			}
		}
		// PLAYER ABAJO
		else if (_player->getUltimaPosicion().y - (_player->getBounds().height / 2.f) >= _bloque_caja->getBounds().top + _bloque_caja->getBounds().height)
		{
			_player->setPosition(_player->getPosition().x, _bloque_caja->getPosition().y + _bloque_caja->getBounds().height + (_player->getBounds().height / 2));
			
			if (!_bloque_caja->getBounds().intersects(_bloque_ladrillo->getBounds()))
			{
				_bloque_caja->move(0.f, -0.5f);
			}
			else
			{
				_bloque_caja->setPosition(_bloque_caja->getUltimaPosicion() - sf::Vector2f(0.f, 0.5f));
				_player->move(0.f, 1.5f);
			}
		}
		// PLAYER IZQUIERDA
		else if (_player->getUltimaPosicion().x + (_player->getBounds().width / 2.f) <= _bloque_caja->getBounds().left)
		{
			_player->setPosition(_bloque_caja->getPosition().x - (_player->getBounds().width / 2.f), _player->getPosition().y);
			
			if (!_bloque_caja->getBounds().intersects(_bloque_ladrillo->getBounds()))
			{
				_bloque_caja->move(0.5f, 0.f);
			}
			else
			{
				_bloque_caja->setPosition(_bloque_caja->getUltimaPosicion() - sf::Vector2f(0.5f, 0.f));
				_player->move(-1.5f, 0.f);
			}
			
		}
		// PLAYER DERECHA
		else if (_player->getUltimaPosicion().x - (_player->getBounds().width / 2.f) >= _bloque_caja->getBounds().left + _bloque_caja->getBounds().width)
		{
			_player->setPosition((_bloque_caja->getPosition().x + _bloque_caja->getBounds().width) + (_player->getBounds().width / 2.f), _player->getPosition().y);
			
			if (!_bloque_caja->getBounds().intersects(_bloque_ladrillo->getBounds()))
			{
				_bloque_caja->move(-0.5f, 0.f);
			}
			else
			{
				_bloque_caja->setPosition(_bloque_caja->getUltimaPosicion() - sf::Vector2f(0.5f, 0.f));
				_player->move(1.5f, 0.f);
			}
		}
	}
}

//Collider bloque
void Gameplay::updateColliders()
{
	colliderBloqueLadrillo();
	colliderBloqueCaja();
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
	_bloque_ladrillo->update();
	_bloque_ladrillo_2->update();
	_bloque_caja->update();
	_bloque_arbol->update();

	//Colliders
	updateColliders();

	//Efectos
	updateEfectos();
}

void Gameplay::render()
{
	// Clear
	_window->clear();

	//Bullets
	for (auto* bala : _balas)
	{
		bala->render(*_window);
	}

	//Bloque Ladrillo
	_bloque_ladrillo->render(*_window);
	_bloque_ladrillo_2->render(*_window);


	//Bloque Caja
	if (_bloque_caja->getLife() > 0) // PROVISORIO. TODO VECTOR CAJAS Y BORRAR OBJETOS
	{
		std::cout << "Entro" << std::endl;
		_bloque_caja->render(*_window);
	}

	//Player
	_player->render(*_window);
	
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