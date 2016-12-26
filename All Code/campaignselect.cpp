#include "campaignselect.h"

CampaignSelect::CampaignSelect(std::string title) :
Menus(title)
{
	this->_campaignNames = 	SingletonInputOutputManager::getInstance()->readFileLineByLine(SingletonFilePathAndFolderManager::getInstance()->_path_to_savedCampaignsList);
}
void CampaignSelect::setupMenu()
{
	std::string buttonbase = "Create / Edit Campaign";
	int totalwidth = this->_menuWindow->getWindowWidth() * (0.30);

	//set menu background color, and font
	this->_menuWindow->setFontType(9);
	this->_menuWindow->setTitleFontSize(72);
	this->_baseMenuColors[_MenuBackground_]->red;
	this->_menuWindow->setBackgroudColor(this->_baseMenuColors[_MenuBackground_]->red,this->_baseMenuColors[_MenuBackground_]->green,this->_baseMenuColors[_MenuBackground_]->blue);

	//put title in center
	SDL_Rect menucomponent;

	//title should be centrally aligned
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.65);
	menucomponent.x = this->_menuWindow->getWindowWidth()/2 - menucomponent.w/2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.05;
	this->_menuWindow->setTitle("SELECT CAMPAIGN", this->_baseMenuColors[_Title_]->red,this->_baseMenuColors[_Title_]->green,this->_baseMenuColors[_Title_]->blue, menucomponent);

	//go down 6 rectangle spaces
	menucomponent.y = menucomponent.y + menucomponent.h + (menucomponent.h*4);
	
	//now list names for all that exist, other wise display empty slot
	for(int x=0; x<_MaximumCampaigns_; x++)
	{
		//check if value exists in vector, if true add button with value
		if((x)< this->_campaignNames.size())
		{
			menucomponent.w = textWidthCalculator(_campaignNames[x], buttonbase, totalwidth);
			menucomponent.x = this->_menuWindow->getWindowWidth()/4 - menucomponent.w/2;
			this->_menuWindow->addButton(_campaignNames[x], this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		}
		//else add button non existent
		else
		{
			menucomponent.w = textWidthCalculator("Non Existent", buttonbase, totalwidth);
			menucomponent.x = this->_menuWindow->getWindowWidth()/4 - menucomponent.w/2;
			this->_menuWindow->addButton("Non Existent", this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		}
		//go down 1.5 rectangles
		menucomponent.y = menucomponent.y + menucomponent.h;
	}

	//now there has to be a button for main menu
	//go down 3 rectangles
	menucomponent.y = menucomponent.y + menucomponent.h;
	this->_menuWindow->addButton("Back to Main Menu", this->_baseMenuColors[_NoButtonSelect_]->red,this->_baseMenuColors[_NoButtonSelect_]->green,this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	this->_menuWindow->setMenuOnRenderer();
}
int CampaignSelect::destinationMap(int index)
{
	if(index < this->_campaignNames.size())
		return 1;
	else if(index == _MaximumCampaigns_)
		return _MainMenu_;
	return -1;
}
std::string CampaignSelect::getNameOfCampaignFromIndex(int index)
{
	if(index < this->_campaignNames.size())
		return this->_campaignNames[index];
	return "";
}