#include "Entity\Prop.hpp"
#include "Map\TileMap.h"
#include "Ray.h"
#include <conio.h>

Prop::Prop()
{
	Entity::Entity();
	Animated_game_sprite sr;
	sprite.push_back(sr);
	for (int i = 0; i < sprite_amount; i++)
	{
		sprite[i].Set_parent(*this);
	}
	std::cout << sprite.size();
	slowdown.x = 50;
	collisionbox.add_point(sf::Vector2f(-16, -10));
	collisionbox.add_point(sf::Vector2f(0, -16));
	collisionbox.add_point(sf::Vector2f(16, -10));
	collisionbox.add_point(sf::Vector2f(0, 16));
	left_collide_points.push_back(0);
	right_collide_points.push_back(2);
	top_collide_points.push_back(1);
	bottom_collide_points.push_back(3);
	acceleration.y = 4000;

	this->setPosition(50, 50);
	collisionbox.Set_parent(*this);
	collisionbox.Update(1);
}

bool Prop::set_prop(TextElement &prop, std::vector <TextElement> &sprite_types, sf::Texture &texture)
{
	std::string sprite_id = prop.get_variable_by_name("Sprite")->var[0];

	bool found_sprite = 0;
	for (int i = 0; i < sprite_types.size();i++)
	{
		if (sprite_id == sprite_types[i].get_variable_by_name("Id")->var[0])
		{

			sprite[0].set_animated_sprite(texture, sprite_types[i]);
			found_sprite = true;
			break;
		}
	}
	if (found_sprite == false) std::cout << "Can't find sprite for " << name << std::endl;

	
	collisionbox.clear();

	int vert_amount = 0;
	vert_amount = prop.get_variable_by_name("Vertex_amount")->to_int(0);

	for (int i = 0; i < vert_amount;i++)
	{
		sf::Vector2f point;
		point.x = prop.get_variable_by_name("Collision_shape")->to_int(2 * i);;
		point.y = prop.get_variable_by_name("Collision_shape")->to_int(2 * i+1);;
		collisionbox.add_point(point);
	}

	int leftp,rightp, topp, bottomp = 0;
	leftp = prop.get_variable_by_name("Left_collide_points")->var.size();
	rightp = prop.get_variable_by_name("Right_collide_points")->var.size();
	topp = prop.get_variable_by_name("Top_collide_points")->var.size();
	bottomp = prop.get_variable_by_name("Bottom_collide_points")->var.size();

	for (int i = 0; i < leftp;i++)
	{
		int point = 0;
		point = atoi(prop.get_variable_by_name("Left_collide_points")->var[i].c_str());
		left_collide_points.push_back(point);
	}
	for (int i = 0; i < rightp;i++)
	{
		int point = 0;
		point = atoi(prop.get_variable_by_name("Right_collide_points")->var[i].c_str());
		right_collide_points.push_back(point);
	}
	for (int i = 0; i < topp;i++)
	{
		int point = 0;
		point = atoi(prop.get_variable_by_name("Top_collide_points")->var[i].c_str());
		top_collide_points.push_back(point);
	}
	for (int i = 0; i < bottomp;i++)
	{
		int point = 0;
		point = atoi(prop.get_variable_by_name("Bottom_collide_points")->var[i].c_str());
		bottom_collide_points.push_back(point);
	}
	
		return 0;

	
}

void Prop::Update_prop(float &delta_time, TileMap &tilemap)
{

	
	
	Collision_handler(tilemap, delta_time);
	for (int i = 0; i < sprite_amount; i++)
	{
		sprite[i].Update_animated_sprite(delta_time);
	}

	
}

void Prop::Impulse_velocity_x_to_max_speed(const float &velocity_x, const float &max_speed)

{
	if (velocity.x < max_speed && velocity_x>0 || velocity.x > max_speed && velocity_x < 0)
	{
		if (velocity.x < 0 && velocity_x>0 || velocity.x >0 && velocity_x<0)
		{
			velocity.x = 0;
		}
		else
		{
			velocity.x += velocity_x;
		}
	}
	else velocity.x = max_speed;
}

void Prop::add_sprites(const Animated_game_sprite *sprites, unsigned int amount)
{
	sprite_amount = amount;
	//sprite = new Animated_game_sprite[amount];
	for (int i = 0; i < amount;i++)
	{
		/// TODO: przeciazenie operatora porownania
	}
}
void Prop::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < sprite_amount; i++)
	{
		sprite[i].draw(window);
	}
}

/*
void Prop::Collision_handler( TileMap &tilemap, float &delta_time)
{

	collisionbox.Update(delta_time);
	for (int i = 0; i < top_collide_points.size();i++)
	{
		is_collide_top = tilemap.check_collision(collisionbox.get_point(top_collide_points[i]));
		if (is_collide_top)
		{
			if (velocity.y < 0)
			{
				move(0, -velocity.y*delta_time);
				velocity.y = 0;
			}
			else if (!is_collide_bottom)move(0, 2);
			collisionbox.Update(delta_time);
			break;
		}
	}

	for (int i = 0; i < bottom_collide_points.size();i++)
	{

		slope_modifier = check_collision_with_line(tilemap.get_tile_top_points(collisionbox.get_point(bottom_collide_points[i])),collisionbox.get_point(bottom_collide_points[i]), sf::Vector2f(getPosition().x, 0));
		is_collide_bottom = tilemap.check_collision(collisionbox.get_point(bottom_collide_points[i]));
		if (is_collide_bottom)
		{
			//is_collide_bottom = tilemap.check_collision(sf::Vector2f(collisionbox.get_point(bottom_collide_points[i]).x, collisionbox.get_point(bottom_collide_points[i]).y));
			if (velocity.y > 0)
			{
				velocity.y = 0;
			}
			else move(0, -2);

			if (slope_modifier.y != 0)
			{
				move(0, -collisionbox.get_point(bottom_collide_points[i]).y + slope_modifier.x*getPosition().x + slope_modifier.y);
			}
			//if (tilemap.check_collision(sf::Vector2f(collisionbox.get_point(bottom_collide_points[i]).x, collisionbox.get_point(bottom_collide_points[i]).y - 10)))slope_modifier = check_collision_with_line(tilemap.get_tile_top_points(sf::Vector2f(collisionbox.get_point(bottom_collide_points[i]).x, collisionbox.get_point(bottom_collide_points[i]).y - 20)), collisionbox.get_point(bottom_collide_points[i]), sf::Vector2f(getPosition().x, 0));

	
			collisionbox.Update(delta_time);

			sf::Vector2f slope_start_checker(collisionbox.get_point(bottom_collide_points[i]) + sf::Vector2f(0, -2));
			if (tilemap.check_collision(slope_start_checker))
			{
				slope_modifier = check_collision_with_line(tilemap.get_tile_top_points(slope_start_checker), slope_start_checker, sf::Vector2f(getPosition().x, 0));
				if (slope_modifier.y != 0)
				{
					move(0, -collisionbox.get_point(bottom_collide_points[i]).y + slope_modifier.x*getPosition().x + slope_modifier.y);
				}
				collisionbox.Update(delta_time);
			}

			break;
		}

	

	}

	for (int i = 0; i < left_collide_points.size();i++)
	{
		is_collide_left = tilemap.check_collision(collisionbox.get_point(left_collide_points[i]));
		if (is_collide_left)
		{
			if (velocity.x < 0)
			{
				move(-velocity.x*delta_time, 0);
				velocity.x = 0;
			}
			else move(2, 0);
			collisionbox.Update(delta_time);
			break;
		}
	}

	for (int i = 0; i < right_collide_points.size();i++)
	{
		is_collide_right = tilemap.check_collision(collisionbox.get_point(right_collide_points[i]));
		if (is_collide_right) 
		{ 
			if (velocity.x > 0)
			{
				move(-velocity.x*delta_time, 0);
				velocity.x = 0;
			}
			else move(-2, 0);
			collisionbox.Update(delta_time);
			break; 
		}
	}

	//else acceleration.y = 100;
	//std::cout << "Left " << collisionbox.get_point(0).x << " " << collisionbox.get_point(0).y << " " << is_collide_left << std::endl;
	//std::cout << "Top " << collisionbox.get_point(1).x << " " << collisionbox.get_point(1).y << " " << is_collide_top << std::endl;
	//std::cout << "Right " << collisionbox.get_point(2).x << " " << collisionbox.get_point(2).y << " " << is_collide_right << std::endl;
	//std::cout << "Bottom " << collisionbox.get_point(3).x << " " << collisionbox.get_point(3).y << " " << is_collide_bottom << std::endl;
	//std::cout << "slope_modifier " << slope_modifier << std::endl;
}
*/

void Prop::Collision_handler(TileMap &tilemap, float &delta_time)
{
	
	sf::Vector2f before_update = collisionbox.getPosition();

	Entity::Update(delta_time);
	collisionbox.Update(delta_time);



	Ray ray_collision_check;

	bool collision = 0;

	bool collision_bottom = 0;
	for (int i = 0; i < bottom_collide_points.size(); i++)
	{

		sf::Vector2f check_position_start(before_update-sf::Vector2f(0,1));
		sf::Vector2f check_position_end(collisionbox.get_point(bottom_collide_points[i]));

		ray_collision_check.Set_ray(check_position_start, check_position_end);
		collision = ray_collision_check.Update_intersection(tilemap.get_tiles_collision_hull(tilemap.get_tiles_from_line(check_position_start, check_position_end)));

		if (collision&&velocity.y>0)
		{
			collision_bottom = true;
			velocity.y = 0;
			//std::cout << "Move collisiom bottom " << ray_collision_check.get_ray_end().x - check_position_end.x << " " << ray_collision_check.get_ray_end().y - check_position_end.y << std::endl;
			this->move(0,ray_collision_check.get_ray_end().y - collisionbox.get_point(bottom_collide_points[i]).y);
			collisionbox.Update(delta_time);
		}
	}
	is_collide_bottom = collision || collision_bottom;

	bool collision_top = 0;
	for (int i = 0; i < top_collide_points.size(); i++)
	{
		sf::Vector2f check_position_start(before_update + sf::Vector2f(0, -1));
		sf::Vector2f check_position_end(collisionbox.get_point(top_collide_points[i]));
		ray_collision_check.Set_ray(check_position_start, check_position_end);
		collision = ray_collision_check.Update_intersection(tilemap.get_tiles_collision_hull(tilemap.get_tiles_from_line(check_position_start, check_position_end)));
		
		if (collision==0)collision=intersects_convex(tilemap.get_tile_collision_hull(tilemap.get_tile(check_position_end)), check_position_end);
		if (collision)
		{
			collision_top = true;
			velocity.y = 0;
			this->move(0, ray_collision_check.get_ray_end().y - collisionbox.get_point(top_collide_points[i]).y);
			collisionbox.Update(delta_time);
		}
	}
	is_collide_top = collision || collision_top;

	bool collision_left = 0;
	for (int i = 0; i < left_collide_points.size(); i++)
	{
		sf::Vector2f check_position_start(collisionbox.getPosition()+ sf::Vector2f(1,0));
		sf::Vector2f check_position_end(collisionbox.get_point(left_collide_points[i]));
		ray_collision_check.Set_ray(check_position_start, check_position_end);
		collision = ray_collision_check.Update_intersection(tilemap.get_tiles_collision_hull(tilemap.get_tiles_from_line(check_position_start, check_position_end)));	

		if (collision)
		{
			collision_left = true;
			velocity.x = 0;
			//std::cout << "Move collisiom left " << ray_collision_check.get_ray_end().x - check_position_end.x << " " << ray_collision_check.get_ray_end().y - check_position_end.y << std::endl;
			this->move(10,0);
			collisionbox.Update(delta_time);

		}
	}
	is_collide_left = collision || collision_left;

	bool collision_right = 0;
	for (int i = 0; i < right_collide_points.size(); i++)
	{

		sf::Vector2f check_position_start(before_update + sf::Vector2f(-1, 0));
		sf::Vector2f check_position_end(collisionbox.get_point(right_collide_points[i]));
		ray_collision_check.Set_ray(check_position_start, check_position_end);
		collision = ray_collision_check.Update_intersection(tilemap.get_tiles_collision_hull(tilemap.get_tiles_from_line(check_position_start, check_position_end)));
		if (collision)
		{
			collision_right = true;
			velocity.x = 0;
			this->move(-10,0);
			collisionbox.Update(delta_time);
		}
	
	}
	is_collide_right = collision || collision_right;


	
	if (is_collide_left&&is_collide_right)this->setPosition(before_update.x, getPosition().y);
	if(is_collide_top&&is_collide_bottom)this->setPosition(getPosition().x,before_update.y);
	collisionbox.Update(delta_time);
}


Prop::~Prop()
{
}
