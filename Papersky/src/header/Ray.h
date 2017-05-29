#ifndef RAY_H
#define RAY_H
#include "Entity\Entity.hpp"
#include "collision.hpp"
#include "Map\TileMap.h"
#define M_PI 3.14159265358979323846;

class Ray
{
public:
	Ray();
	~Ray();

	void Ray::Set_parent(Entity &set_parent);
	void Ray::Set_ray(sf::Vector2f position, float set_angle, float set_lenght)
	{
		position_start = position;
		radian = set_angle * M_PI;
		radian /= 180;
		lenght = set_lenght;
		Update();
	}
	void Ray::Set_ray(sf::Vector2f start, sf::Vector2f end)
	{
		position_start = start;
		float a = end.y - position_start.y;
		float b = end.x - position_start.x;

		radian = atan(a / b);
		if (b<0)
		{
			radian += +M_PI;
		}
		lenght = sqrt((end.x-start.x)*(end.x - start.x)+(end.y - start.y)*(end.y - start.y));
		Update();
	}
	void Ray::Set_position(sf::Vector2f start)
	{
		position_start = start;
		Update();
	}
	void Ray::Change_angle(sf::Vector2f end_pos)
	{
		float a = end_pos.y - position_start.y;
		float b = end_pos.x - position_start.x;

		radian = atan(a/b);
		if (b<0)
		{
			radian += + M_PI;
		}
	}
	void Ray::Change_angle(float angle_set)
	{
		radian = angle_set * M_PI;
		radian /= 180;
	}
	bool Ray::Update_intersection(std::vector<std::vector<sf::Vector2f>> &world);
	bool Ray::Update_Ray(TileMap &tilemap);
	bool Ray::Update_Ray(TileMap &tilemap, std::string &object_collision_name);
	void Ray::Update();
	void draw(sf::RenderWindow &window);

	sf::Vector2f get_ray_end()
	{
		return ray_end;
	}

private:

	Entity *parent;
	float radian;
	float lenght;
	sf::Vector2f position_start;
	sf::Vector2f position_end;
	sf::Vector2f ray_end;
	bool is_attached_to_parent = false;
	bool is_static = false;
	bool is_collide = false;

	int collision_object_index = -1;
};

#endif