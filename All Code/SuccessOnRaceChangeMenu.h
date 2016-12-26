/**
*@file SuccessOnRaceChangeMenu.h
*@brief Declares menu which displays that race change was successful!
*/

#ifndef SUCCESSONRACECHANGEMENU_H
#define SUCCESSONRACECHANGEMENU_H

#include"menus.h"
#include "Fighter.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class SuccessOnRaceChangeMenu : public Menus {
private:
	Fighter* _theFighter;
public:
	SuccessOnRaceChangeMenu(std::string title, Fighter* theFighter);
	void setupMenu();
	int destinationMap(int index);
};

#endif