/**
*@file ContainerGenerator.h
*@brief Allows random generation of containers based on player level
*/
#ifndef CONTAINER_GENERATOR_H
#define CONTAINER_GENERATOR_H

#include <vector>
#include "Container.h"
#include "Fighter.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"

/**
*@class ContainerGenerator
*@brief Allows you to randomly generate containers
*/
class ContainerGenerator :
	public Container
{
public:
	ContainerGenerator();
	~ContainerGenerator();
	static Container * generateContainer(Fighter* fighter);
	static const std::vector<std::string> MELEE_WEAPON_NAMES;
	static const std::vector<std::string> RANGED_WEAPON_NAMES;
	static const std::vector<std::string> ARMOR_NAMES;
	static const std::vector<std::string> BELT_NAMES;
	static const std::vector<std::string> BOOTS_NAMES;
	static const std::vector<std::string> HELMET_NAMES;
	static const std::vector<std::string> RING_NAMES;
	static const std::vector<std::string> SHIELD_NAMES;
	static const std::vector<std::string> ATTACK_DICE;
};

#endif // !CONTAINER_GENERATOR_H