#include "Map\Map.h"



Map::Map()
{
	//cameraview.setSize(sf::Vector2f(2000, 2000));
}


Map::~Map()
{
}



void Map::update(float &delta_time)
{
	update_view_position(entities.get_player_position());
	entities.update(delta_time, tile2);
	entities.update_cursor_position(cursor.get_position());
}

void Map::draw(sf::RenderWindow &window)
{
	tile2.draw(window);
	entities.draw(window);


	window.setView(cameraview);
	cursor.draw(window, sf::Vector2f(cameraview.getCenter() - cameraview.getSize() / 2.f));
}

void Map::handle_event(sf::Event &handleevent)
{
	entities.handle_event(handleevent);
}



void Map::update_view_position(sf::Vector2f pos)
{
	sf::Vector2f camera_pos = pos;
	if (cameraview.getSize().x / 2 > pos.x)
	{
		camera_pos.x = cameraview.getSize().x / 2;
	}
	else
	{
		if ( tile2.get_size().x - cameraview.getSize().x / 2 < pos.x)
		{
			camera_pos.x = tile2.get_size().x - cameraview.getSize().x / 2;
		}
	}
	if (cameraview.getSize().y / 2 > pos.y)
	{
		camera_pos.y = cameraview.getSize().y / 2;
	}
	else
	{
		if (tile2.get_size().y - cameraview.getSize().y / 2 < pos.y)
		{
			camera_pos.y = tile2.get_size().y - cameraview.getSize().y / 2;
		}
	}
	cameraview.setCenter(camera_pos);
}