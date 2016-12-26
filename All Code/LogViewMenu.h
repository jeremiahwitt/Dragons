
#ifndef LOGVIEWMENU_H
#define LOGVIEWMENU_H
#include "menus.h"
#include <SDL.h>
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class LogViewMenu : public Menus
{
public:
	LogViewMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
};

#endif