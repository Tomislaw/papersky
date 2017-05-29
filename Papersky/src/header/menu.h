#ifndef menu_h
#define menu_h
#include "SFML/Graphics.hpp"



class MenuLabel
{
public:
	MenuLabel(std::string text, sf::Font &setfont, sf::Vector2f position);
	~MenuLabel();
	void draw(sf::RenderWindow &window);
	void set_selected_state(bool state);
private:
	sf::Text text;
	sf::Vertex rectangle[6];
};



class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	void push_menu(std::string text, sf::Vector2f position);
	int selectedItemIndex;
	sf::Font menu1;
	sf::Font menu2;

	std::vector <MenuLabel> menu;
	sf::Text title;

	sf::Texture texture_tlo;
	sf::Sprite sprite_tlo;
	float width = 0;
	float height = 0;
};





#endif