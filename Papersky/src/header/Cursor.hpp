#ifndef CURSOR_H
#define CURSOR_H
#include "SFML\Graphics.hpp"
#include <iostream>


//Klasa s³u¿¹ca do wyœwietlania kursora, obecnie nieu¿ywana
class Cursor
{
public:
	Cursor();
	~Cursor();
	void draw(sf::RenderWindow &window, sf::Vector2f &camera_offset);
	sf::Vector2f get_position()
	{
		return Cursor_Sprite.getPosition();
	}

private:
	sf::Texture Cursor_texture;
	sf::Sprite Cursor_Sprite;
};

#endif