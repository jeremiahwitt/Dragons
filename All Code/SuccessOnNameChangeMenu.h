/**
*@file SuccessOnNameChangeMenu.h
*@brief Declares menu that displays a successful name change
*/
#include "menus.h"
#include "Fighter.h"

#ifndef SUCCESSONNAMECHANGEMENU_H
#define SUCCESSONNAMECHANGEMENU_H

using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class SuccessOnNameChangeMenu : public Menus {
private:
	Fighter* _theFighter;
public:
	SuccessOnNameChangeMenu(std::string title, Fighter* theFighter);
	void setupMenu();
	int destinationMap(int index);
};

#endif
