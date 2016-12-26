#include "game_loops.h"
#include "Fighter.h"


//!primary driver of the driver class game loops
//!managest the next destination based on the destination values returned in
//!the main while loop
void GameLoops::loopManager()
{
	SDLSetup setup = SDLSetup();
	setup.SDL_Initialize_All_Functionalities();

	//instantiate signleton object, create the menu and set it up once
	SingletonDefaultMapsMenu::getInstance()->setupMenu();
	SingletonDefaultMapsMenu::getInstance()->hideMenu();
	CharacterController::getInstance()->clearLog();
	// instantiate the user container for item cration
	Container * userContainer = new Container();

	//instantiate the sounds for menu
	ContinousEffect* background = new ContinousEffect("assets/Sound/Menu/Background/mainmenu.mp3");
	background->setVolume(40);

	background->play();

	_currentFighterTracker = nullptr;
	bool quit = false;
	int destination;

	char* mappath = new char[100];
	char* campaignname = new char[100];
	std::string temp;
	destination = _MainMenu_;
	while(quit == false)
	{
		switch(destination)
		{
		case _MainMenu_:
			destination = mainMenuLoop(mappath, campaignname);
			break;

		case _CreateEditItems_:
			destination = createEditItems();
			break;

		case _CreateEditPlayer_:
			destination = createEditPlayer();
			break;

		case _CreateNewCharacter_:
			destination = createNewPlayer();
			break;

		case _EditCharacter_:
			destination = editExistingPlayer();
			break;

		case _EditName_:
			destination = CharacterManager::editName(_currentFighterTracker, this->_event);
			break;

		case _EditRace_:
			destination = editPlayerRace(_currentFighterTracker);
			break;

		case _SuccessNameChange_:
			destination = displaySuccessfulNameChange(_currentFighterTracker);
			break;

		case _SuccessRaceChange_:
			destination = displaySuccessfulRaceChange(_currentFighterTracker);
			break;

		case _DeleteCharacter_:
			destination = deleteCharacter();
			break;

		case _DisplayPlayerStats_:
			destination = displayPlayerStats(_currentFighterTracker);
			break;

		case _PlayCampaign_:
			destination = playCampaignLoop(mappath, campaignname);
			break;

		case _NewMapCreation_:
			destination = createNewMap(mappath, campaignname);
			SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(campaignname, this->_currentCampaignTracker);
			break;

		case _EditExistingMap_:
			destination = editExistingMap(mappath, campaignname);
			SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(campaignname, this->_currentCampaignTracker);
			break;

		case _CampaignManagerMenu_:
			destination = campaignManagerLoop(mappath, campaignname);
			break;

		case _EditExistingCampaign_:
			destination = editExistingCampaignLoop(mappath, campaignname);
			break;
		case _GameLog_:
			destination = displayGameLog();
			break;
		// START ITEM CREATION MENU OPTIONS
		case _CreateWeapon_:
			destination = createEditItems(userContainer, _CreateWeapon_);
			break;
		case _CreateArmour_:
			destination = createEditItems(userContainer, _CreateArmour_);
			break;
		case _CreateShield_:
			destination = createEditItems(userContainer, _CreateShield_);
			break;
		case _CreateHelmet_:
			destination = createEditItems(userContainer, _CreateHelmet_);
			break;
		case _CreateBelt_:
			destination = createEditItems(userContainer, _CreateBelt_);
			break;
		case _CreateBoots_:
			destination = createEditItems(userContainer, _CreateBoots_);
			break;
		case _CreateRing_:
			destination = createEditItems(userContainer, _CreateRing_);
			break;
		case _PrintItems_:
			destination = printItems(userContainer);
			break;
		case _LoadItemsFromFile_:
			destination = createEditItems(userContainer, _LoadItemsFromFile_);
			break;
		case _SaveItemsToFile_:
			destination = createEditItems(userContainer, _SaveItemsToFile_);
			break;
		case _RandomlyGenerateItems_:
			destination = createEditItems(userContainer, _RandomlyGenerateItems_);
			break;

		// END ITEM CREATION MENU OPTIONS

		case _ExitToCommandPrompt_:
			quit = true;
		}
	}
	background->stopPlay();
	delete background;
	background = nullptr;
	//
	//
	

	delete mappath;
	delete campaignname;
	mappath = nullptr;
	campaignname = nullptr;
}

//!the loop that handles playing of a full campaign
int GameLoops::playCampaignLoop(char* path, char* campaign)
{
	//first load menu to select campaign
	CampaignSelect* c_menu = new CampaignSelect("menu");
	c_menu->setupMenu();
	c_menu->displayMenu();

	//attach menu to menuengine
	MenuEngine* engine = new MenuEngine(c_menu, this->_event);

	//get an index
	int destination;

	GET_CAMPAIGN_NAME:
	destination = engine->runEngine();

	//save the name of button in a temprary string
	std::string temp = c_menu->getNameOfCampaignFromIndex(destination);

	//now map destination, if a 1 means a valid campaign was selected
	if(c_menu->destinationMap(destination) == 1)
	{
		//first check that there is atleast 1 map
		if(SingletonInputOutputManager::getInstance()->loadONECampaign(temp).size() > 1)
		{
			GameController::getInstance()->log("Campaign "+temp+" was loaded for play.");
			//it is ok to play the campaign
			//load the campaign in a vector
			std::vector<std::string> campaigndatabase = SingletonInputOutputManager::getInstance()->loadONECampaign(temp);

			//now load the maps and mappaths
			std::vector<std::string> mapnames, mappaths;
			for(int x=1; x<campaigndatabase.size(); x+=2)
			{
				mapnames.push_back(campaigndatabase[x]);
				mappaths.push_back(campaigndatabase[x+1]);
			}

			// Now load the player
			this->_currentFighterTracker = loadPlayer();

			// Check if Fighter is nullptr - if it is, means we didn't load so we have to quit!
			if (_currentFighterTracker == nullptr){
				goto QUIT_LOAD;
			}
			c_menu->getMenuWindow()->hideWindow();
			/*this->_currentFighterTracker = CharacterManager::getCharacter();
			*/

			for (int x = 0; x < mappaths.size(); x++)
			{
				GameController::getInstance()->log("Map "+mapnames[x]+" of campaign "+temp+" was loaded for play.");
				if (gameLevelLoop(mappaths[x]) > 0)
				{
					GameController::getInstance()->log("Map " + mapnames[x] + " of campaign " + temp + " was exited before completion.");
					GameController::getInstance()->log("Campaign " + temp + " was aborted before completion.");
					break;
				}
				if (x == mappaths.size() - 1)
				{
					c_menu->getMenuWindow()->hideWindow();
					system("cls");
					std::cout << "CONGRATS!!!\nYou beat campaign " << temp<<std::endl;
					GameController::getInstance()->log("Map " + mapnames[x] + " of campaign " + temp + " was successfully completed.");
					GameController::getInstance()->log("Campaign "+temp+" was won.");
					system("pause");
					CharacterSaveManager::saveCharacter(_currentFighterTracker, this->_event);
					break;
				}
				GameController::getInstance()->log("Map " + mapnames[x] + " of campaign " + temp + " was successfully completed.");
			}
		}
		else
		{
			//cannot play campaign
			c_menu->getMenuWindow()->hideWindow();
			system("cls");
			std::cout<<"There is not a single map in campaign "<<temp<<", please first create a map for this campaign, or select a different campaign\n\n";
			GameController::getInstance()->log("Campaign " + temp + " failed to load due to insufficient maps.");
			std::cout<<"Press any key to continue\n";
			getch();
			c_menu->getMenuWindow()->unHideWindow();
			goto GET_CAMPAIGN_NAME;
		}
	}

	//if -1 it means non existent slot was selected, go back to start
	else if(c_menu->destinationMap(destination) == -1)
		goto GET_CAMPAIGN_NAME;

	//last option is return to main menu so delete and return
	QUIT_LOAD:
	c_menu->hideMenu();
	delete c_menu;
	c_menu = nullptr;
	return _MainMenu_;
}

//!this is the loop that runs when a user created map is loaded
//!this funtion also will be responsible for the main gameplay loop
//!PLEASE NOTE, I have left everything commented out in the submission for
//!this assignment becuase that code fragment works, an I will use that as 
//!template in assignment 3, interim and final project
int GameLoops::gameLevelLoop(std::string mappath)
{
	int destinationInt;
	bool quit = false;

	//Fighter* f = new Fighter();
	
	PreBuiltLevel* l = new PreBuiltLevel("Test", this->_currentFighterTracker);
	GamePlayEngine* engine = new GamePlayEngine();
	l->loadUserCreatedLevel(mappath);
	l->createLevelForTargetWindow();
	l->setupEnemiesOnMap();
	//l->createLevelForTargetWindow();
	l->setupContainersOnMap();
	l->renderAndDisplayLevel();
	

	engine->attachLevel(l, &this->_event);
	vector<string> simpleMap = l->getMapSimpleVersion();
	//this->_currentFighterTracker->setMap(&simpleMap);
	for (int i = 0; i < simpleMap.size(); i++){
		for (int j = 0; j < simpleMap.at(i).size(); j++){
			if (simpleMap.at(i).at(j) == SimplifiedMapSymbols::_Player_){
				this->_currentFighterTracker->setPosition(i, j);
				goto AFTER_SET_POSITION;
			}
		}
	}
	AFTER_SET_POSITION:
	// We setup the FighterView so that the Fighter will be re-rendered whenever it is moved
	FighterOnMapView *fighterView = new FighterOnMapView(this->_currentFighterTracker, l);
	
	// Now run the engine
	destinationInt = engine->runEngine();
	
	l->getLevelWindow()->hideWindow();
	engine->detachLevel();
	delete engine;
	engine = nullptr;
	delete fighterView;
	fighterView = nullptr;

	delete l;
	l=nullptr;
	return destinationInt;
}

//!used to create a new map
int GameLoops::createNewMap(char* path, char* campaign)
{
	//take a valid user input first
	system("cls");
	int input;
	bool valid = false;
	std::cout<<"DUNGEONS AND DRAGONS MAP CREATION ENGINE"<<std::endl<<std::endl;
	std::cout<<"Please input the number of rows and columns you wish in your map."<<std::endl<<std::endl;
	std::cout<<"Minimum: 5 X 5"<<std::endl;
	std::cout<<"Maximum: 50 X 50"<<std::endl;
	std::cout<<"Optimal 25 X 15"<<std::endl<<std::endl;

	int totalhorizontalGameGrids = SingletonInputsAndStringManager::getInstance()->takeIntInput("Please input the number of rows minimum 5 and maximum 50: ", 5,50);
	int totalVerticalGameGrids = SingletonInputsAndStringManager::getInstance()->takeIntInput("Please input the number of columns minimum 5 and maximum 50: ", 5,50);

	system("cls");

	std::string title = "test";
	LevelWindow* window = new LevelWindow(title.c_str(), totalhorizontalGameGrids, totalVerticalGameGrids);
	int destinationInt =-1;
	window->displayWindow();

	//create leveleditor object
	LevelEditor* level = new LevelEditor(window,1);
	level->createLevelForTargetWindow();
	level->renderAllNonGameplayGridPortions();
	level->getLevelWindow()->displayWindow();

	SDL_SetRenderDrawBlendMode(window->getRenderer(), SDL_BLENDMODE_BLEND);
	std::vector<Environment*> envcomponents = level->getEnvironmentComponents();

	int succuess = levelEditorLoop(level, path, campaign);
	
	//if success is negative then it means user did not complete creating the map
	//create an object with same file name and delete the last values loaded
	if(succuess < 0)
	{
		CampaignMapManagers* manager = new CampaignMapManagers("assignment2", this->_currentCampaignTracker);
		std::cout<<this->_currentCampaignTracker<<std::endl;
		manager->sucessfullMapCreated(false);
		manager->hideMenu();
		delete manager;
	}
	else
	{
		GameController::getInstance()->log("New map was created.");
	}

	return _EditExistingCampaign_;
}

//!edits an existing map
int GameLoops::editExistingMap(char* path, char* campaign)
{
	
	//get a valid map name from the maps already in file
	PreBuiltLevel* l = new PreBuiltLevel();
	l->loadUserCreatedLevel(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(path));
	l->createLevelForTargetWindow();

	LevelWindow* temp = new LevelWindow(l->getLevelWindow()->getWindowTitle(), l->getLevelWindow()->getGamePlay_X_Grids(), l->getLevelWindow()->getGamePlay_Y_Grids());
	LevelEditor* level = new LevelEditor(temp, -1);
	level->takeComponentsFromPreBuiltLevel(l);
	level->createLevelForTargetWindow();
	level->renderAllNonGameplayGridPortions();
	level->getLevelWindow()->displayWindow();
	l->getLevelWindow()->hideWindow();
	l->destroyLevel();

	SDL_SetRenderDrawBlendMode(temp->getRenderer(), SDL_BLENDMODE_BLEND);

	//delete the temporary pre built level
	delete l;
	l = nullptr;
	
	//DO NOT delete the level editor here, the level editor map is taking care of it
	levelEditorLoop(level, path, campaign);
	GameController::getInstance()->log("An existing map was edited and saved.");
	return _EditExistingCampaign_;
}

//!lets user create a map
int GameLoops::levelEditorLoop(LevelEditor* level, char* path, char* campaign)
{
	GameController::getInstance()->log("Map Editor loaded.");
	level->renderAndDisplayLevel();
	int destinationInt = -1;
	LevelWindow* const window = level->getLevelWindow();
	MapEditorEngine* m = new MapEditorEngine(level);
	bool mapvalid = false;
	
	while(m->getQuit()==false)
	{
		while(SDL_PollEvent(&_event) != 0)
		{
			SDL_GetMouseState(&this->mouse_X_cor, &this->mouse_Y_cor);

			//this is to ensure if left mouse button was clicked in gameplay grid and released elsewhere,
			//then when the mouse is taken back to gameplay grid nothing renders
			if(m->getRenderingOnGameplayGrids() == true && (_event.type==SDL_MOUSEBUTTONUP))
				m->setRenderingOnGameplayGrids(false);
			
			//quit if user presses red on top right
			if(_event.type == SDL_QUIT)
			{
				m->setQuit(true);
				destinationInt = -1;
			}

			//for right button click target selected is false all parameters get reset
			if((_event.type == SDL_MOUSEBUTTONUP)&&(_event.button.button == SDL_BUTTON_RIGHT) && (m->getTargetSelected() == true))
			{
				m->setTargetSelected(false);
				m->setTargetIsPlayer(false);
				m->targetisfriend = false;
				m->setTargetIsExit(false);
				m->setTargetisContainer(false);
				m->setTargetisEnemy(false);
				m->setTargetTexture(nullptr);
				m->setOnTargetFirstTime(false);
				level->renderAllNonGameplayGridPortions();
				window->displayWindow();
			}

			//for gameplaygrid alphablend on select grids NOTE the -1 as are to give a 1pixel line buffer between the gameplay grid rectangle and rest of the window
			if((mouse_Y_cor<=(((window->getGamePlay_Y_Grids())*window->getGridY_Length()-1))) && (mouse_X_cor<=(((window->getGamePlay_X_Grids())*window->getGridX_Length())-1)))
			{
				m->onGameplayGrids(&_event); 
			}

			//check if mouse is in bottom grid section only if a target is not selected
			else if((mouse_Y_cor>(window->getGamePlay_Y_Grids())*window->getGridY_Length()) && (m->getTargetSelected() == false))
			{
				//check if mouse is on environment grid
				if(mouse_X_cor < level->getEnvironmentPortionEnd_X_Xor())
					m->onEnvironmentGrid(&_event);

				//check if mouse is on container grid
				if(mouse_X_cor < level->getItemPortionEnd_X_Cor())
					m->onContainerGrid(&_event);

				//check if mouse is on character grid
				else if(mouse_X_cor < level->getCharacterPortionEnd_X_Cor())
				{
					level->renderEnvironmentAtBottom();
					m->onCharacterGrid(&_event);
				}
			}

			//check is mouse is on right hand menu
			else if(mouse_X_cor > (window->getGamePlay_X_Grids() * window->getGridX_Length()) && (m->getTargetSelected() == false))
			{
				destinationInt = m->onRightHandMenuGrid(&_event);

				switch(destinationInt)
				{
				//main menu
				case 0:
					destinationInt = -1;
					m->setQuit(true);
					break;

				//instructions
				case 1:
					level->getLevelWindow()->hideWindow();
					system("cls");
					std::cout<<"MAP CREATION INSTRUCTIONS"<<std::endl<<std::endl;
					std::cout<<"1. Left click on components at bottom of window to select, left click on gameplay grid canvas to set the grids with selected component."<<std::endl;
					std::cout<<"2. Right click to deselect a selected component, and repeat the process."<<std::endl;
					std::cout<<"3. When no component is selected, hover on top of grid that is already filled and right click to delete."<<std::endl;
					std::cout<<"4. One and only one player can be put on the map."<<std::endl;
					std::cout<<"5. One and only one exit door can be put on the map."<<std::endl;
					std::cout<<"6. All grids have to be filled for the map to be valid."<<std::endl;
					std::cout<<"7. There has to be a completely unobstructed from from player to exit door for map to be valid."<<std::endl;
					std::cout<<"8. Click on 'Accept Map' on right hand side menu to save map, invalid map will have no affect on button click."<<std::endl;
					std::cout<<"9. When a component is selected, the bottom rightmost rectangle gives the component name and weather it is obstruction or not."<<std::endl;
					std::cout<<"10. Once a valid map is accepted you will be in main menu where you can click on 'Load Map' to load the last valid accepted map."<<std::endl;
					std::cout<<"11. Click on main menu or the cross button at any point to quit, the incomplete map will NOT be saved."<<std::endl<<std::endl;
					std::cout<<"Press any key to continue map creation."<<std::endl;
					_getch();
					system("cls");
					level->getLevelWindow()->unHideWindow();
					break;
				
				//validate map
				case 2:
					if (m->validateMap() == true)
					{
						destinationInt = 1;
						mapvalid = true;
						std::cout << "map valideted to true.\n";
						m->setQuit(true);
						break;
					}
					else
					{
						level->getLevelWindow()->hideWindow();
						system("cls");
						std::cout<<"This map is invalid, it could be for one of the following reasons.\n\n";
						std::cout<<"1. Not all the cells have a component, please not for our project, a cell with a component named 'floor' is like an empty cell where a player can traverse freely\n";
						std::cout<<"2. There is not one and one only player\n";
						std::cout<<"3. There is not one and one only exit door\n";
						std::cout<<"4. There is no direct unobstructed route from the player to the exit door. Please not enemies, items and containers do count as obstruction during map creation\n\n";
						std::cout<<"Press any key to continue editing map.";
						getch();
						level->getLevelWindow()->unHideWindow();
					}
				}
			}
		}
	}

	//if main menu was quit without a valid level then, the level will not be saved
	//if(destinationInt != -1)
	if (mapvalid==true)
	{
		std::cout << "Trying to save level\n";
		std::vector<std::string> templevel = m->getEnvironmentTextLevel();
		std::cout<<std::endl<<std::endl;

		//save the level on text file
		level->setEnvironmentTextVector(templevel);
		level->saveLevel(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(path));
		
		std::cout << "Saved Level";
		//system("pause");

		delete level;
		level = nullptr;
	
		delete m;
		m= nullptr;
		return _EditExistingCampaign_;
	}

	delete level;
	level = nullptr;
	
	delete m;
	return -1;
}

//! Displays the menu that allows access to game log
int GameLoops::displayGameLog(){
	GameController::getInstance()->log("Accessing game logs.");
	GameLogMenu* menu = new GameLogMenu("GAME LOG");
	menu->setupMenu();
	menu->displayMenu();

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, *(new SDL_Event()));
	int buttonNum = engine->runEngine();
	int destination = menu->destinationMap(buttonNum);
	if (destination == _ViewLog_)
	{
		menu->getMenuWindow()->hideWindow();
		LogViewMenu* menu2 = new LogViewMenu("GAME LOG VIEW");
		menu2->setupMenu();
		menu2->displayMenu();

		MenuEngine* engine2 = new MenuEngine(menu2, *(new SDL_Event()));
		int buttonNum = engine2->runEngine();
		int destination = menu2->destinationMap(buttonNum);
		menu2->getMenuWindow()->hideWindow();
		GameLogTest::displayLogChanges(destination);
		delete menu2;
		menu2 = nullptr;
		delete engine2;
		engine2 = nullptr;
	}
	else if (destination == _ToggleLog_)
	{
		menu->getMenuWindow()->hideWindow();
		ToggleLogMenu* menu3;
		MenuEngine* engine3;
		bool exit = false;
		do{
			menu3 = new ToggleLogMenu("GAME LOG TOGGLE");
			menu3->setupMenu();
			menu3->displayMenu();

			engine3 = new MenuEngine(menu3, *(new SDL_Event()));
			int buttonNum = engine3->runEngine();
			int destination = menu3->destinationMap(buttonNum);

			switch (destination)
			{
			case _GameLog_:
				GameController::getInstance()->toggleGame();
				break;
			case _MapLog_:
				MapController::getInstance()->toggleMap();
				break;
			case _CharacterLog_:
				CharacterController::getInstance()->toggleCharacter();
				break;
			case _DiceLog_:
				DiceController::getInstance()->toggleDice();
				break;
			case _ReturnToGame_:
				exit = true;
				break;
			}
			menu3->getMenuWindow()->hideWindow();
			delete menu3;
			menu3 = nullptr;
			delete engine3;
			engine3 = nullptr;

		} while (exit == false);

	}

	//End here
	menu->getMenuWindow()->hideWindow();
	delete menu;
	menu = nullptr;
	delete engine;
	engine = nullptr;
	return _MainMenu_;
}

//!manages campaign editor menu, and driver for assignment 2 specifications
int GameLoops::mainMenuLoop(char* path, char* campaign)
{
	GameController::getInstance()->log("Main menu loaded.");
	MainMenu* menu = new MainMenu("Main Menu");
	menu->setupMenu();
	menu->displayMenu();
	
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int destination = engine->runEngine();
	destination = menu->destinationMap(destination);
	
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//!launches the campaign editor main menu loop
int GameLoops::campaignManagerLoop(char* path, char* campaign)
{
	GameController::getInstance()->log("Campaign menu loaded.");
	CampaignManager* manager = new CampaignManager("final build");
	manager->setupMenu();
	manager->displayMenu();
	MenuEngine* engine = new MenuEngine(manager, this->_event);
	
	int destination = engine->runEngine(campaign);

	if(destination >=0)
		this->_currentCampaignTracker = SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(campaign);

	destination = manager->destinationMap(destination, campaign);
	
	
	manager->hideMenu();
	delete engine;
	engine = nullptr;
	delete manager;
	manager = nullptr;
	return destination;
}

//launches create edit player for game
int GameLoops::createEditPlayer()
{
	GameController::getInstance()->log("Character Management Menu loaded.");
	CharacterCreateEditMenu* menu = new CharacterCreateEditMenu("CREATE / EDIT CHARACTERS");
	menu->setupMenu();
	menu->displayMenu();
	bool returnToMainMenu = false;
	MenuEngine* engine = new MenuEngine(menu, *(new SDL_Event()));
	int destination;
	int buttonNum;

	// Run engine and get the destination
	buttonNum = engine->runEngine();
	destination = menu->destinationMap(buttonNum);
	
	// Hide menu, return back
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//! Initiates sequence to create a new player
int GameLoops::createNewPlayer(){
	GameController::getInstance()->log("Character Creation sequence started.");
	// First, we will have to go to console to get the name of the new Character
	char conf = 'X'; // Will be used to confirm console input from the user
	string name = ""; // Will be used to get the Character's name
	string input = ""; // Will be used to get input
	int selectedRace = 0; // Will be used to get the Character's race
	int selectedLevel = 0; // Will be used to get the Character's selected level

	bool characterIsReady = false;
	while (!characterIsReady){
		// Get the Name the user wants
		do {
			system("CLS");
			cout << "Please enter the name you would like to have for your character: ";
			cin >> name;
			cout << "You entered " << name << ". Are you happy with this? (Y/N) ";
			cin >> conf;
		} while (!(conf == 'Y' || conf == 'y'));
		conf = 'X';

		// Next, get the Race of the Fighter
		selectedRace = choosePlayerRace();

		// Will get the starting level of the Character, confirming that a proper value is provided
		do {
			system("CLS");
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
		characterIsReady = true;
	}

	// The Character will now be created
	// The user will be asked if they want to put the user-created items into their Character's backpack
	Fighter *myChar = CharacterBuilder::create(selectedLevel, Race(selectedRace), name);
	if (addUserMadeItems())
		//myChar->fillBackpack(ItemCreator::loadItemsFromFile());
		ItemCreator::loadItemsFromFile(myChar->backpack);

	int destination;
	// The Character will now be saved to file. If saved successfully, display stats
	if (CharacterSaveManager::saveCharacter(myChar, *(new SDL_Event()))){
		destination = _DisplayPlayerStats_;
		_currentFighterTracker = myChar;
	}
	else {
		destination = _CreateEditPlayer_;
		delete myChar;
	}

	return destination;
}

//! Initiates sequence to edit an existing character
int GameLoops::editExistingPlayer(){
	GameController::getInstance()->log("Character Editing sequence started.");
	Fighter* thePlayer = loadPlayer();

	// If we didn't get a player, then we MUST return
	if (thePlayer == NULL)
		return _CreateEditPlayer_;

	_currentFighterTracker = thePlayer;
	// Else we can start editing the player! Setup menu and display it
	EditCharacterMenu* menu = new EditCharacterMenu("EDIT CHARACTER", thePlayer);
	menu->setupMenu();
	menu->displayMenu();

	// Create the MenuEngine to gather input
	MenuEngine* engine = new MenuEngine(menu, *(new SDL_Event()));
	int buttonNum = engine->runEngine();
	int destination = menu->destinationMap(buttonNum);
	
	// Delete the menu
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//! Launches menu to edit Race of a preloaded Fighter
int GameLoops::editPlayerRace(Fighter* thePlayer){
	GameController::getInstance()->log("Race Editing sequence started.");
	// Setup menu to edit race
	EditRaceMenu* menu = new EditRaceMenu("SELECT RACE");
	menu->setupMenu();
	menu->displayMenu();

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int destination = engine->runEngine();

	// Get and set selected race
	int selectedRace = menu->destinationMap(destination);
	thePlayer->setRace(Race(selectedRace));

	// Save the Character

	CharacterSaveManager::saveCharacter(thePlayer, *(new SDL_Event()));
	// Delete the menu and return
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return _SuccessRaceChange_;
}

//! Launches menu asking if wanting to add user-created items to user-created player
bool GameLoops::addUserMadeItems(){
	GameController::getInstance()->log("Confirming addition of user-created items");
	AddUseMadeItemsConfirmationMenu *menu = new AddUseMadeItemsConfirmationMenu("CONFIRM");
	menu->setupMenu();
	menu->displayMenu();
	bool canAddItems = false;

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int destination = engine->runEngine();
	destination = menu->destinationMap(destination);
	if (destination == _YesConfirmation_)
		canAddItems = true;
	else canAddItems = false;

	// Delete the menu and return
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return canAddItems;
}

//! Gets back the Race which will be used for a new Fighter
int GameLoops::choosePlayerRace(){
	// Setup menu to edit race
	GameController::getInstance()->log("Race Selection sequence loaded.");
	EditRaceMenu* menu = new EditRaceMenu("SELECT RACE");
	menu->setupMenu();
	menu->displayMenu();

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int destination = engine->runEngine();

	// Get and set selected race
	int selectedRace = menu->destinationMap(destination);

	// Delete the menu and return
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return selectedRace;
}

//! Displays the players stats on screen
int GameLoops::displayPlayerStats(Fighter* thePlayer){
	GameController::getInstance()->log("Displaying player stats");
	DisplayPlayerStatsWindow* menu = new DisplayPlayerStatsWindow("PLAYER STATS", thePlayer);
	menu->setupMenu();
	menu->displayMenu();

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int buttonNum = engine->runEngine();
	int destination = menu->destinationMap(buttonNum);

	// if the player wants to manage their equipment, we will go do that.
	// Return _DisplayPlayerStats_ afterward to return back to this menu
	if (destination == _ManageEquipment_){
		menu->hideMenu();
		thePlayer->equipOptions();
		destination = _DisplayPlayerStats_;
	}
	else {
		// Otherwise, the player selected to go back, so we will go back to Create/Edit
		destination = _CreateEditPlayer_;
		delete _currentFighterTracker;
	}
	

	// Delete the menu and return
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//! Displays that race was changed successfully
int GameLoops::displaySuccessfulRaceChange(Fighter* thePlayer){
	GameController::getInstance()->log("Race change - success!");
	SuccessOnRaceChangeMenu* menu = new SuccessOnRaceChangeMenu("SUCCESS", thePlayer);
	menu->setupMenu();
	menu->displayMenu();

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int buttonNum = engine->runEngine();
	int destination = menu->destinationMap(buttonNum);

	// Once we have run the menu, we can delete the _currentPlayerTracker
	if (_currentFighterTracker != nullptr){
		delete _currentFighterTracker;
	}

	// Delete the menu and return
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//! Displays that name was changed successfully
int GameLoops::displaySuccessfulNameChange(Fighter* thePlayer){
	GameController::getInstance()->log("Name change - success!");
	SuccessOnNameChangeMenu* menu = new SuccessOnNameChangeMenu("SUCCESS", thePlayer);
	menu->setupMenu();
	menu->displayMenu();

	// Create engine and run it
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int buttonNum = engine->runEngine();
	int destination = menu->destinationMap(buttonNum);

	// Once we have run the menu, we can delete the _currentPlayerTracker
	if (_currentFighterTracker != nullptr){
		delete _currentFighterTracker;
	}
	// Delete the menu and return
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//! Loads a character from file as per user selection, and returns a pointer to it
Fighter* GameLoops::loadPlayer(){
	GameController::getInstance()->log("Initiating character load sequence");
	Fighter* temp = nullptr;
	LoadCharacterMenu* menu = new LoadCharacterMenu("LOAD CHARACTER");
	menu->setupMenu();
	menu->displayMenu();
	bool returnFighter = false;
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	while (!returnFighter){
		// Get the destination from running the engine
		int destination = engine->runEngine();

		// Get name of Character based on the destination
		string tempName = menu->getNameOfCharacterFromIndex(destination);

		destination = menu->destinationMap(destination);

		// If getting from destination map returns 1, it means the user selected a valid name
		// This means that we can load the Character
		if (destination == 1){
			temp = CharacterSaveManager::loadCharacter(tempName);
			GameController::getInstance()->log(temp->getName() + " has been loaded for use.");
			returnFighter = true;
		}
		else if (destination == 0)
			returnFighter = true; // Dummy value just to break the loop
	}
	
	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return temp;
}

//! Displays menu for creating and editing items
int GameLoops::createEditItems(Container * userContainer, int choice)
{
	//system("CLS");
	GameController::getInstance()->log("Create weapon menu loaded.");
	//	cout << "1) Create Weapon\n2) Create Armour\n3) Create Helmet\n4) Create Shield\n5) Create Belt\n6) Create Ring\n7) Create Boots\n
	// 8) Print created items\n9) Save Items to File\n10) Load Items from File\n11) Back to Menu\n12) Randomly Generate Items\nEnter Choice: ";
	ItemCreator::createItems(userContainer, choice);
	//system("CLS");
	return _CreateEditItems_;
}

//! Allows for creating and editing items
int GameLoops::createEditItems()
{
	GameController::getInstance()->log("Item creation menu loaded.");
	ItemMenus* menu = new ItemMenus("Item Creation");
	menu->setupMenu();
	menu->displayMenu();

	Container * userContainer = new Container();

	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int destination = engine->runEngine();
	destination = menu->destinationMap(destination);

	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//! Prints items to screen
int GameLoops::printItems(Container * userContainer)
{
	GameController::getInstance()->log("Print items menu loaded.");
	PrintItemsMenus * menu = new  PrintItemsMenus("Print Items");
	cout << userContainer->contentsToString();
	menu->setContainer(userContainer);
	menu->setupMenu();
	menu->displayMenu();

	MenuEngine* engine = new MenuEngine(menu, this->_event);
	int destination = engine->runEngine();
	destination = menu->destinationMap(destination);

	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return destination;
}

//! Launches menu for deleting saved Characters
int GameLoops::deleteCharacter(){
	GameController::getInstance()->log("Initiating Character Deletion Sequence.");
	// Setup the Delete Menu
	DeleteCharacterMenu* menu = new DeleteCharacterMenu("DELETE EXISTING CHARACTER");
	menu->setupMenu();
	menu->displayMenu();
	bool returnToPrevMenu = false; // To prevent returning to previous menu
	int destination;
	string tempName;

	// Setup MenuEngine, attach it to the Delete Menu
	MenuEngine* engine = new MenuEngine(menu, this->_event);
	while (!returnToPrevMenu){

		// Get the destination from running the engine
		destination = engine->runEngine();

		// Get name of Character based on the destination
		tempName = menu->getNameOfCharacterFromIndex(destination);

		// Get if valid name was selected
		destination = menu->destinationMap(destination);

		// If getting from destination map returns 1, it means the user selected a valid name
		// This means that we can delete the Character
		if (destination == 1){
			CharacterSaveManager::removeCharacter(tempName);
			returnToPrevMenu = true;
		}
		else returnToPrevMenu = true;
	}

	menu->hideMenu();
	delete engine;
	engine = nullptr;
	delete menu;
	menu = nullptr;
	return _CreateEditPlayer_;
}

//!once a campaign is selected, this function facilitates editing
int GameLoops::editExistingCampaignLoop(char* path, char* campaign)
{
	GameController::getInstance()->log("A campaign was loaded for play.");
	START_AFTER_SEQUENCE_CHANGE:
	std::cout<<path<<std::endl;
	CampaignMapManagers* manager = new CampaignMapManagers("assignment2", this->_currentCampaignTracker);
	manager->setupMenu();
	manager->displayMenu();
	
	MenuEngine* engine = new MenuEngine(manager, this->_event);

	int destination;

	ABORT_SEQUENCE_CHANGE:
	destination = engine->runEngine(path);
	
	//first check if sequence change button or choose from default map was clicked
	//if not then continue as normal
	if((SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(path) != SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(Others::_SequenceChangeButton_))&&(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(path) != SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(Others::_DefaultMapSelectionButton_)))
	{
		destination = manager->destinationMap(destination, path);
		SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(campaign, manager->getCampaignNameOfMap());
	}

	//otherwise do a sequence change
	else if(SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(path) == SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(Others::_SequenceChangeButton_))
	{
		//first take input for which map needs to change, ignoring render for sequence change button
		int index1, index2;

		//first get index 1, destination holds index of change sequence
		index1 = engine->runEngine(destination, -1, path);
		if(index1 == -1)
			goto ABORT_SEQUENCE_CHANGE;

		index2 = engine->runEngine(destination, index1, path);
		if(index2 == -1)
			goto ABORT_SEQUENCE_CHANGE;

		manager->changeSequence(index1, index2);
		GameController::getInstance()->log("Map sequence for campaign " + (SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(campaign)) +" was changed");
		manager->hideMenu();
		delete engine;
		engine = nullptr;
		delete manager;
		manager = nullptr;
		goto START_AFTER_SEQUENCE_CHANGE;
	}
	
	//other wise get and input for map selection
	else if((SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(path) == SingletonInputsAndStringManager::getInstance()->convertCharPointerToString(Others::_DefaultMapSelectionButton_)))
	{
		SingletonDefaultMapsMenu::getInstance()->getMenuWindow()->unHideWindow();
		MenuEngine* defaultmaps = new MenuEngine(SingletonDefaultMapsMenu::getInstance(), this->_event);
		destination = defaultmaps->runEngine(path);
		SingletonDefaultMapsMenu::getInstance()->getMenuWindow()->hideWindow();
		destination = manager->destinationMap(_MaximumMapsPerCampaign_+1, path);
		SingletonDefaultMapsMenu::getInstance()->getMenuWindow()->hideWindow();
		delete defaultmaps;
		defaultmaps = nullptr;
	}

	manager->hideMenu();
	delete engine;
	engine = nullptr;
	delete manager;
	manager = nullptr;
	return destination;
}

