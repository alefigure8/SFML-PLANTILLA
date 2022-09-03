#include "Mapa.h"

Mapa::Mapa()
{
	//_map = new sf::String[28]{
  /*      "000000000000000000000000000000",
        "00                          00",
        "00                          00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  112211  11  11  00",
        "00  11  11  112211  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11          11  11  00",
        "00  11  11          11  11  00",
        "00          11  11          00",
        "00          11  11          00",
        "0011  1111          1111  1100",
        "0022  1111          1111  2200",
        "00          11  11          00",
        "00          111111          00",
        "00  11  11  111111  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11  11  11  11  11  00",
        "00  11  11          11  11  00",
        "00  11  11          11  11  00",
        "00  11  11   1111   11  11  00",
        "00           1  1           00",
        "00           1  1           00",
        "000000000000000000000000000000",
    };*/

	//Medidas mapa y struct.
	//For 0 en adelante asignarle las posiciones con el grid
	
	_grid = sf::Vector2f(80, 60);

    initMapa();

}

Mapa::~Mapa()
{
}

Bloque* Mapa::getTile(int i, int j)
{
    return _tile[i][j];
}


void Mapa::initMapa()
{
	int cant = 0;
	
    for (int i = 0; i < HEIGHT_MAP; i++)
    {
       for (int j = 0; j < WIDTH_MAP; j++)
        {
            switch (_map[i][j])
            {
            case '0':
                _tile[i][j] = new Ladrillo("Texture/house_1_x_5.png", sf::Vector2u(5, 1));
                break;
            case '1':
                _tile[i][j] = new Ladrillo("Texture/house_2_x_5.png", sf::Vector2u(5, 1));
                break;
            case '2':
                _tile[i][j] = new Ladrillo("Texture/house_3_x_5.png", sf::Vector2u(5, 1));
                break;
            case '3':
                _tile[i][j] = new Ladrillo("Texture/house_4_x_5.png", sf::Vector2u(5, 1));
                break;
            case ' ':
                _tile[i][j] = new Arbol("Texture/void.png", sf::Vector2u(1, 1));
                break;
			case '4':
				_tile[i][j] = new Ladrillo("Texture/street_1.png", sf::Vector2u(1, 1));
				break;
            case '5':
                _tile[i][j] = new Base("Texture/cuartel_1_x_4.png", sf::Vector2u(10, 1));//Clase Base
                break;
            case '6':
                _tile[i][j] = new Ladrillo("Texture/house_5_x_5.png", sf::Vector2u(5, 1));//Clase Base
                break;
            case '7':
                _tile[i][j] = new Ladrillo("Texture/house_6_x_5.png", sf::Vector2u(5, 1));//Clase Base
                break;
            case '8':
                _tile[i][j] = new Ladrillo("Texture/house_7_x_5.png", sf::Vector2u(5, 1));//Clase Base
                break;
            default:
                break;
            }
	
            _tile[i][j]->setPosition({ j * _grid.x, i  * _grid.y }); //Grid i y grid j
            _tile[i][j]->setScale({ 1.25f, 1.25f });

            if (i == 0 || i == WIDTH_MAP - 1)
                _tile[i][j]->setAngle(180.f);
        }
    }
	
}

void Mapa::update()
{
    for (int i = 0; i < HEIGHT_MAP; i++)
    {
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			_tile[i][j]->update();
		}

    }
}

void Mapa::render(sf::RenderWindow& window)
{
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			_tile[i][j]->render(window);
		}
	}
}

int Mapa::getHeight()
{
    return HEIGHT_MAP;
}

int Mapa::getWidth()
{
    return WIDTH_MAP;
}

