#include "menuengine.h"

//!parameterized constructor needs to set the menu that the engine needs to run
//!also the SDL event handler that is associated with the main game loop
MenuEngine::MenuEngine(Menus* menu, SDL_Event event_)
{
	this->_menu = menu;
	this->_event = event_;
	this->_currentButtonIndex = -1;
	this->_lastButtonIndex = -1;
	this->_mouse_X_cor = 0;
	this->_mouse_Y_cor = 0;
	rollover = new OneTimeEffect("assets/Sound/Menu/Buttons/rollover.wav");
	click = new OneTimeEffect("assets/Sound/Menu/Buttons/click.wav");
}

//!primary run engine method runs a menu for which only functions are taking a button input and mapping a destination
int MenuEngine::runEngine()
{
	bool onButton = false;
	
	bool quit = false;
	while(quit==false)
	{
		while(SDL_PollEvent(&_event) != 0)
		{
			SDL_GetMouseState(&this->_mouse_X_cor, &this->_mouse_Y_cor);
			
			if(_event.type == SDL_QUIT)
			{
				quit = true;
			}

			//check which button cursor is on
			_currentButtonIndex = _menu->getMenuWindow()->getButtonIndexThatMouseIsOn(this->_mouse_X_cor, this->_mouse_Y_cor);

			//this means I am not at any button, and the last button should be rendered back to old color
			if(_currentButtonIndex < 0)
			{
				onButton = false;
				if(_lastButtonIndex != -1)
				{
					_menu->getMenuWindow()->changeButtonColor(_lastButtonIndex, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
				}
				_lastButtonIndex = _currentButtonIndex;
			}

			//this means I am on a valid button
			if(_currentButtonIndex>=0)
			{
				if (onButton == false)
				{
					onButton = true;
					rollover->play();
				}
				//this means I arrived at a button first time
				if(_currentButtonIndex!=_lastButtonIndex)
				{
					//first render the current button to new color
					_menu->getMenuWindow()->changeButtonColor(_currentButtonIndex, _menu->getAMenuComponentColor(_YesButtonSelect_)->red, _menu->getAMenuComponentColor(_YesButtonSelect_)->green, _menu->getAMenuComponentColor(_YesButtonSelect_)->blue);

					//set last button back to old color make the last button the current button
					if(_lastButtonIndex != -1)
					{
						_menu->getMenuWindow()->changeButtonColor(_lastButtonIndex, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
					}
					_lastButtonIndex = _currentButtonIndex;
				}
				//else I was at this button last frame so no need to change anything
			}

			//if I am at a valid button then I need to get input
			if ((_event.type == SDL_MOUSEBUTTONUP) && (_event.button.button == SDL_BUTTON_LEFT))
			{
				
				if (_currentButtonIndex >= 0)
				{
					quit = true;
					click->play();
					SDL_Delay(200);
					std::cout << "Clicked\n";
				}
			}
		}
	}

	return this->_currentButtonIndex;
}

//!this method was primarily for campaign editor menu
//!added functionality, keeping track of right button click on existing campaigns
//!for deletenig we have to give the name of corresponding button index, otherwise a nullptr has to be returned
int MenuEngine::runEngine(char* buttontracker)
{
	bool onButton = false;
	bool quit = false;
	//buttontracker = nullptr;
	int lowerdeleteindex;
	int upperdeleteindex;

	CampaignMenus* manager;

	//first try dynamic cast of specific
	manager = dynamic_cast<CampaignMapManagers*>(this->_menu);

	//if not successfull then dynamic cast to parent
	if(manager == nullptr)
	{
		manager = dynamic_cast<CampaignManager*>(this->_menu);
	}

	//if not sucessfull try dynamic cast to campaign menus
	if(manager == nullptr)
	{
		manager = dynamic_cast<CampaignMenus*>(this->_menu);
	}


	if(manager == nullptr)
	{
		std::cout<<"Error, could not dynamically cast Menu to Camapaign Mnager, exiting program.\n";
		getch();
		exit(-1);
	}
	manager->checkExistingComponentsIndexRange(&lowerdeleteindex, &upperdeleteindex);
	std::cout<<lowerdeleteindex<<" "<<upperdeleteindex<<std::endl;
	while(quit==false)
	{
		while(SDL_PollEvent(&_event) != 0)
		{
			SDL_GetMouseState(&this->_mouse_X_cor, &this->_mouse_Y_cor);
			
			if(_event.type == SDL_QUIT)
			{
				quit = true;
				buttontracker = nullptr;
				return _ExitToCommandPrompt_;
			}

			//check which button cursor is on
			_currentButtonIndex = _menu->getMenuWindow()->getButtonIndexThatMouseIsOn(this->_mouse_X_cor, this->_mouse_Y_cor);

			//this means I am not at any button, and the last button should be rendered back to old color
			if(_currentButtonIndex < 0)
			{
				onButton = false;
				if(_lastButtonIndex != -1)
				{
					_menu->getMenuWindow()->changeButtonColor(_lastButtonIndex, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
				}
				_lastButtonIndex = _currentButtonIndex;
			}

			//this means I am on a valid button
			if(_currentButtonIndex>=0)
			{
				if (onButton == false)
				{
					onButton = true;
					rollover->play();
				}
				//this means I arrived at a button first time
				if(_currentButtonIndex!=_lastButtonIndex)
				{
					//first render the current button to new color
					_menu->getMenuWindow()->changeButtonColor(_currentButtonIndex, _menu->getAMenuComponentColor(_YesButtonSelect_)->red, _menu->getAMenuComponentColor(_YesButtonSelect_)->green, _menu->getAMenuComponentColor(_YesButtonSelect_)->blue);

					//set last button back to old color make the last button the current button
					if(_lastButtonIndex != -1)
					{
						_menu->getMenuWindow()->changeButtonColor(_lastButtonIndex, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
					}
					_lastButtonIndex = _currentButtonIndex;
				}
				//else I was at this button last frame so no need to change anything
			}

			//if I am at a valid button then I need to get input
			//left button click surely means edit or create new map
			if((_event.type == SDL_MOUSEBUTTONUP)&&(_event.button.button == SDL_BUTTON_LEFT)&&(_currentButtonIndex>=0))
			{
				click->play();
				SDL_Delay(200);
				SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(buttontracker, manager->getNameOfButtonFromIndex(_currentButtonIndex));
				return _currentButtonIndex;
				quit = true;
			}

			//right button click means if I were on an index with already existing campaign name, then i have to delete it, so return with a negative value
			else if((_event.type == SDL_MOUSEBUTTONUP)&&(_event.button.button == SDL_BUTTON_RIGHT)&&(_currentButtonIndex>=lowerdeleteindex)&&(_currentButtonIndex<=upperdeleteindex))
			{
				SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(buttontracker, manager->getNameOfButtonFromIndex(_currentButtonIndex));
				return -1;
			}
		}
	}
	
	return this->_currentButtonIndex;
}

//!this function specially designed for sequence change purpose only
//!the ingore renders are the button indices for which rendering will be ignored
//!and also input will be ignored
int MenuEngine::runEngine(int ignoreRender1, int ignoreRender2, char* buttontracker)
{
	bool onButton = false;
	bool quit = false;
	int lowerdeleteindex;
	int upperdeleteindex;

	CampaignMenus* manager;

	//first try dynamic cast of specific
	manager = dynamic_cast<CampaignMapManagers*>(this->_menu);

	//if not successfull then dynamic cast to parent
	if(manager == nullptr)
	{
		manager = dynamic_cast<CampaignManager*>(this->_menu);
	}

	if(manager == nullptr)
	{
		std::cout<<"Error, could not dynamically cast Menu to Camapaign Mnager, exiting program.\n";
		exit(-1);
	}
	manager->checkExistingComponentsIndexRange(&lowerdeleteindex, &upperdeleteindex);
	while(quit==false)
	{
		while(SDL_PollEvent(&_event) != 0)
		{
			SDL_GetMouseState(&this->_mouse_X_cor, &this->_mouse_Y_cor);
			
			if(_event.type == SDL_QUIT)
			{
				quit = true;
				buttontracker = nullptr;
				return _ExitToCommandPrompt_;
			}

			//check which button cursor is on
			_currentButtonIndex = _menu->getMenuWindow()->getButtonIndexThatMouseIsOn(this->_mouse_X_cor, this->_mouse_Y_cor);
			if ((_currentButtonIndex >= 0))
			{
				rollover->play();
			}
			//this means I am not at any button, and the last button should be rendered back to old color, and if the last button was of the ignore render, then just ignore rendering
			if(_currentButtonIndex < 0)
			{
				
				if((_lastButtonIndex != -1) && (_lastButtonIndex != ignoreRender1) && (_lastButtonIndex != ignoreRender2))
				{
					//std::cout<<_lastButtonIndex<<std::endl;
					_menu->getMenuWindow()->changeButtonColor(_lastButtonIndex, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
				}
				_lastButtonIndex = _currentButtonIndex;
			}

			//this means I am on a valid button
			if(_currentButtonIndex>=0)
			{
				
				//this means I arrived at a button first time
				if(_currentButtonIndex!=_lastButtonIndex)
				{
					//if (onButton == false)
					//{
						//onButton = true;
						
					//}
					//first render the current button to new color ignore the render ones of course
					if((_currentButtonIndex != ignoreRender1) && (_currentButtonIndex != ignoreRender2))
						_menu->getMenuWindow()->changeButtonColor(_currentButtonIndex, _menu->getAMenuComponentColor(_YesButtonSelect_)->red, _menu->getAMenuComponentColor(_YesButtonSelect_)->green, _menu->getAMenuComponentColor(_YesButtonSelect_)->blue);

					//set last button back to old color make the last button the current button, again ignore the renders for the parameters
					if((_lastButtonIndex != -1) && (_lastButtonIndex != ignoreRender1) && (_lastButtonIndex != ignoreRender2))
					{
						_menu->getMenuWindow()->changeButtonColor(_lastButtonIndex, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
					}
					_lastButtonIndex = _currentButtonIndex;
				}
				//else I was at this button last frame so no need to change anything
			}

			//if I am at a valid button then I need to get input
			//left button click surely means edit or create new map again ignore inputs for the parameters passed
			if((_event.type == SDL_MOUSEBUTTONUP)&&(_event.button.button == SDL_BUTTON_LEFT)&&(_currentButtonIndex>=0) && (_currentButtonIndex != ignoreRender1) && (_currentButtonIndex != ignoreRender2) && (_currentButtonIndex <= upperdeleteindex))
			{

				SingletonInputsAndStringManager::getInstance()->assignStringToCharPointer(buttontracker, manager->getNameOfButtonFromIndex(_currentButtonIndex));
				click->play();
				SDL_Delay(200);
				return _currentButtonIndex;
			}

			//right button click means abort the sequence change procedure, so first render the two ignore buttons to old color
			else if((_event.type == SDL_MOUSEBUTTONUP)&&(_event.button.button == SDL_BUTTON_RIGHT))
			{
				if(_lastButtonIndex > -1)
					_menu->getMenuWindow()->changeButtonColor(_lastButtonIndex, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
				if(ignoreRender1 != -1)
					_menu->getMenuWindow()->changeButtonColor(ignoreRender1, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
				if(ignoreRender2 != -1)
					_menu->getMenuWindow()->changeButtonColor(ignoreRender2, _menu->getAMenuComponentColor(_NoButtonSelect_)->red, _menu->getAMenuComponentColor(_NoButtonSelect_)->green, _menu->getAMenuComponentColor(_NoButtonSelect_)->blue);
				return -1;
			}
		}
	}
	
	return this->_currentButtonIndex;
}

//!destructor does not destroy anything, just sets the menu to nullptr since it will be destroyed from the main game loop
MenuEngine::~MenuEngine()
{
	this->_menu = nullptr;
	if (this->click != nullptr)
	{
		delete click;
		click = nullptr;
	}
	if (this->rollover != nullptr)
	{
		delete rollover;
		rollover = nullptr;
	}
}