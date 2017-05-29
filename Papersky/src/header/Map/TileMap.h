// Klasa odpowiedzialna za tilemap

/*

Rysuje tilemap
void draw(sf::RenderWindow &window);

Rysuje tilemape w konsoli
void drawInConsole(sf::Vector2f playerpos);

Sprawdza czy punkt znajduje siê wewn¹trz tile
bool check_collision(sf::Vector2f &position);

Zwraca wielkoœæ tilemapy
sf::Vector2i &get_size()

Zwraca index tile w danym punkcie
sf::Vector2i &get_tile(sf::Vector2f &position);

Zwraca kolizje tile'a
std::vector <sf::Vector2f> get_tile_collision_hull(sf::Vector2f &position);

Zwraca kolizje tile'a
std::vector <sf::Vector2f> get_tile_collision_hull(sf::Vector2i tile_id);

Zwraca kolizje grupy tile'ów
std::vector<std::vector<sf::Vector2f>> get_tiles_collision_hull(const std::vector <sf::Vector2i> &tiles_ids);

Zwraca górne punkty kolizji tile'a
std::vector <sf::Vector2f> get_tile_top_points(sf::Vector2f &position);

Zwraca wszystkie tile znajduj¹ce siêna danej lini
std::vector <sf::Vector2i> get_tiles_from_line(sf::Vector2f start, sf::Vector2f end);
*/

#ifndef TILEMAP_H
#define TILEMAP_H
#include "tile.h"

class TileMap
{
public:
	TileMap();
	TileMap(std::string localization);
	~TileMap();

	void draw(sf::RenderWindow &window);
	void drawInConsole(sf::Vector2f playerpos);
	bool check_collision(sf::Vector2f &position);
	sf::Vector2i &get_size()
	{
		return sf::Vector2i(width * tile_size, height * tile_size);
	};
	sf::Vector2i get_tilemap_size() { return sf::Vector2i(width, height); };
	sf::Vector2i &get_tile( sf::Vector2f &position);
	std::vector <sf::Vector2f> get_tile_collision_hull( sf::Vector2f &position);
	std::vector <sf::Vector2f> get_tile_collision_hull( sf::Vector2i tile_id);

	std::vector<std::vector<sf::Vector2f>> get_tiles_collision_hull(const std::vector <sf::Vector2i> &tiles_ids);
	std::vector <sf::Vector2f> get_tile_top_points(sf::Vector2f &position);
	std::vector <sf::Vector2i> get_tiles_from_line(sf::Vector2f start, sf::Vector2f end);
	
	TextElement* get_tile_type(std::string id);
	
	// Loadery
	bool load_texture_types(std::string localization);
	bool load_tile_types(std::string localization);

private:
	int get_texture_id(std::string text);
	unsigned int width = 0;
	unsigned int height = 0;;
	const float tile_size = 50;
	Tile map_border;
	Tile **tilemap;
	sf::Texture *tile_texture;
	std::vector <std::string> texture_id;
	std::vector <TextElement> Tile_type;

};

#endif