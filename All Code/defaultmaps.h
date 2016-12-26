/**
*@file defaultmaps.h
*@brief Provides Singleton Class for managing default maps
*/
#if !defined (DEFAULT_MAPS_MENU_H)
#define DEFAULT_MAPS_MENU_H
#include "campaignmenus.h"
#include "menuengine.h"
#include "userinputandstringmanager.h"
/*!
*@class SingletonDefaultMapsMenu
*singleton class that inherits from campaign menus. this is the menu
*for selecting a default map that could be added into a user created campaign
*/
class SingletonDefaultMapsMenu : public CampaignMenus
{
private:
	static SingletonDefaultMapsMenu* _menuInstance;
	std::vector<std::string> _mapListDataBase;
	SingletonDefaultMapsMenu(std::string title);
public:
	void setupMenu();
	int destinationMap(int index);
	int destinationMap(int index, char* componentname);
	std::string getNameOfButtonFromIndex(int index);
	void checkExistingComponentsIndexRange(int* lowerindex, int* upperindex);
	static SingletonDefaultMapsMenu* getInstance();
	~SingletonDefaultMapsMenu();
};
#endif