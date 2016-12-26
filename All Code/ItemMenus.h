#pragma once
#include "menus.h"
#include "Container.h"

using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class ItemMenus :
	public Menus
{
public:
	ItemMenus(std::string title);
	void setupMenu();
	int destinationMap(int index);
	~ItemMenus();
};

class PrintItemsMenus :
	public Menus
{
protected:
	Container * userContainer;
public:
	PrintItemsMenus(std::string title);
	void setupMenu();
	void setContainer(Container * userConatainer);
	int destinationMap(int index);
	~PrintItemsMenus();
};