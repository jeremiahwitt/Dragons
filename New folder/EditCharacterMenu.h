/**
*@file EditCharacterMenu.h
*@brief Provides definition of the Editing Character Menu
*/

#ifndef EDITCHARACTERMENU_H
#define EDITCHARACTERMENU_H
#include "menus.h"
#include "Fighter.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class EditCharacterMenu : public Menus {
private:
	Fighter* _theFighter; //! Stores the Fighter that will be editted.
public:
	EditCharacterMenu(std::string title, Fighter* theFighter);
	void setupMenu();
	int destinationMap(int index);
};

#endif