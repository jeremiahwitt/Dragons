#pragma once
#include "game_components.h"
/*!
*@class Environment
* derived class of game component.
* two attributes added, one is if the environment component
* is obstruction to player or not
* and the description of the environment
*/
class Environment : public GameComponent
{
protected:
	std::string _description;

public:
	Environment(std::string componentname, std::string description, char componentchar, gameplayGridComponentTypes componenttype, bool obstructiontoplayer, std::string imagepath);
	void setObstructionToPlayer(bool isobstructiontoplayer);
	std::string getEnvironmentDescription();
	bool isComponentObstructionToPlayer();
	~Environment();
};