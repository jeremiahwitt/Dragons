/**
*@file DisplayPlayerStatsWindow.h
*@brief Provides declaration of menu which will display ONLY the player's
*/

#ifndef DISPLAYPLAYERSTATSWINDOW_H
#define DISPLAYPLAYERSTATSWINDOW_H
#include "menus.h"
#include "Fighter.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class DisplayPlayerStatsWindow : public Menus {
private:
	Fighter* _theFighter; //! Stores the Fighter that will be editted.
public:
	DisplayPlayerStatsWindow(std::string title, Fighter* theFighter);
	void setupMenu();
	int destinationMap(int index);
};

#endif