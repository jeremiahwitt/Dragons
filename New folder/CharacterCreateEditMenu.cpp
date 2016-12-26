/**
*@file CharacterCreateEditMenu.cpp
*@brief Implements methods required to generate the Character Creation and Editing menu
*/
#include "CharacterCreateEditMenu.h"

//!parameterized constructor sets up the menu window
CharacterCreateEditMenu::CharacterCreateEditMenu(std::string title) : Menus(title)
{
}


//!sets up menu componenets on window renderer
void CharacterCreateEditMenu::setupMenu()
{
	SDL_Rect menucomponent;
	//set menu rectangle for title
	menucomponent.x = 30;
	menucomponent.y = 30;

	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.02);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.23);

	// Set Title Font Type
	this->_menuWindow->setFontType(10);

	//set menu background color
	this->_baseMenuColors[_MenuBackground_]->red;
	this->_menuWindow->setBackgroudColor(this->_baseMenuColors[_MenuBackground_]->red, this->_baseMenuColors[_MenuBackground_]->green, this->_baseMenuColors[_MenuBackground_]->blue);


	//title should be centrally aligned
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.9);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("CHARACTER EDITING AND CREATION", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	
	// Setup Button Font Type
	this->_menuWindow->setFontType(9);

	// Create a new Character!
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.07);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.3);
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 4);
	this->_menuWindow->addButton("Create New Character", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Edit an existing Character !
	menucomponent.w = textWidthCalculator("Edit Existing Character", "Create New Character", this->_menuWindow->getWindowWidth() * (0.3));
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.5);
	this->_menuWindow->addButton("Edit Existing Character", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	// Delete a saved Character!
	menucomponent.w = textWidthCalculator("Delete Saved Character", "Create New Character", this->_menuWindow->getWindowWidth() * (0.3));
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.5);
	this->_menuWindow->addButton("Delete Saved Character", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	// Return to main menu !
	menucomponent.w = textWidthCalculator("Return to Main Menu", "Create New Character", this->_menuWindow->getWindowWidth() * (0.3));
	menucomponent.x = (this->_menuWindow->getWindowWidth() / 2) - (menucomponent.w / 2);
	menucomponent.y = menucomponent.y + (menucomponent.h * 1.5);
	this->_menuWindow->addButton("Return to Main Menu", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	//setup menu renderer and display
	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

int CharacterCreateEditMenu::destinationMap(int index)
{
	switch (index)
	{
	case 0:
		return _CreateNewCharacter_;

	case 1:
		return _EditCharacter_;

	case 2:
		return _DeleteCharacter_;

	case 3:
		return _MainMenu_;
	}
	return _MainMenu_;
}