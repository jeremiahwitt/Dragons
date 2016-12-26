/**
*@file LoadCharacterMenu.h
*@brief Implements a Menu which will be able to load a Character from file and return that Character
*/

#ifndef LOADCHARACTERMENU_H
#define LOADCHARACTERMENU_H
#include "menus.h"
#include "CharSaveManager.h"
#include "Fighter.h"
using namespace BaseMenuColorIndex;
using namespace DestinationFromMenus;

class LoadCharacterMenu : public Menus{
private:
	std::vector<std::string>* _characterNames; //! Will store the names of all Characters that are saved
public:
	LoadCharacterMenu(std::string title);
	void setupMenu();
	int destinationMap(int index);
	std::string getNameOfCharacterFromIndex(int index);
};
#endif