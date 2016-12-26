/**
*@file campaignMAPmanagers.h
*@brief Provides declaration of class used to manage campaign maps
*/

#if !defined ( CAMPAIGN_MAP_MANAGER_H )
#define CAMPAIGN_MAP_MANAGER_H
#include "campaignmanager.h"
#include "menuengine.h"
#include <list>
using namespace Others;
/*!
*@class CampaignMapManagers
*@brief Instances of this class would be a menu for a specific campaign. 
*<p> This class inherits from the campaign manager, the intention being polymorphic usage of the menu engine.
*/
class CampaignMapManagers : public CampaignManager
{
private:
	std::vector<std::string> _mapnames;
	std::vector<std::string> _mappaths;
	std::vector<std::string> _allCampaignDatabase;
	std::string _campaignName;

public:
	CampaignMapManagers();
	CampaignMapManagers(std::string title, std::string componentname);
	void setupMenu();
	bool setMapNames(std::vector<std::string> names);
	bool checkIfProposedMapNameInDatabase(std::string newmap);
	bool checkIfMapdatabaseIsLessThanMax();
	int destinationMap(int index, char* campaignname);
	std::string getNameOfButtonFromIndex(int index);
	std::string getCampaignNameOfMap();
	void sucessfullMapCreated(bool success);
	void checkExistingComponentsIndexRange(int* lowerindex, int* upperindex);
	void changeSequence(int index1, int index2);
};

#endif