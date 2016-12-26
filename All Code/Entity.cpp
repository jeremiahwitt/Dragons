#include "Entity.h"

//!Default constructor
Entity::Entity()
{
}

//!Parameterized constructor
Entity::Entity(Race entityRace, int entityLevel)
{
	this->charRace = entityRace;
	this->charLevel = entityLevel;
}
//!Destructor
Entity::~Entity()
{}
