#include "Entity\Animated_game_sprite.h"



Animated_game_sprite::Animated_game_sprite()
{
	name = "Animated_game_sprite";
	sf::IntRect default_rectangle(0, 0, 32, 32);
	sprite.setTextureRect(default_rectangle);
	sf::Vector2i sprite_size(32, 32);
	sf::Texture texture;
	sprite.setTexture(texture);
//	Animation defaultanimation("idle", 0.5, sprite_size);
//	sf::Vector2i default0(0, 0);
//	sf::Vector2i default1(32, 0);
	//defaultanimation.Push_back_frame(default0);
	//defaultanimation.Push_back_frame(default1);

	//animationsheet.push_back(defaultanimation);
	sprite.setOrigin(16, 16);
}
Animated_game_sprite::Animated_game_sprite(const sf::Texture &set_texture, const std::string &texture_localization, const sf::IntRect &rectangle)
{


}
Animated_game_sprite::Animated_game_sprite(sf::Texture &set_texture, TextElement &sprite)
{


}
void Animated_game_sprite::set_animated_sprite(sf::Texture &set_texture, TextElement &spritetext)
{
	set_sprite(set_texture, spritetext);
	int count = 0;
	TextFileData anim;
	anim.read_file("game/animations.txt");
	auto animation = anim.get_first_element_by_name("ANIMATION");
	count = atoi(animation->get_variable_by_name("Animations_count")->var[0].c_str());
	for (int i = 0; i < count; i++)
	{
		std::string animation_name = "Animation_" + std::to_string(i);
		std::string set_name = animation->get_variable_by_name(animation_name)->var[0];
		float animation_speed = atof(animation->get_variable_by_name(animation_name+"_speed")->var[0].c_str());

		sf::Vector2i size;
		size.x = sprite.getTextureRect().width;
		size.y = sprite.getTextureRect().height;
		Animation add_animation(set_name, animation_speed, size);

		int frame_count = 0;
		frame_count = atoi(animation->get_variable_by_name(animation_name + "_frames")->var[0].c_str());
		for(int j = 0; j < frame_count;j++)
		{ 
			std::string framename = animation_name + "_frame_";
			framename += std::to_string(j);
			int framea = atoi(animation->get_variable_by_name(framename)->var[0].c_str());
			int frameb = atoi(animation->get_variable_by_name(framename)->var[1].c_str());
		//	int framec = atoi(animation.get_variable_by_name(framename).var[2].c_str());
		//	int framed = atoi(animation.get_variable_by_name(framename).var[3].c_str());
			add_animation.Push_back_frame(sf::Vector2i(framea, frameb));
		}

		animationsheet.push_back(add_animation);;
	}

}

Animated_game_sprite::~Animated_game_sprite()
{
}


void Animated_game_sprite::set_animation(int a)
{
	current_animation = a;
}
void Animated_game_sprite::set_animation(const std::string &animation_name)
{
	for (int i = 0; i < animationsheet.size(); i++)
	{
		if (animationsheet[i].get_name() == animation_name) 
		{ 
			current_animation = i; 
			break;
		}
	}
}

void Animated_game_sprite::Update_animated_sprite(float delta_time)
{
	if (animationsheet.size() > 0)
	{
		sprite.setTextureRect(animationsheet[current_animation].get_current_rectangle(delta_time));

	};
	Update_sprite(delta_time);
}
