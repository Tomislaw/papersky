// Klasa zajmuj¹ca siê ca³¹ map¹ gry -> tilemap + byty

/*
Uaktualnia byty z entitylist
void update(float &delta_time);

Rysuje ca³¹ mape i byty
void draw(sf::RenderWindow &window);

Rysuje mape i gracza w konsoli
void drawInConsole()

Zajmuje siê wydarzeniami z klawiatury
void handle_event(sf::Event &handleevent);
*/

#ifndef MAP_H
#define MAP_H
#include "TileMap.h"
#include "Entity\player.h"
#include "cursor.hpp"
#include "EntityList.h"
class Map
{
public:
	Map();
	~Map();

	void update(float &delta_time);
	void draw(sf::RenderWindow &window);
	void drawInConsole()
	{
		tile2.drawInConsole(entities.get_player_position());
	}
	void handle_event(sf::Event &handleevent);


private:
	sf::View cameraview;
	//Entity test;
	TileMap tile2;
	EntityList entities;
	Cursor cursor;
	void update_view_position(sf::Vector2f pos);
};

#endif