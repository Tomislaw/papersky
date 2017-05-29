#ifndef ANIMATION_H
#define ANIMATION_H
#include "SFML/Graphics.hpp"
#include <iostream>

class Animation
{
public:
	Animation();
	Animation(const std::string &Name, float anim_speed, const sf::Vector2i & Sprite_size);
	Animation(const std::string &Name, float anim_speed, const sf::Vector2i &Sprite_size, const std::vector < sf::Vector2i > &Frame);

	void Push_back_frame(const sf::Vector2i &frame);

	sf::IntRect get_current_rectangle(float delta_time);
	sf::IntRect get_first_rectangle();

	std::string get_name()
	{
		return name;
	}

	~Animation();

private:
	std::string name;
	float animation_speed = 0;
	float current_time = 0;
	int current_frame = 0;
	sf::Vector2i sprite_size;
	std::vector < sf::Vector2i > animation_frame;
	bool is_loop;
};

#endif