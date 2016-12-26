#ifndef ITEM_CREATOR_H
#define ITEM_CREATOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <afx.h>
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Container.h"

// don't use the windows.h max
#undef max

class ItemCreator {
public:
	static void createItems(Container * userContainer, int userChoice);
	static void createWeapon(Container * userContainer);
	static void createArmour(Container * userContainer);
	static void createShield(Container * userContainer);
	static void createBelt(Container * userContainer);
	static void createBoots(Container * userContainer);
	static void createHelmet(Container * userContainer);
	static void createRing(Container * userContainer);
	static std::string printItems(Container * container);
	static void randomlyGenerateItems(Container * userContainer);
	static void loadItemsFromFile(Container * userContainer);
	static void saveItemsToFile(Container * container);
};

#endif