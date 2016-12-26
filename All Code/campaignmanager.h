/**
*@file campaignmanager.h
*@brief Provides CampaignManager class, used to manage campaigns in the CampaignMenu
*/
#if !defined ( CAMPAIGN_MANAGER_H )
#define CAMPAIGN_MANAGER_H
#include "menus.h"
#include "fileIOmanager.h"
#include "userinputandstringmanager.h"
#include "campaignmenus.h"
#include <conio.h>
#include <string>
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;
using namespace CampaignMaximums;
/*!
*@class CampaignManager
*@brief The instances of this class will be the main menu for campaign management.
*<p> Inherits from abstract class campaign menus and fully implements all functions
*/
class CampaignManager : public CampaignMenus 
{
protected:
	std::vector<std::string> _campaignNames;
public:
	CampaignManager();
	CampaignManager(std::string title);
	int destinationMap(int index);
	void setupMenu();
	int destinationMap(int index, char* componentname);
	std::string getNameOfButtonFromIndex(int index);
	void checkExistingComponentsIndexRange(int* lowerindex, int* upperindex);
};

#endif