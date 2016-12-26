#include "defaultmaps.h"

//!singleton default menu instance
SingletonDefaultMapsMenu* SingletonDefaultMapsMenu::_menuInstance = nullptr;

//!constructor should take care of creating the menu
SingletonDefaultMapsMenu::SingletonDefaultMapsMenu(std::string title) : CampaignMenus(title)
{
	this->_mapListDataBase = SingletonInputOutputManager::getInstance()->readFileLineByLine(SingletonFilePathAndFolderManager::getInstance()->_path_to_default_maps_list);
}

//!sets up the menu on the window renderer based on the default maps list database that is loaded into the private vector
void SingletonDefaultMapsMenu::setupMenu()
{
	std::string buttonbase = "Create / Edit Campaign";
	int totalwidth = SingletonDefaultMapsMenu::_menuInstance->_menuWindow->getWindowWidth() * (0.30);

	//set menu background color, and font
	SingletonDefaultMapsMenu::_menuInstance->_menuWindow->setFontType(9);
	SingletonDefaultMapsMenu::_menuInstance->_menuWindow->setTitleFontSize(72);
	SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_MenuBackground_]->red;
	SingletonDefaultMapsMenu::_menuInstance->_menuWindow->setBackgroudColor(SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_MenuBackground_]->red,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_MenuBackground_]->green,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_MenuBackground_]->blue);

	//put title in center
	SDL_Rect menucomponent;

	//title should be centrally aligned
	menucomponent.w = SingletonDefaultMapsMenu::_menuInstance->_menuWindow->getWindowWidth() * (0.65);
	menucomponent.x = SingletonDefaultMapsMenu::_menuInstance->_menuWindow->getWindowWidth()/2 - menucomponent.w/2;
	menucomponent.y = 30;
	menucomponent.h = SingletonDefaultMapsMenu::_menuInstance->_menuWindow->getWindowHeight() * 0.05;
	SingletonDefaultMapsMenu::_menuInstance->_menuWindow->setTitle("DEFAULT MAPS LIST", SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_Title_]->red,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_Title_]->green,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_Title_]->blue, menucomponent);

	//go down 6 rectangle spaces
	menucomponent.y = menucomponent.y + menucomponent.h + (menucomponent.h*4);
	menucomponent.h = menucomponent.h * 0.8;

	//list all the maps
	for(int x=0; x<SingletonDefaultMapsMenu::_menuInstance->_mapListDataBase.size(); x++)
	{
		menucomponent.w = textWidthCalculator(SingletonDefaultMapsMenu::_menuInstance->_mapListDataBase[x], buttonbase, totalwidth);
		menucomponent.x = (SingletonDefaultMapsMenu::_menuInstance->_menuWindow->getWindowWidth()/2) - menucomponent.w/2;
		SingletonDefaultMapsMenu::_menuInstance->_menuWindow->addButton(SingletonDefaultMapsMenu::_menuInstance->_mapListDataBase[x], SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_NoButtonSelect_]->red,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_NoButtonSelect_]->green,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		//go down 1.5 rectangles
		menucomponent.y = menucomponent.y + menucomponent.h;
	}

	//now add a button for going back
	menucomponent.y = menucomponent.y + menucomponent.h;
	menucomponent.w = textWidthCalculator("Back to Campaign Editor", buttonbase, totalwidth);
	SingletonDefaultMapsMenu::_menuInstance->_menuWindow->addButton("Back to Campaign Editor", SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_NoButtonSelect_]->red,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_NoButtonSelect_]->green,SingletonDefaultMapsMenu::_menuInstance->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	//set the menus on renderer
	SingletonDefaultMapsMenu::_menuInstance->_menuWindow->setMenuOnRenderer();
}

//!this function is not of any use, was implemented only becuase I did not want the class to be abstract, 
//!but at the same time I had to inherit from campaign menus class for polymorphic usage in the menu engine
int SingletonDefaultMapsMenu::destinationMap(int index)
{
	return index;
}

//!this function is not of any use, was implemented only becuase I did not want the class to be abstract, 
//!but at the same time I had to inherit from campaign menus class for polymorphic usage in the menu engine
int SingletonDefaultMapsMenu::destinationMap(int index, char* componentname)
{
	return index;
}

//!returns name of a menu button from the private vector based on the index passed
std::string SingletonDefaultMapsMenu::getNameOfButtonFromIndex(int index)
{
	if(index== SingletonDefaultMapsMenu::_menuInstance->_mapListDataBase.size())
		return SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(_DefaultMapSelectionAbort_);
	return SingletonDefaultMapsMenu::_menuInstance->_mapListDataBase[index];
}

//!the lower and upper index are for usage in the menu engine for component deletion purposes, therefore
//!invoking this method for the dafult menu option will change the values to negative, implying none of the
//!default maps can be deleted from the default maps menu
void SingletonDefaultMapsMenu::checkExistingComponentsIndexRange(int* lowerindex, int* upperindex)
{
	*lowerindex = -10;
	*upperindex = -10;
}

//!returns the singletn instance, cretes new if already not created
SingletonDefaultMapsMenu* SingletonDefaultMapsMenu::getInstance()
{
	if(SingletonDefaultMapsMenu::_menuInstance == nullptr)
		SingletonDefaultMapsMenu::_menuInstance = new SingletonDefaultMapsMenu("Default Maps");
	return SingletonDefaultMapsMenu::_menuInstance;
}

//!destroys the singleton instance.
SingletonDefaultMapsMenu::~SingletonDefaultMapsMenu()
{
	if(SingletonDefaultMapsMenu::_menuInstance != nullptr)
		delete SingletonDefaultMapsMenu::_menuInstance;
	SingletonDefaultMapsMenu::_menuInstance = nullptr;
}