/**
*@file EditRaceMenu.h
*@brief Provides declaration of EditRaceMenu class, which will allow the user to edit the Race of a Character
*/

#ifndef EDITRACEMENU_H
#define EDITRACEMENU_H
#include "menus.h"
#include "Fighter.h"
#include "Entity.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class EditRaceMenu : public Menus {

public:
	EditRaceMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
};

#endif