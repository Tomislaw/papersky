#include "Entity\G_Sprite.hpp"

void Game_sprite::set_texture(sf::Texture &set_texture)
{
	sprite.setTexture(set_texture);
}


void Game_sprite::set_sprite_rectangle(const sf::IntRect &rectangle)
{
	sprite.setTextureRect(rectangle);
}

void Game_sprite::set_sprite(sf::Texture &set_texture, TextElement &spritetext)
{
	std::cout << std::endl;
	std::cout << "WHats goin on" <<set_texture.getSize().x << std::endl;;
	sprite.setTexture(set_texture);
	name = spritetext.get_variable_by_name("Name")->var[0];
	int startposx = atoi(spritetext.get_variable_by_name("Image_start")->var[0].c_str());
	int startposy = atoi(spritetext.get_variable_by_name("Image_start")->var[1].c_str());
	int sizex = atoi(spritetext.get_variable_by_name("Image_size")->var[0].c_str());
	int sizey = atoi(spritetext.get_variable_by_name("Image_size")->var[1].c_str());
	sf::IntRect default_rectangle(startposx, startposy, sizex, sizey);
	sprite.setTextureRect(default_rectangle);

	float scalex = atof(spritetext.get_variable_by_name("Scale")->var[0].c_str());
	float scaley = atof(spritetext.get_variable_by_name("Scale")->var[1].c_str());
	sprite.setScale(scalex,scaley);

	float centerx = atof(spritetext.get_variable_by_name("Center")->var[0].c_str());
	float centery = atof(spritetext.get_variable_by_name("Center")->var[1].c_str());
	sprite.setOrigin(centerx,centery);
}

void Game_sprite::Update_sprite(float &delta_time)
{
	sprite.setPosition(this->getPosition());
	Update(delta_time);
}

void Game_sprite::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}


Game_sprite::Game_sprite()
{
}

Game_sprite::~Game_sprite()
{
}