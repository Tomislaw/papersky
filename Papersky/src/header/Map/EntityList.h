//Klasa odpowadaj¹ca za byty znajduj¹ce siê na mapie gry

/*	

bool load_texture_types(std::string localization);
£aduje plik z danymi przechowuj¹cymi dane tekstur -> ich pozycje, nazwe, wielkoœæ

bool load_entity_types(std::string localization);
£aduje plik z danymi przechowuj¹cymi dane bytów -> ich rodzaj, nu¿yte tekstury i sprite

bool load_entities(std::string localization);
£aduje plik z danymi przechowuj¹cymi po³o¿enie bytów na mapie

bool load_sprities(std::string sprites, std::string animations);
£aduje plik z danymi przechowuj¹cymi sprajty

bool add_entity(TextElement &entity_data);
Dodaje kolejny byt do mapy

void handle_event(sf::Event &handleevent);
Zajmuje siê wydarzeniami z klawiatury

void draw(sf::RenderWindow &window);
Rysuje ca³¹mape oraz wszystkie byty

void update(float delta, TileMap &tilemap);
Uaktualnia fizyke gry oraz sprajty

void update_cursor_position(sf::Vector2f cursor_pos);
Uaktualnia pozycje kursora

const sf::Vector2f &get_player_position()
Zwraca po³o¿enie gracza
*/

#ifndef ENTITYLIST_H
#define ENTITYLIST_H

//#include "projective.h"
//#include "ray.h"
#include "Entity/player.h"
#include "FileManager\TextFileData.h"
class EntityList
{
public:
	EntityList();
	~EntityList();
	
	bool load_texture_types(std::string localization);
	bool load_entity_types(std::string localization);
	bool load_entities(std::string localization);
	bool load_sprities(std::string sprites, std::string animations);


	void handle_event(sf::Event &handleevent);
	void draw(sf::RenderWindow &window);
	void update(float delta, TileMap &tilemap);
	void update_cursor_position(sf::Vector2f cursor_pos);
	const sf::Vector2f &get_player_position()
	{
		return player.getPosition();
	}

	/*void add_bullet(Projective bullet)
	{
		bullets.push_back(bullet);
	}*/
	bool add_entity(TextElement &entity_data);

	void player_fire();
private:
	int get_texture_id(std::string text);

	sf::Texture *sprite_texture;
	std::vector <std::string> texture_id;

	std::vector <TextElement> entity_types;
	std::vector <TextElement> sprite_types;
	std::vector <TextElement> sprite_animation_types;
	//std::shared_ptr<Player> player;
	Player player;
	//Ray ray;
	//std::vector <Projective> bullets;



	sf::Vector2f cursor_position;
};

#endif