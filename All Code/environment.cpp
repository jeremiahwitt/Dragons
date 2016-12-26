#include "environment.h"

//!parameterized constructor, first calls parent constructor and initializes the added features
Environment::Environment(std::string componentname, std::string description, char componentchar, gameplayGridComponentTypes componenttype, bool obstructiontoplayer, std::string imagepath) 
	: GameComponent(componentname, componentchar, componenttype, imagepath)
{
	this->_obstructionToPlayer = obstructiontoplayer;
	this->_description = description;
}

//!returns if the component is obstruction to player or not
bool Environment::isComponentObstructionToPlayer()
{
	return this->_obstructionToPlayer;
}

//!returns the details of the environment as a string
std::string Environment::getEnvironmentDescription()
{
	return this->_description;
}

//!sets the obstruction boolean
void Environment::setObstructionToPlayer(bool isobstructiontoplayer)
{
	this->_obstructionToPlayer = isobstructiontoplayer;
}

//!calls the destroy component of parent class
Environment::~Environment()
{
	destroyComponent();
}