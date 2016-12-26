#/**
*@file CharacterCreateEditMenu.h
*@brief Provides definition of the Character Creation and Editing Menu
*/

#ifndef CHARACTERCREATEEDITMENU_H
#define CHARACTERCREATEEDITMENU_H
#include "menus.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class CharacterCreateEditMenu : public Menus {
public:
	CharacterCreateEditMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
};

#endif