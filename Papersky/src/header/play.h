// Play - klasa odpowiedzialna za czêœægry
/*
uaktualnia wszystkie obiekty z grze
void update(float &delta_time);

Rysuje wszystkie obiekty w grze
void draw(sf::RenderWindow &window);

Zajmuje siê eventami w grze - klawiatura
void handle_event(sf::RenderWindow &window, sf::Event &handleevent);

void PressingArrowLeft();
void PressingArrowRight();
void PressingArrowUp();
void PressingArrowDown();
void PressingSpace();
void NotPressingMoveKeys();
*/


#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

#include "Map\Map.h"
#ifndef play_h
#define play_h



class Play
{
public:
	Play(float width, float height);
	~Play();

	void update(float &delta_time);
	void draw(sf::RenderWindow &window);
	void handle_event(sf::RenderWindow &window, sf::Event &handleevent);
	void PressingArrowLeft();
	void PressingArrowRight();
	void PressingArrowUp();
	void PressingArrowDown();
	void PressingSpace();
	void NotPressingMoveKeys();

private:


	float width = 0; 
	float height = 0;
	int player_number = 0;
	Map map0;

;
};

#endif;