#include "Ray.h"



Ray::Ray()
{

}


Ray::~Ray()
{
}

void Ray::Set_parent(Entity &set_parent)
{
	parent = &set_parent;
	is_attached_to_parent = true;

}

bool Ray::Update_intersection(std::vector<std::vector<sf::Vector2f>> &world)
{
	//std::cout << world.size();
	 
	for (int i = 0; i < world.size();i++)
	{

		if (check_and_get_lines_intersection(world[i], position_start, position_end, ray_end))
		{
			collision_object_index = i;
			return true;
		};
		
	}
	ray_end = position_end;
	collision_object_index = -1;
	return false;
}
bool Ray::Update_Ray(TileMap &tilemap)
{
	Update();
	return Update_intersection(tilemap.get_tiles_collision_hull(tilemap.get_tiles_from_line(position_start,position_end)));
	
}
bool Ray::Update_Ray(TileMap &tilemap, std::string &object_collision_name)
{
	Update();
	TileMap *map = &tilemap;
	

	bool collision = Update_intersection(tilemap.get_tiles_collision_hull(tilemap.get_tiles_from_line(position_start, position_end)));
	if (collision)
	{
		
	}
	return false;
}

void Ray::Update()
{
	if (is_attached_to_parent) position_start = parent->getPosition();

	 position_end = position_start;
	 position_end.x += lenght*cos(radian);
	 position_end.y += lenght*sin(radian);
}

void Ray::draw(sf::RenderWindow &window)
{
	sf::Vertex line[] =
	{
		sf::Vertex(position_start),
		sf::Vertex(ray_end)
	};

	window.draw(line, 2, sf::Lines);
}