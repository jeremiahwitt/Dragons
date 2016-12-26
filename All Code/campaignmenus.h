/**
*@file campaignmenus.h
*@brief Provides access to CampaignMenus
*/
#if !defined ( CAMPAIGN_MENUS_H )
#define CAMPAIGN_MENUS_H
#include "menus.h"
#include <string>
/*!
*@class CampaignMenus
*abstract class inherits from menus. designed for creating and running menus primarily
*for creation and editing of campaigns.
*/
class CampaignMenus : public Menus
{
public:
	CampaignMenus()
	{
	}
	CampaignMenus(std::string title) : Menus(title)
	{
	}
	virtual int destinationMap(int index, char* componentname) = 0;
	virtual std::string getNameOfButtonFromIndex(int index) = 0;
	virtual void checkExistingComponentsIndexRange(int* lowerindex, int* upperindex) = 0;
};

#endif