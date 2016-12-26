/**
*@file ItemFactory.h
*@brief Provides ItemFactory class, used to create blank prototype item of any time.
*/
#pragma once
#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H
#include "Item.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "namespaces.h"

/**
*@class ItemFactory.h
*@brief Used to create blank prototype items that will be filled in during serialization
*/
class ItemFactory {
public:
	static Item* create(int flag);
};

#endif