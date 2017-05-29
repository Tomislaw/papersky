#include "Cursor.hpp";
Cursor::Cursor()
{
	Cursor_texture.loadFromFile("textures/HUD/cursor.png");
	Cursor_Sprite.setTexture(Cursor_texture);
	Cursor_Sprite.setOrigin(8, 8);
	Cursor_Sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

}

void Cursor::draw(sf::RenderWindow &window, sf::Vector2f &camera_offset)
{
	//std::cout << "Mouse x " << sf::Mouse::getPosition().x << " y " << sf::Mouse::getPosition().y << std::endl;
	Cursor_Sprite.setPosition(sf::Mouse::getPosition(window).x + camera_offset.x, sf::Mouse::getPosition(window).y + camera_offset.y);
	window.draw(Cursor_Sprite);
}


Cursor::~Cursor()
{
}