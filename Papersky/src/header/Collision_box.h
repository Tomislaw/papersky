#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H
#include "SFML\Graphics.hpp"
#include "Entity\Entity.hpp"

// Klasa odpowiedzialna za bry³e kolizji obiektu
/*
Czyœci wszystkie punkty z figury obiektu
void clear()

Dodaje punkt do bry³y kolizji 
void add_point(sf::Vector2f &point)

Ustawia punkt bry³y kolizji
void set_point(unsigned int index, sf::Vector2f &point)

Zwraca punkt relatywnie do œrodka
sf::Vector2f get_point_relative(unsigned int index)

Zwraca punkt wzglêdem mapy
sf::Vector2f get_point(unsigned int index)

Zwraca punkty relatywnie do œrodk
std::vector <sf::Vector2f> get_points_relative()

Zwraca punkty wzglêdem mapy
std::vector <sf::Vector2f> get_points()

Zwraca górne punkty kolizji
std::vector <sf::Vector2f> get_top_points(std::vector <int> &point)

Zwraca iloœæ wierzcho³ków bry³y
unsigned int size()

*/
class Collision_box :
	public Entity
{
public:
	Collision_box();
	~Collision_box();

	void clear()
	{
		collision_box.clear();
	}

	void add_point(sf::Vector2f &point)
	{
		collision_box.push_back(point);
	}
	void set_point(unsigned int index, sf::Vector2f &point)
	{
		collision_box[index] = point;
	}
	sf::Vector2f get_point_relative(unsigned int index)
	{
		return collision_box[index];
	}
	sf::Vector2f get_point(unsigned int index)
	{
		sf::Vector2f transformed_point(collision_box[index]+ getPosition());
		return transformed_point;
	}

	std::vector <sf::Vector2f> get_points_relative()
	{
		return collision_box;
	}
	std::vector <sf::Vector2f> get_points()
	{
		std::vector <sf::Vector2f> transformed_points;
		for (int i = 0; i < collision_box.size();i++)
		{
			sf::Vector2f transformed_point(collision_box[i] + getPosition());
			transformed_points.push_back(transformed_point);
		}
		return transformed_points;
	}



	std::vector <sf::Vector2f> get_top_points(std::vector <int> &point)
	{
		std::vector <sf::Vector2f> points;
		if (point.size() == 0) points.push_back(sf::Vector2f(0, 0));
		for (int i = 0; i < point.size();i++)
		{
			points.push_back(get_point(point[i]));
		}
		return points;
	}

	unsigned int size()
	{
		return collision_box.size();
	}
	
protected:
	std::vector <sf::Vector2f> collision_box;
};

#endif