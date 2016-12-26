#include "ItemMenus.h"
#include <sstream>

//!parameterized constructor sets up the menu window
ItemMenus::ItemMenus(std::string title) : Menus(title)
{
}

//!sets up menu componenets on window renderer
void ItemMenus::setupMenu()
{
	SDL_Rect menucomponent;
	//set menu rectangle for title
	menucomponent.x = 30;
	menucomponent.y = 30;

	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.02);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.23);

	std::cout << menucomponent.x << " " << menucomponent.y << std::endl;

	//set menu font type
	this->_menuWindow->setFontType(9);

	//set menu background color
	this->_baseMenuColors[_MenuBackground_]->red;
	this->_menuWindow->setBackgroudColor(this->_baseMenuColors[_MenuBackground_]->red, this->_baseMenuColors[_MenuBackground_]->green, this->_baseMenuColors[_MenuBackground_]->blue);

	// Add title
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.14);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.6);
	menucomponent.y = menucomponent.y + (menucomponent.h*0.1);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	this->_menuWindow->setFontType(10);
	this->_menuWindow->addTextLabel("Create Items", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	//setup buttons
	this->_menuWindow->setFontType(9);
	// create weapon
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.06);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.24);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4) - (menucomponent.w / 2);
	menucomponent.y = this->_menuWindow->getWindowHeight() / 4;
	this->_menuWindow->addButton("Create Weapon", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// create armour
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.23);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Create Armour", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	// create shield
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.24);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Create Shield", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// create helmet
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.24);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Create Helmet", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// create belt
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.18);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Create Belt", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// create ring
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.18);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Create Ring", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
	
	// create boots
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.18);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Create Boots", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// print items
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.23);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4)*3 - (menucomponent.w / 2);
	menucomponent.y = this->_menuWindow->getWindowHeight() / 4;
	this->_menuWindow->addButton("Print Items", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// randomly generate items
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.41);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4)*3 - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Randomly Generate Items", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	
	// save to file
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.32);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4)*3 - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Save Items to File", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// load from file
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.33);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4)*3 - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Load Items from File", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// back to menu
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.25);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 4)*3 - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.2);
	this->_menuWindow->addButton("Back to Menu", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);



	//setup menu renderer and display
	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

//!maps destination based on the index of what button was clicked
//0 = play campaign
//1 = create / edit player
//2 = campaign manager menu
int ItemMenus::destinationMap(int index)
{
	switch (index)
	{
	case 0:
		return _CreateWeapon_;

	case 1:
		return _CreateArmour_;

	case 2:
		return _CreateShield_;

	case 3:
		return _CreateHelmet_;
	
	case 4:
		return _CreateBelt_;

	case 5:
		return _CreateRing_;

	case 6:
		return _CreateBoots_;

	case 7:
		return _PrintItems_;

	case 8:
		return _RandomlyGenerateItems_;

	case 9:
		return _SaveItemsToFile_;

	case 10:
		return _LoadItemsFromFile_;
	}
	return _MainMenu_;
}

ItemMenus::~ItemMenus()
{
}

PrintItemsMenus::PrintItemsMenus(std::string title) : Menus(title)
{
	userContainer = new Container();
}

void PrintItemsMenus::setupMenu()
{
	SDL_Rect menucomponent;
	//set menu rectangle for title
	menucomponent.x = 30;
	menucomponent.y = 30;

	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.02);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.23);

	std::cout << menucomponent.x << " " << menucomponent.y << std::endl;

	//set menu font type
	this->_menuWindow->setFontType(10);

	//set menu background color
	this->_baseMenuColors[_MenuBackground_]->red;
	this->_menuWindow->setBackgroudColor(this->_baseMenuColors[_MenuBackground_]->red, this->_baseMenuColors[_MenuBackground_]->green, this->_baseMenuColors[_MenuBackground_]->blue);

	// Add title
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.14);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.6);
	menucomponent.y = menucomponent.y + (menucomponent.h*0.1);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	this->_menuWindow->setFontType(10);
	this->_menuWindow->addTextLabel("Current Items", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// container output
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.03);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.18);
	menucomponent.y = menucomponent.y + (menucomponent.h*5);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 12);
	
	//this->_menuWindow->addTextLabel(userContainer->contentsToString(), this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	int originalMenuComponentY = menucomponent.y;
	this->_menuWindow->setFontType(9);
	std::string containerContents = userContainer->contentsToString();
	std::istringstream iss(containerContents);
	std::string line;
	while (std::getline(iss, line))
	{
		if (line.size() == 0) {
			line = " ";
			if (menucomponent.y + (menucomponent.h * 6) > this->_menuWindow->getWindowHeight() - 30) {
				menucomponent.y = originalMenuComponentY - (menucomponent.h*1.2);
				menucomponent.x = menucomponent.x + (this->_menuWindow->getWindowWidth() / 2);
			}
		}
		//menucomponent.y = menucomponent.y + (menucomponent.h*1.2);
		/*
		if (menucomponent.y + (menucomponent.h*1.2) > this->_menuWindow->getWindowHeight() - 30) {
			menucomponent.y = originalMenuComponentY + (menucomponent.h*1.2);
			menucomponent.x = menucomponent.x + (this->_menuWindow->getWindowWidth() / 3);
		}
		else {
			menucomponent.y = menucomponent.y + (menucomponent.h*1.2);
		}*/
		menucomponent.y = menucomponent.y + (menucomponent.h*1.2);
		menucomponent.w = Menus::textWidthCalculator(line, "aaaaaaaaaaaaaaaaaaaaaaaa", this->_menuWindow->getWindowWidth() * (0.18));
		this->_menuWindow->addTextLabel(line, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	}
	

	//setup buttons
	this->_menuWindow->setFontType(9);
	// create weapon
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.04);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.10);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 8)*7 - (menucomponent.w / 2);
	menucomponent.y = (this->_menuWindow->getWindowHeight() / 16)*15;
	this->_menuWindow->addButton("Back", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);



	//setup menu renderer and display
	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

void PrintItemsMenus::setContainer(Container * userConatainer)
{
	userContainer = userConatainer;
}

int PrintItemsMenus::destinationMap(int index)
{
	switch (index)
	{
	case 0:
		return _CreateEditItems_;
	}
	return _CreateEditItems_;
}

PrintItemsMenus::~PrintItemsMenus()
{
}
