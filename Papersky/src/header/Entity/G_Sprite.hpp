#ifndef G_SPRITE_H
#define G_SPRITE_H
#include "Entity.hpp"
#include "FileManager\TextFileData.h"

class Game_sprite :
	public Entity
{
public:
	Game_sprite();
	~Game_sprite();

	void set_texture(sf::Texture &set_texture);
	void set_texture_localization(const std::string &texture_localization);
	void set_sprite_rectangle(const sf::IntRect &rectangle);
	void Game_sprite::set_sprite(sf::Texture &set_texture, TextElement &spritetext);

	void Update_sprite(float &delta_time);

	void Set_sprite_orgin(sf::Vector2f orgin)
	{
		sprite.setOrigin(orgin);
	}
	void draw(sf::RenderWindow &window);

protected:
	sf::Sprite sprite;
};
#endif