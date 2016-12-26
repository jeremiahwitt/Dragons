#include "gameplayengine.h"
#include "GameLogMenu.h"
#include "LogViewMenu.h"
#include "ToggleLogMenu.h"
/*!
*default constructor just sets all values to default and false
*/
GamePlayEngine::GamePlayEngine()
{
	this->_level = nullptr;
	this->_event = nullptr;
	this->_moveSelect = false;
	this->_moveValidityTracker = false;
	this->_interactSelect = false;
	this->_attackSelect = false;
	this->_buttonSelect = false;
	this->_mapExit = false;
	this->_gameLog = false;
	this->_endPlayerTurn = false;
	this->_currentGrid.x = -1;
	this->_currentGrid.y = -1;
	this->_lastGrid.x = -1;
	this->_lastGrid.y = -1;
	this->_gridIndex = -1;
	this->_lastButtonIndex = -1;
	this->_exitCharacterIndex = -1;
	this->_exitStringIndex = -1;
	this->_currentButtonIndex = -1;
}

/*!
*attaches a level and an sdl event manager to engine
*/
void GamePlayEngine::attachLevel(PreBuiltLevel* level, SDL_Event* event_)
{
	this->_level = level;
	this->_event = event_;
	this->_buttons = this->_level->getAllButtonDestinations();
	this->_containers = this->_level->getContainersOnMap();
	this->_enemies = this->_level->getEnemiesOnMap();
	this->_observer = new MapObserver(level);

	this->maplogger.y = level->_loggerYend + 5;
	this->maplogger.x = 5;
	this->maplogger.h = level->getLevelWindow()->getWindowHeight() - level->_loggerYend;
	this->maplogger.w = level->getLevelWindow()->getWindowWidth() / 2 - 5;
	this->charlogger.y = level->_loggerYend + 5;
	this->charlogger.x = (level->getLevelWindow()->getWindowWidth() / 2) + 5;
	this->charlogger.h = level->getLevelWindow()->getWindowHeight() - level->_loggerYend;
	this->charlogger.w = level->getLevelWindow()->getWindowWidth() / 2 - 5;

	std::vector<std::string> temp = this->_level->getMapSimpleVersion();
	//setup the exit coordinates
	for (int stringC = 0; stringC < temp.size(); stringC++)
	{
		for (int charInd = 0; charInd < temp[stringC].length(); charInd++)
		{
			if (temp[stringC].at(charInd) == SimplifiedMapSymbols::_ExitDoor_)
			{
				this->_exitStringIndex = stringC;
				this->_exitCharacterIndex = charInd;
				goto DONE;
			}
		}
	}
	DONE:
	;
}

/*!
*detaches level and sdl manager from engine
*/
void GamePlayEngine::detachLevel()
{
	this->_level = nullptr;
	this->_event = nullptr;
	this->_moveSelect = false;
	this->_moveValidityTracker = false;
	this->_interactSelect = false;
	this->_attackSelect = false;
	this->_buttonSelect = false;
	this->_mapExit = false;
	this->_gameLog = false;
	this->_endPlayerTurn = false;
	this->_currentGrid.x = -1;
	this->_currentGrid.y = -1;
	this->_lastGrid.x = -1;
	this->_lastGrid.y = -1;
	this->_gridIndex = -1;
	this->_currentButtonIndex = -1;
	this->_buttons.clear();
	this->_containers.clear();
	this->_enemies.clear();
	delete this->_observer;
	this->_observer = nullptr;
}

//index 0 is player status
//index 1 is move
//index 2 is interact
//index 3 is attack
//index 4 is save player
//index 5 is exit play
/*!
*function runs gameplay loop, returns 0 if player prefers going to next map, or 1 if player wants to quit playing campaign
*/
int GamePlayEngine::runEngine()
{
	bool exit = false;
	int destToReturn;
	//this->_level->_player->setMap(&this->_level->getMapSimpleVersion());
	this->_level->_player->setupLevelObserver(this->_level);
	SDL_Event keyevent;    //The SDL event that we will poll to check if key is pressed during turn rolling

	while (exit == false){
		// First, we will set initiative for ALL characters, as per d20 rules
		Characters* temp = NULL;
		_level->setAllInitiative();
		
		GameController::getInstance()->log("Starting new round.");
		// Next, we will iterate through all Characters in the initiative queue until it is empty
		while (!_level->isInitiativeQueueEmpty()){
			logRender();
			temp = _level->_initiativeCharacterQueue.top();
			_level->_initiativeCharacterQueue.pop();

			
			// If temp is the player Character, we will allow the user to work with the GUI - otherwise, we will just move the Character
			if (typeid((*temp)) == typeid(Fighter)){
				// GameController Logging
				string message = "It is " + dynamic_cast<Fighter*>(temp)->getName() + "'s turn (AKA it is your turn!)";
				GameController::getInstance()->log(message);
				CharacterController::getInstance()->log(message);

				//CharacterController Logging
				message = dynamic_cast<Fighter*>(temp)->getName() + "'s turn: ";
				CharacterController::getInstance()->log(message);

				// Now run the turn
				destToReturn = runUserTurn();

				message = "End turn.";
				CharacterController::getInstance()->log(message);

				// Check destToReturn Flag. If 2, user wants to quit the game. OR if the Character is dead, we immediately quit
				if (destToReturn < 2 || this->_level->getPlayer()->getIsDead()){
					exit = true;
					goto QUIT_CAMPAIGN;
				}
			}

			// Else, the Character is a Monster. We will make sure that the Monster is not dead. If they are dead, we just skip moving them
			else if (!temp->getIsDead()){
				// We set the currentMovingMonster, which will be used elsewhere in game
				currentMovingMonster = temp;

				// GameController Logging
				string message = "It is " + dynamic_cast<Monster*>(temp)->getName() + "'s turn.";
				GameController::getInstance()->log(message);

				//CharacterController Logging
				//message = "\n" + dynamic_cast<Monster*>(temp)->getName() + "'s turn:";
				message = dynamic_cast<Monster*>(temp)->getName() + "'s turn:";
				CharacterController::getInstance()->log(message);

				temp->move(_level, &_currentGrid, this);

				//CharacterController Logging - Log end turn
				message = "End turn. Click to continue.";
				CharacterController::getInstance()->log(message);
			
					/*while (SDL_WaitEvent(&keyevent) >= 0)  //Poll our SDL key event for any keystrokes.
					{
						switch (keyevent.type){
						case SDL_MOUSEBUTTONDOWN:
							//goto BACK_TO_GAME;
							break;
						}
					}*/
				
				currentMovingMonster = NULL;
			}
		}

		// Log end of round
		GameController::getInstance()->log("End of round.");
		// Now, we will check if any Monsters are dead. If they are, they will be removed from the map
		for (int i = 0; i < _enemies.size(); i++){
			// Check HP. if 0, remove from the vector. Will have already been removed from the Map by its observer, so don't
			// need to update the vectors
			if (_enemies.at(i)->getIsDead()){
				// Log removing dead Monster
				GameController::getInstance()->log("Removing dead Monster from game."); 

				Monster *temp = _enemies.at(i); // Get temp holder
				_enemies.erase(_enemies.begin() + i); // Remove from list
				_level->_enemisOnMap.erase(_level->_enemisOnMap.begin() + i);
				delete temp; // Deallocate memory!
			}
		}
	}
QUIT_CAMPAIGN:
	if (this->_level->getPlayer()->getIsDead() == true)
	{
		this->_level->getLevelWindow()->hideWindow();
		system("cls");
		std::cout << "You Died!!\nPractice some more and try again!!\n";
		system("pause");
	}

	return destToReturn;
}

//return 0 for program exit
//return 2 for successfule turn completion
//return 1 will figure it out
int GamePlayEngine::runUserTurn(){
	int turnCounter = 2;
	//error check for level attachment
	if (this->_level == nullptr)
	{
		std::cout << "Error, attempting run gameplay engine without attaching a map, exting program\n";
		getch();
		exit(-1);
	}
	bool exit = false;
	int mouse_X;
	int mouse_Y;
	int buttonindex;

	//while (exit == false && turnCounter > 0)
	while (this->_endPlayerTurn == false && !this->_level->getPlayer()->getIsDead())
	{
		while (SDL_PollEvent(this->_event) != 0)
		{
			//first check for a right button if so ensure that player select becomes false.
			if ((_event->type == SDL_MOUSEBUTTONDOWN) && (_event->button.button == SDL_BUTTON_RIGHT))
			{
				this->_moveSelect = false;
				this->_interactSelect = false;
				this->_attackSelect = false;
				this->_buttonSelect = false;
				if (this->_currentButtonIndex >= 0)
					this->_level->getLevelWindow()->changeButtonColor(this->_currentButtonIndex, 255, 0, 0);
			}

			//check if end map has been reached
			if (this->_mapExit == true)
			{
				system("cls");
				this->_level->getLevelWindow()->hideWindow();
				std::cout << "CONGRATS!!! Map has been completed.\n\n";
				std::cout << this->_level->getPlayer()->getName() << " has leveled up!!" << endl;
				std::cout << "\n\nPress any key to see " << this->_level->getPlayer()->getName() << "'s new stats.\n";
				_getch();
				this->_level->getPlayer()->forceLevelIncrease();
				this->_level->getPlayer()->displayStats();
				system("cls");
				//std::cout << "\n\nPress any key to continue\n";
				//_getch();
				return 0;
			}

			//if move select is true all move function, decrease turncounter after successful move
			if (this->_moveSelect == true){
				//if (movePlayer())
				if (turnCounter>0 && movePlayer())
				{
					logRender();
					cout << "I moved!";
					turnCounter--;
					cout << turnCounter << endl;
				}
			}

			//if interact select is true and run container interact logic
			if (this->_interactSelect == true)
				interactEnvironment();

			//if attack select is true then run attack logic, decrease turncounter after successful move
			if (this->_attackSelect == true)
				if (turnCounter > 0 && attackEnemy())
				{
					logRender();
					turnCounter--;
				}

			//if game log is true, then run game log driver
			if (this->_gameLog == true)
			{
				this->_level->getLevelWindow()->hideWindow();
				//system("cls");
				//Add here
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

					} while (exit==false);
				
				}
				else if (destination == _ReturnToGame_)
				{
					this->_gameLog = false;
				}

				//End here
				this->_level->getLevelWindow()->unHideWindow();
				menu->getMenuWindow()->hideWindow();
				delete menu;
				menu = nullptr;
				delete engine;
				engine = nullptr;
				this->_gameLog = false;
				this->_buttonSelect = false;
				this->_level->getLevelWindow()->unHideWindow();
			}

			//get current mouse coordinates
			SDL_GetMouseState(&mouse_X, &mouse_Y);

			//check if on gameplay grids
			if ((mouse_X < (this->_level->getLevelWindow()->getGamePlay_X_Grids() * this->_level->getLevelWindow()->getGridX_Length())) &&
				(mouse_Y < (this->_level->getLevelWindow()->getGamePlay_Y_Grids() * this->_level->getLevelWindow()->getGridY_Length())))
			{
				//onGameplayGrids();
			}

			//Index 7 is quit
			//index 6 is gamelog
			//index 5 is end turn
			//other wise prolly on right hand menu
			else
			{
				if (this->_buttonSelect == false)
				{
					buttonindex = onRIghtHandMenu();
					this->_currentButtonIndex = buttonindex;
					//first check for exit
					if (buttonindex == 7)
					{
						exit = true;
						return 1;
					}

					if (buttonindex == 0)
					{
						this->_buttonSelect = false;
						system("cls");
						this->_level->getLevelWindow()->hideWindow();
						//!!!!!!!!!!!!!!!!!!!!
						// DISPLAY CHARACTER STATS AND INVENTORY HERE
						//!!!!!!!!!!!!!!!!!!!!
						this->_level->getPlayer()->displayStats();
					
						system("cls");
						this->_level->getLevelWindow()->unHideWindow();
					}

					if (buttonindex == 1)
					{
						this->_moveSelect = true;
					}

					if (buttonindex == 2)
					{
						this->_interactSelect = true;
					}

					if (buttonindex == 3)
					{
						this->_attackSelect = true;
					}

					if (buttonindex == 4)
					{
						this->_buttonSelect = false;
						this->_level->getLevelWindow()->hideWindow();
						CharacterSaveManager::saveCharacter(this->_level->getPlayer(), *this->_event);
						this->_level->getLevelWindow()->unHideWindow();
					}

					//this means end turn button was clicked
					if (buttonindex == 5)
					{
						this->_endPlayerTurn = true;
					}

					//this means game log button was clicked logic is above in this function
					if (buttonindex == 6)
					{
						this->_gameLog = true;
					}
				}
			}
		}//inner while end
	}

	//ensure player end turn button and button select is made false
	//also player end button has to be rendered back to default color before rendering
	this->_endPlayerTurn = false;
	this->_buttonSelect = false;
	if (this->_currentButtonIndex >= 0)
		this->_level->getLevelWindow()->changeButtonColor(this->_currentButtonIndex, 255, 0, 0);
	return 2;
}

/*!
*renders map and character log at bottom
*/
void GamePlayEngine::logRender()
{
	//render map log on the left
	int y = this->_level->_loggerYend + 5;
	int x = 5;

	SDL_Rect temp;
	temp.y = y;
	temp.x = x;
	temp.h = (this->_level->getLevelWindow()->getWindowHeight() - y) / 10;
	temp.w = this->_level->getLevelWindow()->getWindowWidth() / 2 - 5;

	SDL_Rect temp2;
	temp2.y = y;
	temp2.x = temp.x + this->_level->getLevelWindow()->getWindowWidth() / 2;
	temp2.h = ((this->_level->getLevelWindow()->getWindowHeight() - y) / 10);
	temp2.w = (this->_level->getLevelWindow()->getWindowWidth() / 2 - 5) / 2;


	SDL_SetRenderDrawColor(this->_level->getLevelWindow()->getRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(this->_level->getLevelWindow()->getRenderer(), &this->maplogger);
	SDL_RenderFillRect(this->_level->getLevelWindow()->getRenderer(), &this->charlogger);
	//for clearing the logger part
	this->_level->getLevelWindow()->clearTextLabels();

	std::vector<std::string> local = SingletonInputOutputManager::getInstance()->getlast10(MapController::getInstance()->getPath());
	std::vector<std::string> local2 = SingletonInputOutputManager::getInstance()->getlast10(CharacterController::getInstance()->getPath());
	this->_level->getLevelWindow()->clearTextLabels();
	
	for (int h = 0; h < 10; h++)
	{
		if (local.size() > h)
		{
			if (local[h].length() > 0)
			{
				temp.w = Menus::textWidthCalculator2(local[h], "hello world", ((this->_level->getLevelWindow()->getWindowWidth()/2)*0.15));
				temp.x = maplogger.x + maplogger.w / 2 - temp.w / 2;
				this->_level->getLevelWindow()->addTextLabel(local[h], 255, 165, 0, temp);
				temp.y = temp.h + temp.y;
			}
		}

		//render the character part
		if (local2.size() > h)
		{
			if (local2[h].length() > 0)
			{
				temp2.w = Menus::textWidthCalculator2(local2[h], "hello world", ((this->_level->getLevelWindow()->getWindowWidth() / 2)*0.15));
				temp2.x = charlogger.x + charlogger.w / 2 - temp2.w / 2;
				this->_level->getLevelWindow()->addTextLabel(local2[h], 0, 255, 0, temp2);
				temp2.y = temp2.h + temp2.y;
			}
		}
	}
	this->_level->getLevelWindow()->setMenuOnRenderer();

}


/*!
*function used when player wants to interact with container on environment
*/
void GamePlayEngine::interactEnvironment()
{
	bool interact;
	int mouseIndex;
	int contGridX;
	int contGridY;
	int mouseX;
	int mouseY;
	this->_containers = _level->getContainersOnMap();
	this->_currentGrid = checkMousePosition(this->_level->getGameplayGridsRects(), &mouseIndex);
	int charIndex = _currentGrid.x / this->_level->getLevelWindow()->getGridX_Length();
	int vectorIndex = _currentGrid.y / this->_level->getLevelWindow()->getGridY_Length();
	// update the container list in case any enemies have died
	this->_containers = this->_level->getContainersOnMap();

	for (int x = 0; x < this->_containers.size(); x++)
	{
		interact = this->_level->getPlayer()->validateMapComponentWithinRange(this->_containers[x]->stringIndex, this->_containers[x]->charIndex);
		if (interact == true)
		{
			contGridX = this->_containers[x]->charIndex * this->_level->getLevelWindow()->getGridX_Length();
			contGridY = this->_containers[x]->stringIndex * this->_level->getLevelWindow()->getGridY_Length();
			SDL_GetMouseState(&mouseX, &mouseY);
			if ((mouseX >= contGridX) && (mouseX <= contGridX + this->_level->getLevelWindow()->getGridX_Length()) &&
				(mouseY >= contGridY) && (mouseY <= contGridY + this->_level->getLevelWindow()->getGridY_Length()))
			{
				if ((_event->type == SDL_MOUSEBUTTONUP) && (_event->button.button == SDL_BUTTON_LEFT))
				{
					this->_level->getLevelWindow()->hideWindow();
					system("cls");
					this->_level->getPlayer()->interactWithContainer(this->_containers[x]->container);
					this->_level->getLevelWindow()->unHideWindow();
					if (this->_containers[x]->container->getNumContents() == 0) {
						this->_level->removeContainerOnMap(x);
						this->_containers = this->_level->getContainersOnMap();
					}
					system("cls");
					
					return;
				}
			}
		}
	}	
}

/*!
*funtion used when player wants to engage in combat with an enemy
*/
bool GamePlayEngine::attackEnemy()
{
	bool attack;
	int mouseIndex;
	int enGridX;
	int enGridY;
	int mouseX;
	int mouseY;
	this->_currentGrid = checkMousePosition(this->_level->getGameplayGridsRects(), &mouseIndex);
	int charIndex = _currentGrid.x / this->_level->getLevelWindow()->getGridX_Length();
	int vectorIndex = _currentGrid.y / this->_level->getLevelWindow()->getGridY_Length();
	for (int x = 0; x < this->_enemies.size(); x++)
	{
		attack = this->_level->getPlayer()->validateMapComponentWithinRange(this->_enemies[x]->getVectPos(), this->_enemies[x]->getCharPos());
		if (attack == true)
		{
			enGridX = this->_enemies[x]->getCharPos() * this->_level->getLevelWindow()->getGridX_Length();
			enGridY = this->_enemies[x]->getVectPos() * this->_level->getLevelWindow()->getGridY_Length();
			SDL_GetMouseState(&mouseX, &mouseY);
			if ((mouseX >= enGridX) && (mouseX <= enGridX + this->_level->getLevelWindow()->getGridX_Length()) &&
				(mouseY >= enGridY) && (mouseY <= enGridY + this->_level->getLevelWindow()->getGridY_Length()))
			{
				if ((_event->type == SDL_MOUSEBUTTONUP) && (_event->button.button == SDL_BUTTON_LEFT))
				{
					system("cls");
					this->_level->getPlayer()->attack(this->_enemies[x]);
					this->_enemies[x]->Notify();
					return true;
				}
			}
		}
	}
	return false;
}

/*!
*function used to move player
*/
bool GamePlayEngine::movePlayer()
{
	return this->_level->getPlayer()->move(this->_level, &this->_currentGrid, this);
}

/*!
*function used to run the menu on right hand side
*/
int GamePlayEngine::onRIghtHandMenu()
{
	//first check which button I am on
	int x_cor, y_cor;
	SDL_GetMouseState(&x_cor, &y_cor);
	int index = _level->getLevelWindow()->getButtonIndexThatMouseIsOn(x_cor, y_cor);

	if (index < 0)
	{
		if (_lastButtonIndex != -1)
			_level->getLevelWindow()->changeButtonColor(_lastButtonIndex, 255, 0, 0);
		_lastButtonIndex = index;
	}
	//now if on a valid new button render new color and check for input and return corresponding index
	else
	{
		if (index != _lastButtonIndex)
		{
			_level->getLevelWindow()->changeButtonColor(index, 0, 255, 0);

			if (_lastButtonIndex != -1)
				_level->getLevelWindow()->changeButtonColor(_lastButtonIndex, 255, 0, 0);
			_lastButtonIndex = index;
		}
	}

	if ((_event->type == SDL_MOUSEBUTTONUP) && (_event->button.button == SDL_BUTTON_LEFT) && (index >= 0))
	{
		this->_buttonSelect = true;
		return index;
	}
		
	return -1;
}

/*!
*function returns a rectangle grid on map based on current mouse position on window
*/
SDL_Rect GamePlayEngine::checkMousePosition(std::vector<SDL_Rect> components, int* targetIndex)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (int z = 0; z<components.size(); z++)
	{
		if ((x >= components[z].x) && (x <= components[z].x + components[z].w)
			&& (y >= components[z].y) && (y <= components[z].y + components[z].h))
		{
			*targetIndex = z;
			return components[z];
		}
	}
	SDL_Rect d;
	d.x = -5;
	d.y = -5;
	d.h = -5;
	d.w = -5;
	return d;
}
