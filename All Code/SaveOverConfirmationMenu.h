/**
*@file SaveOverConfirmationMenu.h
*@brief Provides declaration of Menu which will confirm if user wants to save over a pre-existing Character
*/

#ifndef SAVEOVERCONFIRMATIONMENU_H
#define SAVEOVERCONFIRMATIONMENU_H
#include "menus.h"
#include "Fighter.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class SaveOverConfirmationMenu : public Menus {
private:
	Fighter* theFighter;
public: 
	SaveOverConfirmationMenu(std::string title, Fighter* theFighter);
	void setupMenu();
	int destinationMap(int index);
};


#endif