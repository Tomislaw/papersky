// Klasa odpowiedzialna za prop - byt z kolizj¹
/*
wirtualna funkcja s³u¿¹ca do ustawiania propa
virtual bool Prop::set_prop(TextElement &prop, std::vector <TextElement> &sprite_types, sf::Texture &texture);

Zwaraca kolizje
std::vector <sf::Vector2f> & Get_collision_box() { return collisionbox.get_points(); }

Uaktualnia byt
void Update_prop(float &delta_time, TileMap &tilemap);

Przesuwa byt do czasu osi¹gniêcia okreœlonej prêdkoœci
void Impulse_velocity_x_to_max_speed(const float &velocity_x, const float &max_speed);

Operacje wykonane po wykryciu kolizji
void Collision_handler(TileMap &tilemap, float &delta_time);

Wirtualna funkcja do ustwiania sprite propa
virtual void add_sprites(const Animated_game_sprite *sprite, unsigned int amount);

Rysowanie propsa
void draw(sf::RenderWindow &window);
*/

#ifndef PROP_HPP
#define PROP_HPP
#include "Entity.hpp"
#include "collision_box.h"
#include "collision.hpp"
#include "animated_game_sprite.h"
#include "Map\TileMap.h"
//#include "Ray.h"
class Prop :
	public Entity
{
public:
	Prop();
	~Prop();

	virtual bool Prop::set_prop(TextElement &prop, std::vector <TextElement> &sprite_types, sf::Texture &texture);


	 std::vector <sf::Vector2f> & Get_collision_box() { return collisionbox.get_points(); }

	virtual void Update_prop(float &delta_time, TileMap &tilemap);

	void Impulse_velocity_x_to_max_speed(const float &velocity_x, const float &max_speed);
	virtual	void Update(float delta_time)
	{
		Entity::Update(delta_time);
	}
	
	void Collision_handler( TileMap &tilemap, float &delta_time);

	virtual void add_sprites(const Animated_game_sprite *sprite, unsigned int amount);
	void draw(sf::RenderWindow &window);
	void teleport(sf::Vector2f p) { setPosition(p);collisionbox.setPosition(p); };
protected:

	int get_point_direction(int index)
	{
		for (int i = 0; i < bottom_collide_points.size();i++)
		{
			if (index = bottom_collide_points[i])return 2;
		}
		for (int i = 0; i < top_collide_points.size();i++)
		{
			if (index = top_collide_points[i])return 1;
		}
		for (int i = 0; i < right_collide_points.size();i++)
		{
			if (index = right_collide_points[i]) return 0;
		}
		for (int i = 0; i < left_collide_points.size();i++)
		{
			if (index = left_collide_points[i])return 3;
		}
	}
	Collision_box collisionbox;

	unsigned int sprite_amount = 1;
	std::vector<Animated_game_sprite> sprite;

	bool is_collide_with_world = true;
	bool is_collidable = true;

	sf::Vector2f slope_modifier;

	std::vector <int> left_collide_points;
	std::vector <int> right_collide_points;
	std::vector <int> top_collide_points;
	std::vector <int> bottom_collide_points;

	bool is_collide_left = false;
	bool is_collide_right = false;
	bool is_collide_top = false;
	bool is_collide_bottom = false;



};

#endif
