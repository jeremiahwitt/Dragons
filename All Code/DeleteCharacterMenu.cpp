/**
*@file DeleteCharacterMenu.cpp
*@brief Provides definition of methods that give the user the ability to delete Characters
* via a GUI
*/
#include "DeleteCharacterMenu.h"

/**
* Parameterized Constructor. Sets the title of the menu using the superclass, and retrieves the names
* of all available Characters from file
*/
DeleteCharacterMenu::DeleteCharacterMenu(std::string title) : Menus(title){
	vector<string>* names = CharacterSaveManager::getNames();
	if (names == nullptr)
		_characterNames = new vector<string>();
	else _characterNames = names;
}

void DeleteCharacterMenu::setupMenu(){

	string buttonbase = "Create New Character";
	int totalwidth = this->_menuWindow->getWindowWidth() * (0.3);

	// Set the menu background color and font
	this->_menuWindow->setFontType(10);
	this->_menuWindow->setTitleFontSize(72);
	this->_baseMenuColors[_MenuBackground_]->red;
	this->_menuWindow->setBackgroudColor(this->_baseMenuColors[_MenuBackground_]->red, this->_baseMenuColors[_MenuBackground_]->green, this->_baseMenuColors[_MenuBackground_]->blue);
	SDL_Rect menucomponent;

	//set menu rectangle for title
	menucomponent.x = 30;
	menucomponent.y = 30;

	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.02);
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.23);

	//title should be centrally aligned
	menucomponent.w = this->_menuWindow->getWindowWidth() * (0.9);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("DELETE CHARACTER", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	
	// Setup Text, first set Font
	this->_menuWindow->setFontType(9);
	
	//setup buttons
	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.05);
	menucomponent.w = textWidthCalculator("Select the character you want to remove: ", buttonbase, totalwidth);
	this->_menuWindow->addTextLabel("Select the character you want to remove: ", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
	menucomponent.y = menucomponent.y + (menucomponent.h*(1.5));

	// If no names, alert the user
	menucomponent.x += menucomponent.x; 
	if (_characterNames->size() == 0){
		menucomponent.w = textWidthCalculator("There are no characters to delete!", buttonbase, totalwidth);
		this->_menuWindow->addTextLabel("There are no characters to delete!", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
		menucomponent.y = menucomponent.y + menucomponent.h;
	} else

	// Display all Character names, offset x to indent
	for (int i = 0; i < _characterNames->size(); i++){
		menucomponent.w = textWidthCalculator(_characterNames->at(i), buttonbase, totalwidth);
		this->_menuWindow->addButton(_characterNames->at(i), this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);
		menucomponent.y = menucomponent.y + menucomponent.h;
	}

	// Remove offset
	menucomponent.x -= (0.5) * menucomponent.x;
	menucomponent.y = menucomponent.y + (menucomponent.h);
	menucomponent.w = textWidthCalculator("Back to Character Management Menu", buttonbase, totalwidth);
	this->_menuWindow->addButton("Back to Character Management Menu", this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

//! Returns the int representing the destination of the Menu
int DeleteCharacterMenu::destinationMap(int index){
	// If index is one of the names, then return 1
	if (index < this->_characterNames->size())
		return 1;
	// Else, if index is max of names, then return Character Management index
	else if (index == this->_characterNames->size())
		return _CreateEditPlayer_;
	else return _CreateEditPlayer_;
}

//! Returns the Name of the Character the user wants to delete
string DeleteCharacterMenu::getNameOfCharacterFromIndex(int index){
	if (index < this->_characterNames->size())
		return this->_characterNames->at(index);
	return "";
}