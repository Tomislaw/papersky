#include "menu.h"


	Menu::Menu(float w, float h)
{
	width = w;
	height = h;
	if (!menu1.loadFromFile("fonts/arial.ttf"))
	{
		// handle error
	}
	if (!menu2.loadFromFile("fonts/mainmenu.ttf"))
	{
		// handle error
	}

	title.setFont(menu2);
	title.setColor(sf::Color::Black);
	title.setString(L"Papersky");
	title.setCharacterSize(height / 15);
	title.setPosition(sf::Vector2f(title.getCharacterSize(), title.getCharacterSize()));

	menu.push_back(MenuLabel(std::string("Play"),menu1, sf::Vector2f(width/2,300)));
	//menu.push_back(MenuLabel(std::string("Opcje"), menu1, sf::Vector2f(width / 2, 350)));
	menu.push_back(MenuLabel("Exit", menu1, sf::Vector2f(width / 2, 350)));
	menu[0].set_selected_state(true);


	selectedItemIndex = 0;


	// Ładowanie tła
	texture_tlo.loadFromFile("textures/menu/tlo.png");
	sprite_tlo.setTexture(texture_tlo);
	sprite_tlo.setPosition(0, 0);
	sprite_tlo.setScale((width + 2) / 1024, (width + 2) / 1024);



}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{


	window.draw(sprite_tlo);
	window.draw(title);

	for (int i = 0; i < menu.size(); i++)
	{
		menu[i].draw(window);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].set_selected_state(false);
		selectedItemIndex--;
		menu[selectedItemIndex].set_selected_state(true);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < menu.size())
	{
		menu[selectedItemIndex].set_selected_state(false);
		selectedItemIndex++;
		menu[selectedItemIndex].set_selected_state(true);
	}
}



/*
void Menu::push_menu(std::string text, sf::Vector2f position)
{
	sf::Text menu_label;
	menu_label.setFont(menu1);
	menu_label.setColor(sf::Color::White);
	menu_label.setString(text);
	menu_label.setOrigin(sf::Vector2f(menu_label.getCharacterSize()/2,0));
	menu_label.setPosition(position);
	menu.push_back(menu_label);
}

*/








//////////////////////////////////////////////



MenuLabel::MenuLabel(std::string string, sf::Font &setfont, sf::Vector2f position)
{
	text.setFont(setfont);
	text.setColor(sf::Color::Black);
	text.setString(string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width/2, 0));
	text.setPosition(position);

	sf::Vector2f lefttop(text.getGlobalBounds().left-100, text.getGlobalBounds().top-5);
	sf::Vector2f leftbottom(text.getGlobalBounds().left-100, text.getGlobalBounds().top + text.getGlobalBounds().height+5);
	sf::Vector2f middlebottom(text.getPosition().x, text.getGlobalBounds().top + text.getGlobalBounds().height + 5);
	sf::Vector2f rightbottom(text.getGlobalBounds().left + text.getGlobalBounds().width+100, text.getGlobalBounds().top + text.getGlobalBounds().height+5);
	sf::Vector2f righttop(text.getGlobalBounds().left + text.getGlobalBounds().width + 100, text.getGlobalBounds().top - 5);
	sf::Vector2f middletop(text.getPosition().x, text.getGlobalBounds().top - 5);

	rectangle[0] = sf::Vertex(lefttop, sf::Color(255,255,255,0)),
	rectangle[1] = sf::Vertex(leftbottom, sf::Color(255, 255, 255, 0)),
	rectangle[2] = sf::Vertex(middletop, sf::Color(255, 255, 255, 200)),
	rectangle[3] = sf::Vertex(middlebottom, sf::Color(255, 255, 255, 200)),
	rectangle[4] = sf::Vertex(righttop, sf::Color(255, 255, 255, 0));
	rectangle[5] = sf::Vertex(rightbottom, sf::Color(255, 255, 255, 0));
}

MenuLabel::~MenuLabel()
{
}

void MenuLabel::draw(sf::RenderWindow &window)
{
	window.draw(rectangle, 6, sf::TrianglesStrip);
	window.draw(text);
}

void MenuLabel::set_selected_state(bool state)
{
	if (state)
	{
		text.setColor(sf::Color::Red);
		rectangle[2].color = sf::Color(255, 180, 180, 200);
		rectangle[3].color = sf::Color(255, 180, 180, 200);
	}
	else
	{
		text.setColor(sf::Color::Black);
		rectangle[2].color = sf::Color(255, 255, 255, 200);
		rectangle[3].color = sf::Color(255, 255, 255, 200);
	}
}