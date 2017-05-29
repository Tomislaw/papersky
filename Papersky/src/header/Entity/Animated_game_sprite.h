#ifndef ANIMATED_GAME_SPRITE_H
#define ANIMATED_GAME_SPRITE_H
#include "Entity\G_Sprite.hpp"
#include "FileManager\TextFileData.h"
#include "animation.hpp"
#include <iostream>
class Animated_game_sprite :
	public Game_sprite
{
public:
	Animated_game_sprite();
	~Animated_game_sprite();
	
	Animated_game_sprite::Animated_game_sprite(const sf::Texture &set_texture, const std::string &texture_localization, const sf::IntRect &rectangle);
	Animated_game_sprite::Animated_game_sprite(sf::Texture &set_texture, TextElement &sprite);
	void set_animated_sprite(sf::Texture &set_texture, TextElement &sprite);
	void set_animation(int a);
	void set_animation(const std::string &animation_name);

	void Update_animated_sprite(float delta_time);

protected:
	int current_animation;
	std::vector < Animation > animationsheet;

};

#endif