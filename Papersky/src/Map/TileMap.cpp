#include "Map\TileMap.h"


TileMap::TileMap()
{
	std::string localization = "maps/map1.txt";
	TextFileData map;
	map.read_file(localization);
	height = map.get_first_element_by_name("TILEMAP")->get_variable_by_name("Size")->to_float(1);
	width = map.get_first_element_by_name("TILEMAP")->get_variable_by_name("Size")->to_float(0);

	
	load_texture_types("game/tiles.txt");
	load_tile_types("game/tiles.txt");
	tilemap = new Tile*[width];

	for (int x = 0; x < width; x++)
	{
		tilemap[x] = new Tile[height];
	}

	
	for (int y = 0; y < height; y++)
	{
		
		for (int x = 0; x < width; x++)
		{
			std::string index = std::to_string(y);
			std::string tile_type_id = map.get_first_element_by_name("TILEMAP")->get_variable_by_name(index)->var[x].c_str();
			get_tile_type(tile_type_id)->get_variable_by_name("Texture")->var[0];
			int id = get_texture_id(get_tile_type(tile_type_id)->get_variable_by_name("Texture")->var[0]);
			sf::Vector2f position(x * tile_size + tile_size/2, y * tile_size + tile_size/2);
			tilemap[x][y].setTile(*get_tile_type(tile_type_id), tile_texture[id], position);
			
		}
	}
	
	map_border.setTileMapBorder(sf::Vector2i(width * tile_size, height * tile_size));

	//std::<<endl;
	
}


TileMap::TileMap(std::string localization)
{
	TextFileData map;
	map.read_file(localization);
	height =map.get_first_element_by_name("TILEMAP")->get_variable_by_name("Size")->to_int(1);
	width =map.get_first_element_by_name("TILEMAP")->get_variable_by_name("Size")->to_int(0);

	load_texture_types("game/tiles.txt");
	load_tile_types("game/tiles.txt");
	tilemap = new Tile*[width];

	for (int x = 0; x < width; x++)
	{
		tilemap[x] = new Tile[height];
	}


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; y < width; x++)
		{
			TextElement* tile = get_tile_type(map.get_first_element_by_name("TILEMAP")->get_variable_by_name(std::to_string(y))->var[x].c_str());
			int id = get_texture_id(tile->get_variable_by_name("Texture")->var[0]);
			sf::Vector2f position(x * tile_size + tile_size/2, y * tile_size + tile_size/2);
			tilemap[x][y].setTile(*tile,tile_texture[id], position);
		}
	}

}

void TileMap::draw(sf::RenderWindow &window)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			tilemap[x][y].drawTile(window);
		}
	}

}

bool TileMap::check_collision(sf::Vector2f &position)
{
	sf::Vector2i pos = get_tile(position);
	if (pos.x == -1) return true;
	return tilemap[pos.x][pos.y].check_collision(position);
}

 sf::Vector2i &TileMap::get_tile( sf::Vector2f &position)
{
	sf::Vector2i pos(position.x / tile_size, position.y / tile_size);
	if (position.x < 0 || pos.x>width-1 || position.y<0 || pos.y > height-1) { pos.x = -1; pos.y = -1; }
	return pos;
}

  std::vector <sf::Vector2f> TileMap::get_tile_collision_hull( sf::Vector2f &position)
{
	sf::Vector2i pos = get_tile(position);
	if (pos.x == -1) return map_border.get_collision();
	return tilemap[pos.x][pos.y].get_collision();
}
std::vector <sf::Vector2f> TileMap::get_tile_collision_hull( sf::Vector2i tile_id)
{
	if (tile_id.x < 0 || tile_id.x >= width) return map_border.get_collision();
	if (tile_id.y < 0 || tile_id.y >= height) return map_border.get_collision();
	return tilemap[tile_id.x][tile_id.y].get_collision();
}
std::vector<std::vector<sf::Vector2f>> TileMap::get_tiles_collision_hull(const std::vector <sf::Vector2i> &tiles_ids)
{
	std::vector<std::vector<sf::Vector2f>> collision;
	
	for (int i = 0; i < tiles_ids.size();i++)
	{

		collision.push_back(get_tile_collision_hull(tiles_ids[i]));
	}
	return collision;
}
std::vector <sf::Vector2f> TileMap::get_tile_top_points(sf::Vector2f &position)
{
	sf::Vector2i pos = get_tile(position);
	if (pos.x == -1) return map_border.get_top_points();
	return tilemap[pos.x][pos.y].get_top_points();
}

TileMap::~TileMap()
{
	for (int i = 0; i < width; ++i)
		delete[] tilemap[i];

	delete[] tilemap;

	delete[] tile_texture;
}

 std::vector <sf::Vector2i> TileMap::get_tiles_from_line(sf::Vector2f start, sf::Vector2f end)
{
	std::vector<sf::Vector2i> tile_ids;
	sf::Vector2i starting_id = get_tile(start);
	sf::Vector2i ending_id(end.x / tile_size, end.y / tile_size);
	if (end.x < 0) ending_id.x = -1;
	if (end.y < 0) ending_id.y = -1;
	if (starting_id == ending_id || starting_id.x < 0)
	{
		tile_ids.push_back(starting_id);

		return tile_ids;
	}
	if (true)
	{
		// Tworzenie funkcji liniowej
		float divide = end.x - start.x;
		float a = (end.y - start.y) / divide;
		float b = end.y - a*end.x;
		// zmiana a na nieskonczonosc
		if (!(divide>0.0000001 || divide<-0.0000001)) { a = INFINITY;}

		// ustawianie licznika x i y
		int x_count= abs(starting_id.x - ending_id.x);
		int y_count = abs(starting_id.y - ending_id.y);


		// dodawanie lub odejmowanie licznika
		int operation_x = 1;
		int operation_y = 1;
		if (start.x > end.x)
		{
			operation_x = -1;
		}
		if (start.y > end.y)
		{
			operation_y = -1;
		}

		tile_ids.push_back(starting_id);
		if (a<1 && a>-1)
		{
			int current_x = starting_id.x;

			for (int i = 0; i < x_count; i++)
			{
				

				
				float value_x = current_x * tile_size + operation_x / 10.f + tile_size/2 * (1 + operation_x);
				sf::Vector2f function_pos_x= sf::Vector2f(value_x, a*(value_x) + b);
				sf::Vector2i id_x(get_tile(function_pos_x));

				if (id_x.x != tile_ids.back().x && id_x.y != tile_ids.back().y)
				{
					float value_y = tile_ids.back().y * tile_size + tile_size/2 * (1 + operation_y) + operation_y / 10.f;
					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(get_tile(function_pos_y));

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);
					if (id_y.x < 0) break;
				}


				if (id_x != tile_ids.back())tile_ids.push_back(id_x);
				if (id_x.x < 0) break;
				current_x += operation_x;
			}
			sf::Vector2i id_last(get_tile(end));
			if (id_last != tile_ids.back())
			{
				if (id_last.x != tile_ids.back().x && id_last.y != tile_ids.back().y)
				{
					float value_y = tile_ids.back().y * tile_size + tile_size/2 * (1 + operation_y) + operation_y / 10.f;
					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(get_tile(function_pos_y));

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);

				}

				if (id_last != tile_ids.back())tile_ids.push_back(id_last);
			}
		}
		else
		{
			if (a != INFINITY)
			{
				int current_x = starting_id.x;
				int current_y = starting_id.y;
			

				for (int i = 0; i < y_count;i++)
				{

					float value_y = tile_ids.back().y * tile_size + tile_size/2 * (1 + operation_y) + operation_y / 10.f;

					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(get_tile(function_pos_y));


					if (id_y.x != tile_ids.back().x && id_y.y != tile_ids.back().y)
					{
						float value_x = current_x * tile_size + operation_x / 10.f + tile_size/2 * (1 + operation_x);
						sf::Vector2f function_pos_x = sf::Vector2f(value_x, a*value_x + b);
						sf::Vector2i id_x(get_tile(function_pos_x));
						if (id_x != tile_ids.back())tile_ids.push_back(id_x);
						if (id_x.x < 0)break;
	
						current_x += operation_x;

					}
	
					if (id_y != tile_ids.back())tile_ids.push_back(id_y);
					if (id_y.x < 0)break;
					current_y += operation_y;
				}
			}
			else
			{
				for (int i = 0; i < y_count;i++)
				{
					sf::Vector2i startvector = get_tile(start + sf::Vector2f(0,(i+1)*tile_size));
					tile_ids.push_back(startvector);
					if (startvector.y < 0) break;
				}
			}
		

		}
		

		for (int i = 0; i < tile_ids.size();i++)
		{
		//	std::cout << "Tile " << tile_ids[i].x << " " << tile_ids[i].y << std::endl;
		}
		return tile_ids;
	}
}




bool TileMap::load_texture_types(std::string localization)
{
	TextFileData texture_list;
	texture_list.read_file(localization);
	std::vector <TextElement*> textures = texture_list.get_all_elements_by_name("TEXTURE");
	if (textures.size() < 1) {
		std::cout << "blad odczytu" << std::endl;
		return 1;
	}
	tile_texture = new sf::Texture[textures.size()];

	for (int i = 0; i < textures.size(); i++)
	{
		std::cout << textures[i]->get_variable_by_name("File")->var[0] << std::endl;
		tile_texture[i].loadFromFile(textures[i]->get_variable_by_name("File")->var[0]);
		texture_id.push_back(textures[i]->get_variable_by_name("Id")->var[0]);
	}
	std::cout << "Texture size = " << textures.size() << std::endl;
}

bool TileMap::load_tile_types(std::string localization)
{
	TextFileData tile_list;
	tile_list.read_file(localization);
	auto tiles = tile_list.get_all_elements_by_name("TILE");
	for (int i = 0;i < tiles.size();i++)
	{
		Tile_type.push_back(*tiles.at(i));
	}
	
	return 0;
}

TextElement* TileMap::get_tile_type(std::string id)
{
	for (int i = 0; i < Tile_type.size();i++)
	{
		if (Tile_type[i].get_variable_by_name("Id")->var[0] == id)
		{
			return &Tile_type[i];
		}
	}
	std::cout << "Tile + " + id + " not found!";
	
	return nullptr;
}

int TileMap::get_texture_id(std::string text)
{
	for (int i = 0; i < texture_id.size();i++)
	{
		if (text == texture_id[i]) return i;
	}
	return 0;
}



void TileMap::drawInConsole(sf::Vector2f playerpos)
{
	int sizex = width;
	int sizey = height;

	//if (sizex > 10)sizex = 10;
	//if (sizey > 10)sizey = 10;
	sf::Vector2i pos = get_tile(playerpos);


	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pos.x == x && pos.y == y)
			{
				std::cout << "><";
			}
			else
			{
				if (tilemap[x][y].get_tilename() == "air") std::cout << "  ";
				if (tilemap[x][y].get_tilename() == "concrete_main" || tilemap[x][y].get_tilename() == "earth") std::cout << "[]";
				if (tilemap[x][y].get_tilename() == "concrete_slope01") std::cout << "[.";
				if (tilemap[x][y].get_tilename() == "concrete_slope02") std::cout << "/]";
			}
		}
		std::cout << std::endl;
	}
	int lol;
}