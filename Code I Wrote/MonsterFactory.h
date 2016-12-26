/**
*@file MonsterFactory.h
*@brief Creates a randomly generated monster, based upon player level
*/
#pragma once
#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H
#include "Monster.h"

/**
*@class MonsterFactory
*@brief allows for the creation of a random monster, based on the level of the Character provided to it
*/
class MonsterFactory{
public:
	static Monster* createMonster(Fighter* theChar, bool friendFlag);
	
};

#endif
