#include "Map\EntityList.h"



EntityList::EntityList()
{

	load_texture_types("game/tiles.txt");
	load_entity_types("game/entity.txt");
	load_sprities("game/sprite.txt", "game/animations.txt");
	load_entities("maps/map1.txt");
	//ray.Set_ray(sf::Vector2f(250, 400), -180, 800);
	//ray.Set_parent(player);

//	bullets.push_back(Projective::Projective());

	player.Set_entity_list(*this);
}


EntityList::~EntityList()
{
	delete[] sprite_texture;
}


bool EntityList::load_texture_types(std::string localization)
{
	std::cout << "Loading texture types from " + localization << std::endl;
	TextFileData texture_list;
	texture_list.read_file(localization);
	std::vector <TextElement*> textures = texture_list.get_all_elements_by_name("TEXTURE");
	if (textures.size() < 1) {
		std::cout << "Can't find any texture file in " << localization << std::endl;
		return 1;
	}
	sprite_texture = new sf::Texture[textures.size()];

	for (int i = 0; i < textures.size(); i++)
	{
		std::cout << "Loaded texture: " <<textures[i]->get_variable_by_name("File")->var[0] << std::endl;
		sprite_texture[i].loadFromFile(textures[i]->get_variable_by_name("File")->var[0]);
		texture_id.push_back(textures[i]->get_variable_by_name("Id")->var[0]);
	}

}

bool EntityList::load_entity_types(std::string localization)
{
	std::cout << "Loading entity types from " + localization << std::endl;
	TextFileData entity_list;
	entity_list.read_file(localization);
	entity_types = entity_list.get_all_elements();
	if (entity_types.size() < 1) std::cout << "Can't find any entity declaration." << std::endl;
	return 0;
}

bool EntityList::load_entities(std::string localization)
{
	std::cout << "Loading entities from " + localization << std::endl;
	TextFileData map;
	map.read_file(localization);
	std::vector<TextElement*> map_entities = map.get_all_elements_by_name("ENTITY");
	if (map_entities.size() < 1) std::cout << "Can't find any entity in " << localization << std::endl;
	for (int i = 0; i < map_entities.size();i++)
	{
		add_entity(*map_entities[i]);
		map_entities[i]->display();
	}
	return 0;
}

bool EntityList::load_sprities(std::string sprites, std::string animations)
{
	std::cout << "Loading sprities from " + sprites << std::endl;
	std::cout << "Loading sprites animations from " + animations << std::endl;
	TextFileData sprite_list;
	sprite_list.read_file(sprites);
	sprite_types = sprite_list.get_all_elements();

	TextFileData animation_list;
	animation_list.read_file(animations);
	sprite_animation_types = animation_list.get_all_elements();
	if (sprite_types.size() < 1) std::cout << "Can't find any sprite declaration." << std::endl;
	if (sprite_animation_types.size() < 1) std::cout << "Can't find any sprite animation declaration." << std::endl;
	return 0;
}

bool EntityList::add_entity(TextElement &entity_data)
{
	std::string type = entity_data.get_variable_by_name("Entity_type")->var[0];

	if(type == "PLAYER")
	{
		for (int i = 0; i < entity_types.size();i++)
		{
			if (entity_types[i].name == type)
			{
				std::cout << "Player " << get_texture_id(entity_types[i].get_variable_by_name("Texture")->var[0]);
				player.set_prop(entity_types[i], sprite_types ,sprite_texture[get_texture_id(entity_types[i].get_variable_by_name("Texture")->var[0])]);
				return 0;
			}
		}
	}
	
	return 1;
}

int EntityList::get_texture_id(std::string text)
{
	for (int i = 0; i < texture_id.size();i++)
	{
		if (text == texture_id[i]) return i;
	}
	return 0;
}


void EntityList::handle_event(sf::Event &handleevent)
{
	player.handle_event(handleevent);
}
void EntityList::draw(sf::RenderWindow &window)
{
	player.draw(window);
	//ray.draw(window);
	/*for (int i = 0; i < bullets.size();i++)
	{
		bullets[i].draw(window);
	}*/
}
void EntityList::update(float delta, TileMap &tilemap)
{
	player.Update_prop(delta, tilemap);
	//ray.Update_Ray(tilemap);
	/*for (int i = 0; i < bullets.size();i++)
	{
		if (bullets[i].Update(delta, tilemap))
		{
			bullets.erase(bullets.begin() + i);
		}
		std::cout << i << std::endl;
	}*/
}

void EntityList::update_cursor_position(sf::Vector2f cursor_pos)
{
//	ray.Change_angle(cursor_pos);
	cursor_position = cursor_pos;
}

void EntityList::player_fire()
{
	//add_bullet(Projective::Projective(player.getPosition(), cursor_position,5000));
}