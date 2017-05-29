#ifndef options_h
#define options_h
#include <SFML/Graphics.hpp>
#define MENU_COUNT 3
class options
{
public:
	options();
	~options();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font menu1;
	sf::Font menu2;
	sf::Text menu[MENU_COUNT];
	sf::Text title;
	sf::Texture texture_tlo;
	sf::Sprite sprite_tlo;
	float width = 0;
	float height = 0;
};

#endif