#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Bala.h"
#include "Ladrillo.h"
#include "Arbol.h"
#include "Efectos.h"
#include "Caja.h"
#include "Mapa.h"

class Gameplay
{
private:
	sf::RenderWindow* _window;
	Mapa* _mapa;
	Player* _player;
	std::vector<Bala*> _balas;
	sf::Vector2f ultima_posicion_disparo;
	Ladrillo* _bloque_ladrillo;
	Ladrillo* _bloque_ladrillo_2;
	Caja* _bloque_caja;
	Arbol* _bloque_arbol;
	Efectos* _disparo;

	void _initWindow();
	void _initPlayer();
	Bala* _initBalas();
	void _initBloque();
	void _initEfectos();
	
public:
	//Constructor
	Gameplay();
	~Gameplay();

	//Collider
	void colliderBloqueLadrillo();
	void colliderBloqueCaja();
	//Run
	void run();
	
	//Update
	void updatePollevents();
	void updateColliders();
	void updateInput();
	void updateBalas();
	void updateEfectos();
	void update();

	//Render
	void render();
};

