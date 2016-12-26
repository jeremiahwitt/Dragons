/**
*@file mainmenu.h
*@brief Provides access to MainMenu class
*/
#if !defined ( MAINMENU_H )
#define MAINMENU_H
#include "menus.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;
/*!
*@class MainMenu
*The instance of this class will be the main menu for assignment 2, inherits from abstract class menus
*/
class MainMenu : public Menus
{
public:
	MainMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
};

#endif