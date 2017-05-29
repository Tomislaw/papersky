#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <iostream>
#include <SFML\Graphics.hpp>
#include <algorithm>

struct Wall
{
	sf::Vector2f A;
	sf::Vector2f B;
	float distance;
};
Wall operator >(Wall & wall1, Wall & wall2);
Wall operator <(Wall & wall1, Wall & wall2);



bool check_line_collision(sf::Vector2f &Line1A, sf::Vector2f &Line1B, sf::Vector2f &Line2A, sf::Vector2f &Line2B);
double det_matrix(sf::Vector2f &x, sf::Vector2f &y, sf::Vector2f &z);
bool same_line(sf::Vector2f &x, sf::Vector2f &y, sf::Vector2f &z);
bool check_lines(sf::Vector2f &A, sf::Vector2f &B, sf::Vector2f &X, sf::Vector2f &Y);
 sf::Vector2f &check_collision_with_line( std::vector <sf::Vector2f> &shape,  sf::Vector2f &A,  sf::Vector2f &B);
sf::Vector2i check_collision(sf::ConvexShape &shapeX, sf::ConvexShape &shapeY);
bool intersects_convex(std::vector<sf::Vector2f> &shape, sf::Vector2f &point);

unsigned int get_nearest_wall(std::vector<sf::Vector2f> &shape, sf::Vector2f &point);

std::vector <Wall> get_sorted_walls(std::vector<sf::Vector2f> &shape, sf::Vector2f &point);
bool check_and_get_lines_intersection( std::vector<sf::Vector2f> &shape,  sf::Vector2f p2,  sf::Vector2f p3, sf::Vector2f &position);
bool check_and_get_line_intersection(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f &i);

#endif