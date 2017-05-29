#ifndef PLAYER_H
#define PLAYER_H

#include "Entity\Prop.hpp"
#include "Map\TileMap.h"
#include <iostream>
#include <string>

//#include "game_sprite.h"



////////// Przestarzale
/*
class player :
	public game_object
{
public:
	player();
	player(float x, float y);
	~player();
	void move_left();
	void move_right();

	//void move(float x, float y);
	void p_update(float &deltatime);
	void p_draw(sf::RenderWindow &window);
	//Settery
	void set_is_moving(bool x) { is_moving = x; }

protected:

	bool is_moving = false;

};
*/


class Player :
	public Prop
{
public:
	Player();
	~Player();
	//bool set_prop(TextElement &prop, std::vector <TextElement> &sprite_types, sf::Texture &texture);
	virtual void Update_prop(float &delta_time, TileMap &tilemap);
	
	bool set_player(TextElement &setplayer, sf::Texture &texture);
	void handle_event(sf::Event &handleevent);
	void set_is_moving(bool x) { is_moving = x; }
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void fire();
	bool face_left = false;
private: 

};

#endif