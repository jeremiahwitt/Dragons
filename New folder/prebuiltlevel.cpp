#include "prebuiltlevel.h"

//!default constructor for testing purposes only
PreBuiltLevel::PreBuiltLevel()
{
	this->_player = nullptr;
}

//!parameterized constructor sets the path from which the pre built map needs to be loaded
PreBuiltLevel::PreBuiltLevel(std::string path, Fighter* player)
{
	this->_player = player;
	this->_directory_path_for_level_file_text_file = path;

}

//!loads the user created level in private member variables
void PreBuiltLevel::loadUserCreatedLevel(std::string path)
{
	//load the level and component path
	this->_level = SingletonFilePathAndFolderManager::getInstance()->loadUserGeneratedLevel(path, &this->_environmentComponentPath);

	//load the component names
	this->_environmentComponentNames = SingletonInputOutputManager::getInstance()->readFileLineByLine(this->_environmentComponentPath + SingletonFilePathAndFolderManager::getInstance()->getNameofFileContainingAssetNames());
}

//!sets the level text vector that would be used to set the level on the target window
void PreBuiltLevel::setLevelOnTargetWindow()
{
	this->_level = SingletonInputOutputManager::getInstance()->readFileLineByLine(_directory_path_for_level_file_text_file);
}

//!sets the pointer rect to values from current rects in map
void PreBuiltLevel::getDestRectsForObserver(SDL_Rect* dest1, SDL_Rect* dest2)
{
	*dest1 = this->_dest1ForObserver;
	*dest2 = this->_dest2ForObserver;
}

//!when NPCs die, this function is called to have them added as a container on map
void PreBuiltLevel::addContainerOnTheMap(ContainerOnMap* prolly_a_dead_dude)
{
	this->_containersOnMap.push_back(prolly_a_dead_dude);
}

//!first creates a level window based on the level text vector
//!then calls parent function to the artwork on the window
void PreBuiltLevel::createLevelForTargetWindow()
{
	//make level window based on loaded text vector
	this->_level_window = new LevelWindow("PreBuilt", this->_level[0].length(), this->_level.size());

	//call parent function
	Level::createLevelForTargetWindow();

	//create button destinations
	this->_level_window->setFontType(9);
	this->_level_window->setTitleFontSize(72);

	this->_inventoryPaneDest.x = (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()) + (this->_level_window->getWindowWidth() - (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length())) * 0.1;
	this->_inventoryPaneDest.y = this->_level_window->getWindowHeight() * 0.05;
	this->_inventoryPaneDest.w = (this->_level_window->getWindowWidth() - (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length())) * 0.8;
	this->_inventoryPaneDest.h = this->_level_window->getWindowHeight() * 0.045;
	this->_level_window->addButton("Player Status", 255, 0, 0, this->_inventoryPaneDest);

	this->_movePlayerDest.x = this->_inventoryPaneDest.x;
	this->_movePlayerDest.w = this->_inventoryPaneDest.w;
	this->_movePlayerDest.h = this->_inventoryPaneDest.h;
	this->_movePlayerDest.y = this->_inventoryPaneDest.y + this->_inventoryPaneDest.h * 2;
	this->_level_window->addButton("Move Player", 255, 0, 0, this->_movePlayerDest);

	this->_interact.x = this->_inventoryPaneDest.x;
	this->_interact.w = this->_inventoryPaneDest.w;
	this->_interact.h = this->_inventoryPaneDest.h;
	this->_interact.y = this->_movePlayerDest.y + this->_inventoryPaneDest.h * 2;
	this->_level_window->addButton("Interact", 255, 0, 0, this->_interact);

	this->_attack.x = this->_inventoryPaneDest.x;
	this->_attack.w = this->_inventoryPaneDest.w;
	this->_attack.h = this->_inventoryPaneDest.h;
	this->_attack.y = this->_interact.y + this->_inventoryPaneDest.h * 2;
	this->_level_window->addButton("Attack", 255, 0, 0, this->_attack);

	this->_savePlayer.x = this->_inventoryPaneDest.x;
	this->_savePlayer.w = this->_inventoryPaneDest.w;
	this->_savePlayer.h = this->_inventoryPaneDest.h;
	this->_savePlayer.y = this->_attack.y + this->_inventoryPaneDest.h * 2;
	this->_level_window->addButton("Save Player", 255, 0, 0, this->_savePlayer);

	this->_endTurn.x = this->_inventoryPaneDest.x;
	this->_endTurn.w = this->_inventoryPaneDest.w;
	this->_endTurn.h = this->_inventoryPaneDest.h;
	this->_endTurn.y = this->_savePlayer.y + this->_inventoryPaneDest.h * 2;
	this->_level_window->addButton("End Turn", 255, 0, 0, this->_endTurn);

	this->_gameLog.x = this->_inventoryPaneDest.x;
	this->_gameLog.w = this->_inventoryPaneDest.w;
	this->_gameLog.h = this->_inventoryPaneDest.h;
	this->_gameLog.y = this->_endTurn.y + this->_inventoryPaneDest.h * 2;
	this->_level_window->addButton("Game Log", 255, 0, 0, this->_gameLog);

	this->_exitPlay.x = this->_inventoryPaneDest.x;
	this->_exitPlay.w = this->_inventoryPaneDest.w * 0.8;
	this->_exitPlay.h = this->_inventoryPaneDest.h;
	this->_exitPlay.y = this->_gameLog.y + this->_inventoryPaneDest.h * 2;
	this->_level_window->addButton("Exit play", 255, 0, 0, this->_exitPlay);

	//setup the line for game log
	int x = this->getLevelWindow()->getWindowWidth() / 2;
	SDL_SetRenderDrawColor(this->getLevelWindow()->getRenderer(), 0, 255, 0, 0);
	for (int y = this->getLevelWindow()->getGamePlay_Y_Grids()*this->getLevelWindow()->getGridY_Length()+1; y < this->getLevelWindow()->getWindowHeight(); y++)
	{
		SDL_RenderDrawPoint(this->getLevelWindow()->getRenderer(), x, y);
	}
	//using namespace LoggerColorGame;
	//now give a text labels
	SDL_Rect loggers;
	loggers.w = this->_exitPlay.w;
	loggers.h = this->_exitPlay.h / 2;
	loggers.x = ((this->getLevelWindow()->getWindowWidth() / 2)/2) - loggers.w / 2;
	loggers.y = this->getLevelWindow()->getGamePlay_Y_Grids()*this->getLevelWindow()->getGridY_Length() + 8;
	this->_loggerYend = loggers.y +loggers.h;
	this->_level_window->addTextLabel("Map log", 255, 165, 0, loggers);

	loggers.w = loggers.w * 2;
	loggers.x = ((this->getLevelWindow()->getWindowWidth() / 2)) + ((this->getLevelWindow()->getWindowWidth() / 2) / 2) - loggers.w / 2;
	//this->_level_window->addTextLabel("Character log", _CHAR_R_, _CHAR_G_, _CHAR_B_, loggers);
	this->_level_window->addTextLabel("Character log", 0, 255, 0, loggers);

	//setup the menu component
	this->_level_window->setMenuOnRenderer();
}

//!sets up container coordinates on map
void PreBuiltLevel::setupContainersOnMap()
{
	ContainerOnMap* temp;
	//first find howmany an get there coordinates
	for (int y = 0; y < this->_level.size(); y++)
	{
		for (int x = 0; x < this->_level[y].size(); x++)
		{
			if (_level[y].at(x) == SimplifiedMapSymbols::_BasicContainer_)
			{
				temp = new ContainerOnMap();
				temp->stringIndex = y;
				temp->charIndex = x;
				temp->container = ContainerGenerator::generateContainer(this->_player);
				this->_containersOnMap.push_back(temp);
			}
		}
	}
}

//!sets up enemy coordinates on map
void PreBuiltLevel::setupEnemiesOnMap()
{
	Monster* temp;
	MonsterOnMapView* tempView;
	//first find howmany an get there coordinates
	for (int y = 0; y < this->_level.size(); y++)
	{
		for (int x = 0; x < this->_level[y].size(); x++)
		{
			if (_level[y].at(x) == SimplifiedMapSymbols::_Enemies_)
			{
				temp = MonsterFactory::createMonster(this->_player, false);
				temp->setPosition(y, x);
				temp->setMap(&this->getMapSimpleVersion());
				tempView = new MonsterOnMapView(temp, this, temp->_charType);
				temp->setupLevelObserver(this);
				this->_enemisOnMap.push_back(temp);
			}
			if (_level[y].at(x) == SimplifiedMapSymbols::_Friend_)
			{
				temp = MonsterFactory::createMonster(this->_player, true);
				temp->setComponentChar(SimplifiedMapSymbols::_Friend_);
				temp->setImagePath(SingletonFilePathAndFolderManager::getInstance()->_path_to_basic_friend);
				temp->setPosition(y, x);
				temp->setMap(&this->getMapSimpleVersion());
				tempView = new MonsterOnMapView(temp, this, temp->_charType);
				temp->setupLevelObserver(this);
				this->_enemisOnMap.push_back(temp);
			}
		}
	}
}

//!function to update destination rectangles for the observer
void PreBuiltLevel::setDestRectsForObserver(SDL_Rect dest1, SDL_Rect dest2)
{
	this->_dest1ForObserver = dest1;
	this->_dest2ForObserver = dest2;
}

//!container coordinate accessor
std::vector<ContainerOnMap*> PreBuiltLevel::getContainersOnMap()
{
	return this->_containersOnMap;
}

//!container coordinate accessor
void PreBuiltLevel::removeContainerOnMap(int index)
{
	SDL_Rect dest;
	SDL_Rect currentGrid;
	std::vector<std::string> temp = getMapStringVersiion();

	// container coordinates
	int coordinateX = _containersOnMap[index]->charIndex;
	int coordinateY = _containersOnMap[index]->stringIndex;

	// delete the container
	this->_containersOnMap.erase(this->_containersOnMap.begin() + index);

	// rerender the map
	for (int k = 0; k < getEnvironmentComponents().size(); k++)
	{
		//render the floor
		if (getEnvironmentComponents()[k]->getComponentName() == "floor")
		{
			dest.x = coordinateX*getLevelWindow()->getGridX_Length();
			dest.y = coordinateY*getLevelWindow()->getGridY_Length();
			dest.h = getLevelWindow()->getGridY_Length();
			dest.w = getLevelWindow()->getGridX_Length();

			//now update the environment for the observer
			_environmentForObserver = getEnvironmentComponents()[k];

			//make the x y of loop a free path
			temp[coordinateY].at(coordinateX) = getEnvironmentComponents()[k]->getComponentChar();
			setMainMapVector(temp);
			goto DONE_FLOOR;
		}

	}//done putting player to floor
	DONE_FLOOR:

	// Now set the grid for the update
	currentGrid.x = coordinateX*getLevelWindow()->getGridX_Length();
	currentGrid.y = coordinateY*getLevelWindow()->getGridY_Length();
	currentGrid.h = getLevelWindow()->getGridY_Length();
	currentGrid.w = getLevelWindow()->getGridX_Length();

	//update the two destination rectangles in subject
	setDestRectsForObserver(dest, currentGrid);

	//call the observer update and render and display, also lets all LevelObservers know the level has changed
	setRecentUpdateFlag(EmptyContainer);
	Notify();
	
}

//!enemy coordiante accessor
std::vector<Monster*> PreBuiltLevel::getEnemiesOnMap()
{
	return this->_enemisOnMap;
}

//!environment component path accessor
std::string PreBuiltLevel::getEnvironmentComponentsPath() const
{
	return this->_environmentComponentPath;
}

//!level text file path accessor
std::string PreBuiltLevel::getDirectoryPathForLevelTextFile() const
{
	return this->_directory_path_for_level_file_text_file;
}

//!path for player image accessor
std::string PreBuiltLevel::getPlayerPath() const
{
	return this->_playerPath;
}

//!enemy file path accessor
std::string PreBuiltLevel::getEnemyPath() const
{
	return this->_enemyPath;
}

std::string PreBuiltLevel::getFriendPath() const
{
	return this->_friendPath;
}

//!level text vector accessor
std::vector<std::string> PreBuiltLevel::getBuiltLevelFile() const
{
	return this->_level;
}

//!fighter accessor
Fighter* PreBuiltLevel::getPlayer()
{
	return this->_player;
}

//!map menu buttons accessor 
std::vector<SDL_Rect> PreBuiltLevel::getAllButtonDestinations()
{
	std::vector<SDL_Rect> temp;
	temp.push_back(this->_inventoryPaneDest);
	temp.push_back(this->_movePlayerDest);
	temp.push_back(this->_exitPlay);
	return temp;
}

/**
* Will set the initiative for all Characters that are on the map currently. Will then fill the initiative queue
* with all Characters
*/
void PreBuiltLevel::setAllInitiative(){
	GameController::getInstance()->log("Setting initiative for all characters in game.");
	// Will set the player, and then the Monster initiative
	_player->setInitiative();
	for (int i = 0; i < _enemisOnMap.size(); ++i){
		_enemisOnMap.at(i)->setInitiative();
	}
	// Next, we will set the initiative queue up
	setupInitiativeQueue();
}

/**
* Fills the initiative priority queue with all Characters. Will be used to determine order of Character turns
* during each round.
*/
void PreBuiltLevel::setupInitiativeQueue(){
	// First, we will push the Character into the queue
	GameController::getInstance()->log("\nAdding characters to priority queue...");
	_initiativeCharacterQueue.push(_player);
	GameController::getInstance()->log(_player->getName() + " has been added to the priority queue.");
	// Next, we will push all Monsters into the queue
	for (int i = 0; i < _enemisOnMap.size(); ++i){
		_initiativeCharacterQueue.push(_enemisOnMap.at(i));
		GameController::getInstance()->log(_enemisOnMap.at(i)->getName() + " has been added to the priority queue.");
	}
	GameController::getInstance()->log("Done adding players to queue.");
}

//!local destructor destroys the positions for enemies and containers
PreBuiltLevel::~PreBuiltLevel()
{
	for (int x = 0; x < this->_containersOnMap.size(); x++)
	{
		if (this->_containersOnMap[x] != nullptr)
		{
			delete this->_containersOnMap[x];
			this->_containersOnMap[x] = nullptr;
		}	
	}
	for (int x = 0; x < this->_enemisOnMap.size(); x++)
	{
		if (this->_enemisOnMap[x] != nullptr)
		{
			delete this->_enemisOnMap[x];
			_enemisOnMap[x] = nullptr;
		}
	}
}