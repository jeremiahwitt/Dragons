/**
*@file campaignselect.h
*@brief
*/
#if !defined ( CAMPAIGNMENU_H )
#define CAMPAIGNMENU_H
#include "menus.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;
using namespace CampaignMaximums;
/*!
*@class CampaignSelect
*The instance of this class will be the main menu for assignment 2, inherits from abstract class menus
*/
class CampaignSelect : public Menus
{
private:
	std::vector<std::string> _campaignNames;
public:
	CampaignSelect(std::string title);
	void setupMenu();
	int destinationMap(int index);
	std::string getNameOfCampaignFromIndex(int index);
};

#endif