
#ifndef TOGGLELOGMENU_H
#define TOGGLELOGMENU_H
#include "menus.h"
#include <SDL.h>
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class ToggleLogMenu : public Menus
{
public:
	ToggleLogMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
};

#endif