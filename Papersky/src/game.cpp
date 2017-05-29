#include "header\game.h"
Game::Game()
{

}

bool Game::play()
{


///////////////////////Ustawienia ekranu
	sf::Vector2f view_size(1000, 1000);
	sf::RenderWindow window(sf::VideoMode(view_size.x, view_size.y), "Papersky", sf::Style::Default);
	Menu menu(window.getSize().x, window.getSize().y);
	Play play(window.getSize().x, window.getSize().y);

//	window.setMouseCursorVisible(false);

////////////////////////////ustawienia ekranu

////////////////////////Ustawienia petli gry
	//window.setFramerateLimit(FPS_RATE);

	long double delta = 0.00;
	long double frame_time = 0.00;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / FPS_RATE);
	sf::Event event;

	while (window.isOpen())
	{
		delta = timeSinceLastUpdate.asSeconds();
		timeSinceLastUpdate += clock.restart();


		while (timeSinceLastUpdate > TimePerFrame)
		{
			frame_time = delta;
			events(menu,play,event,window);

			update(delta, play);
	
			timeSinceLastUpdate -= TimePerFrame;
		}
		window.clear(sf::Color::White);
		
		draw(menu, play, window);
		window.display();

	}


	return 0;
}


bool Game::events(Menu &menu, Play &play, sf::Event &event, sf::RenderWindow &window)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{

			// Obsluga nacisniecia klawisza
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				if (menu_open == true)menu.MoveUp();
				break;

			case sf::Keyboard::Down:
				if (menu_open == true)menu.MoveDown();
				break;

			case sf::Keyboard::Escape:
				if (game_open == true)
				{
					menu_open = true;
					game_open = false;
					window.setView(window.getDefaultView());
				}

				//window.close();
				break;

				// Obsluga klawisza Escape
			case sf::Keyboard::Return:
				if(menu_open)
				{
				switch (menu.GetPressedItem())
				{
				case 0:
					game_open = true;
					menu_open = false;
					break;
				case 1:
					window.close();
					break;
				case 2:
					window.close();
					break;
				}
				}
				break;
			}
			break;

			// Obs³uga 


		case sf::Event::Closed:
			window.close();

			break;

		}
	}

	if (game_open) play.handle_event(window,event);
	return 0;
}

bool Game::update(float delta, Play &play)
{
	if (game_open)play.update(delta);
	return 0;
}

bool Game::draw(Menu &menu, Play &play, sf::RenderWindow &window)
{
	if (menu_open)menu.draw(window);
	if (game_open)play.draw(window);
	return 0;
}

Game::~Game()
{
}
