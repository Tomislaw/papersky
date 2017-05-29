#include "Entity\Entity.hpp"
#include "Map\EntityList.h"


Entity::Entity()
{

}


Entity::~Entity()
{
}


void Entity::Set_parent(Entity &set_parent)
{ 
	parent = &set_parent;
	is_attached_to_parent = true;
	
}

void Entity::Set_entity_list(EntityList &list)
{
	entlist = &list;

}
void Entity::Deattach_from_parent()
{

	is_attached_to_parent = false;
	setPosition(parent->getPosition());
	setRotation(parent->getRotation());
}

void Entity::Update(float delta_time)
{
	if(!is_attached_to_parent)
	{ 


	velocity += acceleration*((delta_time));
	if (!is_moving)
	{
		if (velocity.x >= 0)
		{
			if (velocity.x < slowdown.x)
			{
				velocity.x = 0;
			}
			else
			{
				velocity.x -= slowdown.x;
			}
		}
		else
		{
			if (velocity.x > -slowdown.x)
			{
				velocity.x = 0;
			}
			else
			{
				velocity.x += slowdown.x;
			}
		}
	}
	
	move(velocity*delta_time);

	//std::cout << "velocityx " << velocity.x << std::endl;
	//std::cout << "velocityy " << velocity.y << std::endl;
	}
	else
	{
	setPosition(parent->getPosition());
	setRotation(parent->getRotation());
	}
}