/**
*@file AddUserMadeItemsConfMenu.h
*@brief Declares a menu which will ask the user if they want to add user-generated items to their character
*/

#ifndef ADDUSERMADEITEMSCONFMENU_H
#define ADDUSERMADEITEMSCONFMENU_H
#include "menus.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class AddUseMadeItemsConfirmationMenu : public Menus {

public:
	AddUseMadeItemsConfirmationMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
};

#endif