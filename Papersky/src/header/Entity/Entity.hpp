
#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
class EntityList;
// Entity - klasa odpowiedzialna za podstawowy byt gry
/*
Przyczepia obiekt do innego obiektu
void Set_parent(Entity & set_parent);

Odczepia obiekt od obiektu
void Deattach_from_parent();

Uaktualnia pozycje bytu
void Update(float delta_time);
*/
class Entity :
	public sf::Transformable
{
public:
	Entity();
	~Entity();

	void Set_entity_list(EntityList & list);
	void Set_parent(Entity & set_parent);
	void Deattach_from_parent();
virtual	void Update(float delta_time);

protected:

	std::string name;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f slowdown;

	sf::Vector2f move_vector;
	Entity * parent;

	EntityList * entlist;
	
	

	bool is_moving = false;
	bool is_attached_to_parent = false;
};

#endif