/**
*@file CharacterManager.cpp
*@brief Provides implementation of methods for management of Characters
*/
#include "CharacterManager.h"
#include "ContainerGenerator.h"
#include "ItemCreator.h"

/**
* Allows the user to select a Character from a list of saved Characters, returns the pointer
* so that the Character can be used.
*@return Fighter pointer, pointing to a loaded Fighter
*/
Fighter* CharacterManager::getCharacter(){
	Fighter* loadedFighter = CharacterSaveManager::loadCharacter();
	if (loadedFighter == NULL)
		cout << "There were issues selecting character." << endl;
	return loadedFighter;
}

/**
* Provides a menu to allow the user to either create a new Character, edit a Character, or delete a Character
*/
void CharacterManager::createOrEditCharacter(){
	char conf = 'X'; // char that will be used to get user input
	bool cont = true;

	// Ask if user wants to CREATE, EDIT or REMOVE a character
	cin.clear();
	do{
		system("CLS");
		_displayCreateEditMenu();
		cin >> conf;
		switch (conf){
		case '1': // User wants to create a new character
			createNewCharacter();
			break;
		case '2': // User wants to edit a saved character
			_editCharacter();
			break;
		case '3': // User wants to delete a character
			_deleteCharacter();
			break;
		case 'm':
		case 'M':
			return;
		default:
			std::cout << "Sorry, I think you entered an option that isn't allowed. Please try again." << endl;
		}
	} while (cont);
	return;
}

/**
* Will be used to create a new Character and save it to file.
*/
void CharacterManager::createNewCharacter(){
	string name = "";	// Will be used to get Character's name
	string input = "";	// Will store input
	int selectedRace = 0; // Will be used to get Character's race
	int selectedLevel = 0;	// Will be used to get Character's level
	char conf = 'X';	// Used to confirm choices
	system("CLS");
	cout << "*****************************" << endl;
	cout << "***** CHARACTER CREATER *****" << endl;
	cout << "*****************************" << endl << endl;

	// Get name of Character
	do {
		cout << "Please enter the name you would like to have for your character: ";
		cin >> name;
		cout << "You entered " << name << ". Are you happy with this? (Y/N) ";
		cin >> conf;
	} while (!(conf == 'Y' || conf == 'y'));
	conf = 'X';

	// Now the program will get the Character's Race
	do {
		cout << "Please select the race that you want for your character: " << endl;
		cout << "[0 = Dwarf][1 = Elf][2 = Halfling][3 = Human]" << endl;

		// Will get the integer representing the race the user wants, and will ensure that it is correct
		cin >> input;
		try {
			selectedRace = stoi(input);
		}
		catch (invalid_argument) {
			cout << "You entered an invalid argument. Please try again." << endl;
			continue;
		}

		// Will confirm the race for the user
		switch (selectedRace) {
		case 0:
		case 1:
		case 2:
		case 3:
			cout << "You selected " << raceString[selectedRace] << ". Are you happy with this? (Y/N) ";
			break;
		default:
			cout << "You selected an invalid option. Please try again." << endl;
			continue;
		}
		cin >> conf;
	} while (!(conf == 'Y' || conf == 'y'));
	conf = 'x';

	// Will get the starting level of the Character, confirming that a proper value is provided
	do {
		cout << "Please enter which level you would like your character to start at (1 - 20) : ";
		cin >> input;
		try {
			selectedLevel = stoi(input);
		}
		catch (invalid_argument) {
			cout << "You entered an invalid argument. Please try again." << endl;
			continue;
		}
		if (selectedLevel < 0 || selectedLevel > 20) {
			cout << "You entered an invalid level! Please try again." << endl;
			continue;
		}
		else {
			cout << "You entered " << selectedLevel << " as your starting level. Are you happy with this? (Y/N) : ";
			cin >> conf;
		}
	} while (!(conf == 'Y' || conf == 'y'));
	conf = 'x';

	// The Character will now be created
	// The user will be asked if they want to put the user-created items into their Character's backpack
	Fighter *myChar = CharacterBuilder::create(selectedLevel, Race(selectedRace), name);
	do {
		std::cout << endl << "Would you like to add user-created items to your character? (Y/N)" << endl;
		cin >> conf;
	} while (!(conf == 'Y' || conf == 'y' || conf == 'N' || conf == 'n'));

	if (conf == 'Y' || conf == 'y')
		//myChar->fillBackpack(ItemCreator::loadItemsFromFile());
		ItemCreator::loadItemsFromFile(myChar->backpack);

	// The Character will now be saved to file.
	CharacterSaveManager::saveCharacter(myChar, *(new SDL_Event()));
	myChar->displayOnlyStats();
	delete myChar;
	myChar = NULL;
	cout << endl << "Press any key to return to character management menu." << endl;
	system("PAUSE");
	return;
}

/**
* Allows the user to edit a Character of their choice, which has been saved to disk.
*/
void CharacterManager::_editCharacter(){
	system("CLS");
	cout << "****************************" << endl;
	cout << "****** EDIT CHARACTER ******" << endl;
	cout << "****************************" << endl << endl;
	Fighter *theChar = CharacterSaveManager::loadCharacter();
	system("PAUSE");
	// If no character was loaded, then the method will just return without doing anything
	if (theChar == NULL){
		return;
	}
	char conf = 'X'; // char that will be used to get user input
	bool cont = true;
	
	do{
		system("CLS");
		theChar->displayOnlyStats();
		// Displays menu to user so they can select what they want to do
		_displayEditMenu();
		// Ask if user wants to CREATE or EDIT the character
		cin >> conf;
		switch (conf){
		case '1': // User wants to edit Character name
			editName(theChar, *(new SDL_Event()));
			break;
		case '2': // User wants to edit a Character race
			_editRace(theChar);
			break;
		case 'e':
		case 'E':
			delete theChar;
			return;
		default:
			cout << "Sorry, I think you entered an option that isn't allowed. Please try again." << endl;
			system("PAUSE");
		}
	} while (cont);
	delete theChar;
	return;
	
}

/**
* Allows the user to edit the race of a Fighter
*@param theFighter Fighter* to the fighter that will be edited
*/
void CharacterManager::_editRace(Fighter* theFighter){
	// Will display the Fighter's current race
	string name = theFighter->getName();
	cout << name << " is currently a " << raceString[theFighter->getRace()] << "." << endl;
	char conf = 'X';
	string input = "";
	int selectedRace = -1;

	// Now the program will get the race the user wants to change it to
	do {
		cout << "Please select the Class that you want for " << name << ":" << endl;
		cout << "[0 = Dwarf][1 = Elf][2 = Halfling][3 = Human]" << endl;

		// Will get the integer representing the race the user wants, and will ensure that it is correct
		cin >> input;
		try {
			selectedRace = stoi(input);
		}
		catch (invalid_argument) {
			cout << "You entered an invalid argument. Please try again." << endl;
			continue;
		}

		// Will confirm the race for the user
		switch (selectedRace) {
		case 0:
		case 1:
		case 2:
		case 3:
			cout << "You selected " << raceString[selectedRace] << ". Are you happy with this? (Y/N) ";
			break;
		default:
			cout << "You selected an invalid option. Please try again." << endl;
			continue;
		}
		cin >> conf;
	} while (!(conf == 'Y' || conf == 'y'));
	conf = 'x';
	theFighter->setRace(Race(selectedRace));
	cout << "Changes will now be saved." << endl;
	CharacterSaveManager::saveCharacter(theFighter, *(new SDL_Event()));
	system("PAUSE");
	return;
}

/**
* Allows the user to delete a saved Character
*/
void CharacterManager::_deleteCharacter(){
	CharacterSaveManager::removeCharacter();
	system("PAUSE");
}

/**
* Prints the Create / Edit menu to screen
*/
void CharacterManager::_displayCreateEditMenu(){
	cout << "Please enter what you would like to do: " << endl;
	cout << "     [1] - Create a new character" << endl;
	cout << "     [2] - Edit an existing character" << endl;
	cout << "     [3] - Delete a saved character" << endl;
	cout << "Enter 'M' to return to main menu." << endl;
	cout << "Enter your option here: ";
}

/**
* Prints the Edit Menu to screen
*/
void CharacterManager::_displayEditMenu(){
	cout << "Please enter what you would like to do: " << endl;
	cout << "     [1] - Edit name" << endl;
	cout << "     [2] - Edit race" << endl;
	cout << "Enter 'E' to return to main menu." << endl;
	cout << "Enter your option here: ";
}

/**
* Allows the user to edit the name of a Character
*@param theFighter Fighter* to the fighter which will be edited
*@return destination to go to in the menu
*/
int CharacterManager::editName(Fighter *theFighter, SDL_Event _event){
	// Displays to the user the current name of the Character
	system("CLS");
	string prevName = theFighter->getName();
	cout << prevName << " is the current name." << endl;
	string name = "";
	char conf = 'X';
	
	// Get name of Character
	do {
		cout << "Please enter the name you would like to have for your character: ";
		cin >> name;
		cout << "You entered " << name << ". Are you happy with this? (Y/N) ";
		cin >> conf;
		if (!(conf == 'Y' || conf == 'y' || conf == 'N' || conf == 'n'))
			cout << "Sorry, I didn't understand your confirmation. Please try again." << endl;
	} while (!(conf == 'Y' || conf == 'y'));
	conf = 'X';

	// Changes the name
	theFighter->setName(name);

	// Saves the Fighter using new name
	if (CharacterSaveManager::saveCharacter(theFighter, _event)) {
		cout << theFighter->getName() << " has been updated!" << endl;
	// Deletes the entry corresponding to the old name
		CharacterSaveManager::removeCharacter(prevName);
		return _SuccessNameChange_;
	} else { // Means that saving returned false and no updates were saved
		cout << "Could not update " << theFighter->getName() << " properly. Reverting to " << prevName<< "." << endl;
		theFighter->setName(prevName);
		return _CreateEditPlayer_;
	}
}



