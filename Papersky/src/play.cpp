
#include "header\play.h"

Play::Play(float width, float height)
{
}


Play::~Play()
{

}


void Play::update(float &delta_time)
{
	map0.update(delta_time);
	

}

void Play::draw(sf::RenderWindow &window)
{

	map0.draw(window);

}
void Play::handle_event(sf::RenderWindow &window, sf::Event &handleevent)
{
	map0.handle_event(handleevent);
}
