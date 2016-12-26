#include "levels.h"

//!parameterized constructor initializes the path from which the level needs to be loaded from
//!also sets the window for the level
Level::Level(std::string path, LevelWindow* window)
{
	_directory_path_for_level_file_text_file = path;
	this->_level_window = window;
}

//!default constructor for testing purposes only
Level::Level()
{
}

//!accessor for string version of map that is not simplified
std::vector<std::string> Level::getMapStringVersiion()
{
	return this->_level;
}

//!setter for main map that is NOT simplified
void Level::setMainMapVector(std::vector<std::string> newmap)
{
	this->_level = newmap;
}

//!accessor for string version of map that has all environment symbols simplified to just obstruction or free path
std::vector<std::string> Level::getMapSimpleVersion()
{
	std::vector<std::string> temp;
	std::string s = "";

	Environment* floor = nullptr;
	Environment* exit = nullptr;
	for (int x = 0; x < this->_environment_components.size(); x++)
	{
		if (this->_environment_components[x]->getComponentName() == "floor")
			floor = this->_environment_components[x];
		else if (this->_environment_components[x]->getComponentName() == "exit")
			exit = this->_environment_components[x];
	}

	//first convert to simple map
	for (int y = 0; y < this->_level.size(); y++)
	{
		s = "";
		for (int x = 0; x < this->_level[y].length(); x++)
		{
			//first check player
			if (this->_level[y].at(x) == SimplifiedMapSymbols::_Player_)
			{
				s += SimplifiedMapSymbols::_Player_;
			}

			//check container
			else if (this->_level[y].at(x) == SimplifiedMapSymbols::_BasicContainer_)
			{
				s += SimplifiedMapSymbols::_BasicContainer_;
			}

			//check enemy
			else if (this->_level[y].at(x) == SimplifiedMapSymbols::_Enemies_)
			{
				s += SimplifiedMapSymbols::_Enemies_;
			}

			//check friend
			else if (this->_level[y].at(x) == SimplifiedMapSymbols::_Friend_)
			{
				s += SimplifiedMapSymbols::_Friend_;
			}

			//check free path for env component it should be floor
			else if (this->_level[y].at(x) == floor->getComponentChar())
			{
				s += SimplifiedMapSymbols::_FreePath_;
			}

			//check for exit door
			else if (this->_level[y].at(x) == exit->getComponentChar())
			{
				s += SimplifiedMapSymbols::_ExitDoor_;
			}

			//otherwise it is obstructive environment
			else
			{
				s += SimplifiedMapSymbols::_Obstruction_;
			}
		}
		//push the string back
		temp.push_back(s);
	}

	//return the simple map
	return temp;
}


//!accessor for string version of map that has all environment symbols simplified to just obstruction or free path
std::vector<std::string>* Level::getMapSimplePtrVersion()
{
	std::vector<std::string>* temp = new std::vector<std::string>();
	std::string s = "";

	Environment* floor = nullptr;
	Environment* exit = nullptr;
	for (int x = 0; x < this->_environment_components.size(); x++)
	{
		if (this->_environment_components[x]->getComponentName() == "floor")
			floor = this->_environment_components[x];
		else if (this->_environment_components[x]->getComponentName() == "exit")
			exit = this->_environment_components[x];
	}

	//first convert to simple map
	for (int y = 0; y < this->_level.size(); y++)
	{
		s = "";
		for (int x = 0; x < this->_level[y].length(); x++)
		{
			//first check player
			if (this->_level[y].at(x) == SimplifiedMapSymbols::_Player_)
			{
				s += SimplifiedMapSymbols::_Player_;
			}

			//check container
			else if (this->_level[y].at(x) == SimplifiedMapSymbols::_BasicContainer_)
			{
				s += SimplifiedMapSymbols::_BasicContainer_;
			}

			//check enemy
			else if (this->_level[y].at(x) == SimplifiedMapSymbols::_Enemies_)
			{
				s += SimplifiedMapSymbols::_Enemies_;
			}

			//check friend
			else if (this->_level[y].at(x) == SimplifiedMapSymbols::_Friend_)
			{
				s += SimplifiedMapSymbols::_Friend_;
			}

			//check free path for env component it should be floor
			else if (this->_level[y].at(x) == floor->getComponentChar())
			{
				s += SimplifiedMapSymbols::_FreePath_;
			}

			//check for exit door
			else if (this->_level[y].at(x) == exit->getComponentChar())
			{
				s += SimplifiedMapSymbols::_ExitDoor_;
			}

			//otherwise it is environment
			else
			{
				s += SimplifiedMapSymbols::_Obstruction_;
			}
		}
		//push the string back
		temp->push_back(s);
	}

	//return the simple map
	return temp;
}

//!this function loads the artwork and assigns them to approprate vectors
void Level::createLevelForTargetWindow()
{
	Environment* comp;

	int charNum = MapSymbolsData::_EnvironmentStart_;
	std::vector<std::string> splitString;
	bool obstruction;
	this->_playerPath = SingletonFilePathAndFolderManager::getInstance()->getPlayerImagePath();
	this->_basicContainerPath = SingletonFilePathAndFolderManager::getInstance()->_path_to_basic_container;
	this->_enemyPath = SingletonFilePathAndFolderManager::getInstance()->_path_to_basic_enemy;
	this->_friendPath = SingletonFilePathAndFolderManager::getInstance()->_path_to_basic_friend;
	//environment rendering
	//2 increment because after each line, I have 1 line for descriptions.
	for(int x=0; x<this->_environmentComponentNames.size(); x+=2)
	{
		splitString = SingletonInputOutputManager::getInstance()->splitString(this->_environmentComponentNames[x]);

		if(splitString[1] == "true")
			obstruction = true;
		else
			obstruction = false;

		comp = new Environment(splitString[0], this->_environmentComponentNames[x+1], (char)charNum, environment, obstruction, (this->_environmentComponentPath + splitString[2]));
		_environment_components.push_back(comp);
		charNum++;
	}

	//container loading
	std::vector<Item*> test;
	this->_container = new Container(0, test, "basic container", MapSymbolsData::_BasicContainer_, container, this->_basicContainerPath);

	this->_corpse = new Container(0, test, "basic container", MapSymbolsData::_BasicContainer_, container, SingletonFilePathAndFolderManager::getInstance()->_path_to_corpse);

	//characters loading
	this->_player = new GameComponent("player", _Player_, character, this->_playerPath);

	//enemis loading
	this->_enemy = new Monster();

	//friend loading
	this->_friend = new Monster();
	this->_friend->setImagePath(SingletonFilePathAndFolderManager::getInstance()->_path_to_basic_friend);
	this->_friend->setComponentChar(SimplifiedMapSymbols::_Friend_);
	this->_friend->setComponentName("friend");

	//now check if theme is valid
	//rule 1: 1 component that is named floor and that is not an obstruction to player
	//rule 2: 1 and 1 component only that is named exit which is not an obstruction to player
	//rule 3: at least 1 component that is an obstruction to player
	bool floor_validity = false;
	bool exit_validity = false;
	bool obstruction_validity = false;
	int exit_counter = 0;
	int floor_counter = 0;
	for(int x=0; x< this->_environment_components.size(); x++)
	{
		if(this->_environment_components[x]->getComponentName() == "floor")
		{
			floor_counter++;
			if(this->_environment_components[x]->isComponentObstructionToPlayer() == false)
				floor_validity = true;
		}

		else if((this->_environment_components[x]->getComponentName() == "exit"))
		{
			exit_counter++;
			if(this->_environment_components[x]->isComponentObstructionToPlayer() == false)
				exit_validity = true;
		}

		else if(this->_environment_components[x]->isComponentObstructionToPlayer() == true)
			obstruction_validity = true;
	}

	if((floor_validity == false)||(exit_validity==false)||(obstruction_validity = false)||(exit_counter!=1))
	{
		std::cout<<"Invalid Theme loading attempted."<<std::endl<<std::endl;
		std::cout<<"RULE 1: One and only One component named floor that is not an obstruction to player."<<std::endl;
		std::cout<<"RULE 2: One and only One component named exit that is not an obstruction to player."<<std::endl;
		std::cout<<"RULE 3: At least one component that is an obstruction to player."<<std::endl;
		std::cout<<"exiting program."<<std::endl;
		system("pause");
		exit(-1);
	}

	//setup the evironment component vector
	for(int x=0; x<_environment_components.size(); x++)
		_environment_components[x]->setupComponentOnTargetWindowRenderer(this->_level_window->getRenderer());

	//setup player image
	this->_player->setupComponentOnTargetWindowRenderer(this->_level_window->getRenderer());

	//setup container image
	this->_container->setupComponentOnTargetWindowRenderer(this->_level_window->getRenderer());

	//setup enemy image
	this->_enemy->setupComponentOnTargetWindowRenderer(this->_level_window->getRenderer());

	//setup friend image
	this->_friend->setupComponentOnTargetWindowRenderer(this->_level_window->getRenderer());

	//setup corpse image 
	this->_corpse->setupComponentOnTargetWindowRenderer(this->_level_window->getRenderer());

	//draw the vertical and horzontal lines for the level
	SDL_SetRenderDrawColor(this->_level_window->getRenderer(), 0, 255, 0, 0);
	int y = (this->_level_window->getGamePlay_Y_Grids() * this->_level_window->getGridY_Length()) + 1;

	//first draw the horizontal line at bottom
	for(int x=0; x< this->_level_window->getWindowWidth(); x++)
		SDL_RenderDrawPoint(this->_level_window->getRenderer(), x, y);

	int x = (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()) + 1;
	
	//draw vertical line top down on the right
	std::cout<<"X is: "<<x<<std::endl<<"window width: "<<this->_level_window->getWindowWidth();
	/*for(int y=0; y<((this->_level_window->getNumberOfGrids_Y() * this->_level_window->getGridY_Length()) + 1); y++)
	{
		SDL_RenderDrawPoint(this->_level_window->getRenderer(), x, y);
	}*/
	for(int y=0; y<((this->_level_window->getGamePlay_Y_Grids() * this->_level_window->getGridY_Length()) + 1); y++)
	{
		SDL_RenderDrawPoint(this->_level_window->getRenderer(), x, y);
	}

}

//!the level window accessor
LevelWindow* Level::getLevelWindow()
{
	return this->_level_window;
}

//!this function uses the text level vector and the art vectors to render the level on the target window
void Level::renderAndDisplayLevel()
{
	SDL_Rect dest;
	dest.h = this->_level_window->getGridY_Length();
	dest.w = this->_level_window->getGridX_Length();
	dest.x = 0;
	dest.y = 0;

	//creating the gameplay rectangular grids based the _level text file
	//for(int y=0; y<this->_level_window->getNumberOfGrids_Y(); y++)
	for(int y=0; y<this->_level_window->getGamePlay_Y_Grids(); y++)
	{
		if(_level.size()< y+1)
			break;
		dest.y = y * this->_level_window->getGridY_Length();
		//for(int x=0; x<=this->_level_window->getNumberOfGrids_X(); x++)
		for(int x=0; x<this->_level_window->getGamePlay_X_Grids(); x++)
		{
			this->_gameplayGrids.push_back(dest);
			if(_level[y].length() < x+1)
				break;
			dest.x = x * this->_level_window->getGridX_Length();

			//check if it is player
			if((_level[y].at(x) == _player->getComponentChar()))
					this->_level_window->loadTextureOnRenderer(_player->getImageDetails()->getImageTexture(), nullptr, &dest);

			//check if it is container
			else if(_level[y].at(x) == _container->getComponentChar())
					this->_level_window->loadTextureOnRenderer(_container->getImageDetails()->getImageTexture(), nullptr, &dest);

			//check if it is enemy
			else if (_level[y].at(x) == SimplifiedMapSymbols::_Enemies_)
				this->_level_window->loadTextureOnRenderer(_enemy->getImageDetails()->getImageTexture(), nullptr, &dest);

			//check if it is friend
			else if (_level[y].at(x) == SimplifiedMapSymbols::_Friend_)
				this->_level_window->loadTextureOnRenderer(_friend->getImageDetails()->getImageTexture(), nullptr, &dest);

			//otherwise it is probaly envronment
			//render the map
			else
			{
				for(int j=0; j<_environment_components.size(); j++)
				{
					//check is it is environment
					if(_level[y].at(x) == _environment_components[j]->getComponentChar())
						this->_level_window->loadTextureOnRenderer(_environment_components[j]->getImageDetails()->getImageTexture(), nullptr, &dest);

					//check if it is player
					//else if((_level[y].at(x) == _player->getComponentChar()))
						//this->_level_window->loadTextureOnRenderer(_player->getImageDetails()->getImageTexture(), nullptr, &dest);

					//check if it is container
					//else if(_level[y].at(x) == _container->getComponentChar())
						//this->_level_window->loadTextureOnRenderer(_container->getImageDetails()->getImageTexture(), nullptr, &dest);
				}
			}
			//else nothing happens, grid remains blank
		}
	}

	//display the level once render update is complete
	this->_level_window->displayWindow();
}

//!accessor for dummy container component
Container* Level::getContainerComponent()
{
	return this->_container;
}

//!environment components accessor
std::vector<Environment*> Level::getEnvironmentComponents()
{
	return _environment_components;
}

//!accessor for dummy player component
GameComponent* Level::getPlayerComponent()
{
	return this->_player;
}

//!accessor for dummy enemy
Monster* Level::getEnemy()
{
	return this->_enemy;
}

//!accessor for dummy friend
Monster* Level::getFriend()
{
	return this->_friend;
}

//!adds a recangle to the grids for gameplay
void Level::addRectToGamePlayGrids(SDL_Rect dest)
{
	this->_gameplayGrids.push_back(dest);
}

//!access grid coorinates that are used in gameplay
std::vector<SDL_Rect> Level::getGameplayGridsRects()
{
	return this->_gameplayGrids;
}

//!access texture for a specific environment
SDL_Texture* Level::getEnvironmentTexture(int index)
{
	if((index+1)>this->_environment_components.size())
	{
		std::cout<<"Invalid index for texture access, exiting program."<<std::endl;
		exit(-1);
	}
	return _environment_components[index]->getImageDetails()->getImageTexture();
}

//!function destroy dynamically allocated memory for level
void Level::destroyLevel()
{
	for(int x=0; x<_environment_components.size(); x++)
	{
		if(_environment_components[x]!=nullptr)
		{
			_environment_components[x]->destroyComponent();
			delete _environment_components[x];
			_environment_components[x] = nullptr;
		}
	}
	if(this->_player != nullptr)
	{
		_player->destroyComponent();
		delete _player;
		_player = nullptr;
	}
	if(this->_container != nullptr)
	{
		_container->destroyComponent();
		delete this->_container;
		this->_container = nullptr;
	}
	if (this->_enemy != nullptr)
	{
		this->_enemy->destroyComponent();
		delete this->_enemy;
		this->_enemy = nullptr;
	}
	if (this->_friend != nullptr)
	{
		this->_friend->destroyComponent();
		delete this->_friend;
		this->_friend = nullptr;
	}
	if(this->_level_window!=nullptr)
	{
		this->_level_window->destroyWindow();
		this->_level_window = nullptr;
	}
}

//!destructor just calls the destroy level method
Level::~Level()
{
	destroyLevel();
}






