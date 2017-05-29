
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

#include "menu.h"
#include "play.h"

#ifndef game_h
#define game_h
class Game
{
public:
	Game();
	~Game();

	bool play();

private:

	const int FPS_RATE = 60;

	bool menu_open = true;
	bool options_open = false;
	bool game_open = false;

	bool events(Menu &menu, Play &play, sf::Event &events, sf::RenderWindow &window);
	bool update(float delta_time, Play &play);
	bool draw(Menu &menu, Play &play,sf::RenderWindow &window);
};

#endif