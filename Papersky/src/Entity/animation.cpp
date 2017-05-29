#include "Entity\animation.hpp"
Animation::Animation()
{
	is_loop = true;
	animation_speed = 0.1;
	sprite_size.x = 32;
	sprite_size.y = 32;
	sf::Vector2i frame0(0, 0);
	sf::Vector2i frame1(32, 0);
	sf::Vector2i frame2(64, 0);
	sf::Vector2i frame3(96, 0);
	animation_frame.push_back(frame0);
	animation_frame.push_back(frame1);
	animation_frame.push_back(frame2);
	animation_frame.push_back(frame3);
}

Animation::Animation(const std::string &Name, float anim_speed, const sf::Vector2i & Sprite_size)
{
	is_loop = true;
	animation_speed = anim_speed;
	sprite_size = Sprite_size;
}

Animation::Animation(const std::string &Name, float anim_speed, const sf::Vector2i & Sprite_size, const std::vector < sf::Vector2i > &Frame)
{
	name = Name;
	is_loop = true;
	animation_speed = anim_speed;
	sprite_size = Sprite_size;
	for (int i = 0; i < Frame.size(); i++)
	{
		animation_frame.push_back(Frame[i]);
	}
}

void Animation::Push_back_frame(const sf::Vector2i &frame)
{
	animation_frame.push_back(frame);
}

sf::IntRect Animation::get_current_rectangle(float delta_time)
{

	if (animation_speed*animation_frame.size() > current_time)
	{
		current_frame = current_time/animation_speed;
	}

	if (current_frame > animation_frame.size())
	{
		current_frame = 0;

	}

	if (animation_speed*animation_frame.size() < current_time)
	{
		current_time = 0;
	}

	current_time += delta_time;

	 sf::IntRect frame(animation_frame[current_frame], sprite_size);
	return frame;
}

sf::IntRect Animation::get_first_rectangle()
{
	sf::IntRect frame(animation_frame[0], sprite_size);
	return frame;
}

Animation::~Animation()
{
}