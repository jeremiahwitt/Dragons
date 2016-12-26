
#ifndef GAMELOGMENU_H
#define GAMELOGMENU_H
#include "menus.h"
#include <SDL.h>
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class GameLogMenu : public Menus
{
public:
	GameLogMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
};

#endif
