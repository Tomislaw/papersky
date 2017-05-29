// Klasa odpowiedzialna za pojedyñczy kafelek z mapy

/*
Ustawia kafelek z danych g³ównych, wskaŸnika do pliku tekstury oraz pozycji kafelka
void setTile(TextElement tile, sf::Texture &texture, sf::Vector2f tile_position);

Ustawia kafelek specjalny odpowiadaj¹cy za granice mapy
void setTileMapBorder(sf::Vector2i size);

Rysuje kafelek
void drawTile(sf::RenderWindow &window);

Funkcja do uaktualniania collisionboxa w pobocznym niedokoñczonym programie objecteditor
void updateCollisionBoxVertexArray();

Funkcja do rysowania collisionboxa w pobocznym niedokoñczonym programie objecteditor
void drawCollisionBoxVertexArray(sf::RenderWindow &window, bool draw_shape, bool draw_lines, int draw_point);

Zwraca collisionbox tile'a
std::vector<sf::Vector2f> get_collision()

Zwraca punkty górne collisionboxa (ju¿ nieu¿ywane
std::vector<sf::Vector2f> get_top_points()

Sprawdza, czy punkt znajduje siêwewn¹trz collisionboxa
bool check_collision(sf::Vector2f &point)

Zwraca nazwe tile'a
std::string get_tilename()

*/

#ifndef TILE_H
#define TILE_H
#include "SFML/Graphics.hpp"
#include <vector>
#include "collision.hpp"
#include "Collision_box.h"
#include "Entity/Entity.hpp"
#include "FileManager\TextFileData.h"


class Tile :
	public Entity
{
public:
	Tile();

	void setTile(TextElement tile, sf::Texture &texture, sf::Vector2f tile_position);

	void setTileMapBorder(sf::Vector2i size);

	void drawTile(sf::RenderWindow &window);
	void updateCollisionBoxVertexArray();
	void Tile::drawCollisionBoxVertexArray(sf::RenderWindow &window, bool draw_shape, bool draw_lines, int draw_point);
	std::vector<sf::Vector2f> get_collision()
	{
		return collisionbox.get_points();
	}
	std::vector<sf::Vector2f> get_top_points()
	{
		return collisionbox.get_top_points(top_vertex_id);
	}

	bool check_collision(sf::Vector2f &point)
	{
		return intersects_convex(collisionbox.get_points(), point);
	}
	std::string get_tilename()
	{
		if (TileName.empty()) return "NONE";
		return TileName;
	}
	~Tile();
private:
	sf::VertexArray vertexarray;

	std::string TileName;
	Collision_box collisionbox;
	std::vector <int> top_vertex_id;
	const float tile_size = 50;

	sf::Sprite tile_sprite;
};

#endif