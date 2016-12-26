/**
*@file DisplayPlayerStatsWindow.cpp
*@brief Provides the methods required to generate a Menu which displays all the stats of a player
*/
#include "DisplayPlayerStatsWindow.h"

/**
* Parameterized Constructor. Sets the title of the menu using the superclass, and sets the pointer to the Fighter which will be editted.
*/
DisplayPlayerStatsWindow::DisplayPlayerStatsWindow(std::string title, Fighter* theFighter) : Menus(title), _theFighter(theFighter){}

/**
* Will initialize the edit menu
*/
void DisplayPlayerStatsWindow::setupMenu(){

	string buttonbase = "Create New Charact";
	int totalwidth = this->_menuWindow->getWindowWidth() * (0.2);
	int tinyGap = 3;
	int bigGap = 20;
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
	menucomponent.w = textWidthCalculator("PLAYER INFO", buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() / 2 - menucomponent.w / 2;
	menucomponent.y = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * 0.1;
	this->_menuWindow->setTitle("PLAYER INFO", this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Setup Text, first set Font
	this->_menuWindow->setFontType(9);

	// Name Label
	menucomponent.y = menucomponent.y + 30 + menucomponent.h;
	string nextDisplay = "Name:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.03);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);
	
	// Name Text
	nextDisplay = _theFighter->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Class Label
	nextDisplay = "Class:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Class Text
	nextDisplay = "Fighter";
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Race Label
	nextDisplay = "Race:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.66) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Race Text
	Race charRace = _theFighter->getRace();
	switch(charRace){
	case Dwarf:
		nextDisplay = "Dwarf";
			break;
	case Elf:
		nextDisplay = "Elf";
		break;
	case Halfling:
		nextDisplay = "Halfling";
			break;
	case Human:
		nextDisplay = "Human";
		break;
	}
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Level Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "Level:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Level Text
	nextDisplay = to_string(_theFighter->getLevel());
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// HP Label
	nextDisplay = "Hit Points:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// HP Text
	nextDisplay = to_string(_theFighter->getHP()) + "/" + to_string(_theFighter->getMaxHP());
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	if ((double)_theFighter->getHP() / _theFighter->getMaxHP() < 0.5)
		this->_menuWindow->addTextLabel(nextDisplay, 255, 0, 0, menucomponent);
	else this->_menuWindow->addTextLabel(nextDisplay, 0, 255, 0, menucomponent);

	// EXP Label
	nextDisplay = "EXP:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.66) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// EXP Text
	nextDisplay = to_string(_theFighter->getExp());
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Ability Scores Title
	menucomponent.y = menucomponent.y + bigGap + menucomponent.h;
	nextDisplay = "ABILITY SCORES";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.04);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Strength Scores Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "STR:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.03);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);
	
	// Strength Scores Text
	nextDisplay = to_string(_theFighter->getScores(0, 0)) + "(" + to_string(_theFighter->getScores(1, 0)) + ")";
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Dexterity Scores Label
	nextDisplay = "DEX:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Dexterity Scores Text
	nextDisplay = to_string(_theFighter->getScores(0, 1)) + "(" + to_string(_theFighter->getScores(1, 1)) + ")";
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Constitution Scores Label
	nextDisplay = "CON:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.66) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Constitution Scores Text
	nextDisplay = to_string(_theFighter->getScores(0, 2)) + "(" + to_string(_theFighter->getScores(1, 2)) + ")";
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Intelligence Scores Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "INT:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Intelligence Scores Text
	nextDisplay = to_string(_theFighter->getScores(0, 3)) + "(" + to_string(_theFighter->getScores(1, 3)) + ")";
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Wisdom Scores Label
	nextDisplay = "WIS:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Wisdom Scores Text
	nextDisplay = to_string(_theFighter->getScores(0, 4)) + "(" + to_string(_theFighter->getScores(1, 4)) + ")";
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Charisma Scores Label
	nextDisplay = "CHA:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.66) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Charisma Scores Text
	nextDisplay = to_string(_theFighter->getScores(0, 5)) + "(" + to_string(_theFighter->getScores(1, 5)) + ")";
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Proficiency Bonus Title
	menucomponent.y = menucomponent.y + bigGap + menucomponent.h;
	nextDisplay = "Proficiency Bonus:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);
	
	// Proficiency Bonus Text
	nextDisplay = to_string(_theFighter->getProficiencyBonus());
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Armor Class Label
	nextDisplay = "Armor Class:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Armor Class Scores Text
	nextDisplay = to_string(_theFighter->getArmorClass());
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Attack Bonus Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "Attack Bonus:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Attack Bonus Text
	nextDisplay = to_string(_theFighter->getAttackBonus());
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Damage Bonus Label
	nextDisplay = "Damage Bonus:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Damage Bonus Text
	nextDisplay = to_string(_theFighter->getDamageBonus());
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Equipment Title
	menucomponent.y = menucomponent.y + bigGap + menucomponent.h;
	nextDisplay = "EQUIPMENT";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.04);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Armor Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "Armor:";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.03);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Armor Text
	nextDisplay = _theFighter->getArmor()->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Weapon Label
	nextDisplay = "Weapon:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Weapon Text
	nextDisplay = _theFighter->getWeapon()->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Shield Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "Shield:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Shield Text
	nextDisplay = _theFighter->getShield()->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Helmet Label
	nextDisplay = "Helmet:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Helmet Text
	nextDisplay = _theFighter->getHelmet()->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Ring Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "Ring:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Ring Text
	nextDisplay = _theFighter->getRing()->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Boots Label
	nextDisplay = "Boots:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * (0.33) + 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Boots Text
	nextDisplay = _theFighter->getBoots()->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Belt Label
	menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
	nextDisplay = "Belt:";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Attack Bonus Text
	nextDisplay = _theFighter->getBelt()->getName();
	menucomponent.x = menucomponent.x + 10 + menucomponent.w;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);

	// Backpack Title
	menucomponent.y = menucomponent.y + bigGap + menucomponent.h;
	nextDisplay = "BACKPACK";
	menucomponent.h = this->_menuWindow->getWindowHeight() * (0.04);
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = 30;
	this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Label_]->red, this->_baseMenuColors[_Label_]->green, this->_baseMenuColors[_Label_]->blue, menucomponent);

	// Set values needed to print out the backpack
	int xMod = 0.33;
	int itemsDisplayed = 0;
	Container* theBackPack = _theFighter->getBackPack();
	// Outer loop will control each line
	for (int i = 0; i < ceil(((double)theBackPack->getNumContents() / 3)); i++){
		// Ensure that x and y offset are initialized to left-size values
		menucomponent.y = menucomponent.y + tinyGap + menucomponent.h;
		menucomponent.x = 30;
		for (int j = 0; j < 3; j++){
			// Check if we have displayed all items. If we have, exit the loops!
			if (itemsDisplayed == theBackPack->getNumContents())
				goto DONE_DISPLAY;

			// Else, we must display the next item
			nextDisplay = theBackPack->getContents()[itemsDisplayed++]->getName();
			menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
			this->_menuWindow->addTextLabel(nextDisplay, this->_baseMenuColors[_Title_]->red, this->_baseMenuColors[_Title_]->green, this->_baseMenuColors[_Title_]->blue, menucomponent);
			menucomponent.x += (this->_menuWindow->getWindowWidth() * ((0.33)));
		}
	}
	DONE_DISPLAY:
		
	// Reset x component, set new x component at bottom
	// MANAGE EQUIPMENT

	menucomponent.y = this->_menuWindow->getWindowHeight() - menucomponent.h;
	// Return to Character Management Menu
	nextDisplay = "Manage Equipment";
	//menucomponent.y = menucomponent.y + (menucomponent.h);
	menucomponent.x = _menuWindow->getWindowWidth() * 0.25;
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);


	// Reset x component, set it to opp end of screen
	nextDisplay = "Go Back";
	menucomponent.w = textWidthCalculator(nextDisplay, buttonbase, totalwidth);
	menucomponent.x = this->_menuWindow->getWindowWidth() * 0.60;
	this->_menuWindow->addButton(nextDisplay, this->_baseMenuColors[_NoButtonSelect_]->red, this->_baseMenuColors[_NoButtonSelect_]->green, this->_baseMenuColors[_NoButtonSelect_]->blue, menucomponent);

	this->_menuWindow->setMenuOnRenderer();
	this->_menuWindow->displayWindow();
}

//! Returns the int representing the destination of the Menu
int DisplayPlayerStatsWindow::destinationMap(int index){
	switch (index){
	case 0:
		return _ManageEquipment_;
	case 1:
		return _GoBack_;
	}
	return _GoBack_;
}