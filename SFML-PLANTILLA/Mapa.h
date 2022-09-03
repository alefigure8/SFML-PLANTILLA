#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bloque.h"
#include "Ladrillo.h"
#include "Arbol.h"
#include "Caja.h"
#include "Base.h"
class Mapa
{
private: 
	static const int HEIGHT_MAP = 9;
	static const int WIDTH_MAP = 12;
	Bloque* _tile[HEIGHT_MAP][WIDTH_MAP];
	char _map[HEIGHT_MAP][WIDTH_MAP] = {			 
		{'4','4','4','4','4','4','4','4','4','4','4','4'},
		{'4','7','3','1','0',' ',' ','2',' ','4',' ','4'},
		{'4','1','2',' ','0','8',' ','7',' ','3',' ','4'},
		{'4','6',' ',' ',' ',' ',' ','6',' ','1',' ','4'},
		{'4','1',' ',' ','6',' ',' ','3',' ','7','6','4'},
		{'4',' ',' ',' ',' ','8',' ',' ',' ','1',' ','4'},
		{'4','1','2',' ','0',' ',' ',' ','7','0',' ','4'},
		{'4','8',' ',' ','0',' ',' ',' ',' ','3',' ','4'},
		{'4','4','4','4','4',' ','5',' ','4','4','4','4'},
	};
	sf::Vector2f _grid;

public:
	Mapa();
	~Mapa();
	Bloque* getTile(int i, int j);
	void initMapa();
	void update();
	void render(sf::RenderWindow& window);
	int getHeight();
	int getWidth();
};

