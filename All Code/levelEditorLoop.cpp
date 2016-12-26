/*#include "game_loops.h"

int GameLoops::levelEditorLoop()
{
	std::string title = "test";
	int totalhorizontalGameGrids = 25;
	int totalVerticalGameGrids = 15;
	LevelWindow* window = new LevelWindow(title.c_str(), totalhorizontalGameGrids, totalVerticalGameGrids);
	window->displayWindow();
	//std::cout<<"grid width: "<<window->getWindowWidth()/window->getNumberOfGrids_X();
	//std::cout<<"grid height: "<<window->getWindowHeight()/window->getNumberOfGrids_Y();
	int destinationInt =-1;
	window->displayWindow();

	// next put the options at the bottom
	LevelEditor* level = new LevelEditor(window,1);
	level->createLevelForTargetWindow();
	level->renderAllNonGameplayGridPortions();
	level->getLevelWindow()->displayWindow();
	//put options at the right

	//run the loop till valid level is created
	SDL_SetRenderDrawBlendMode(window->getRenderer(), SDL_BLENDMODE_BLEND);
	std::vector<SDL_Rect> components;
	std::vector<Environment*> envcomponents = level->getEnvironmentComponents();
	std::vector<std::string> templevel;
	

	for(int y=0; y<window->getGamePlay_Y_Grids(); y++)
	{
		templevel.push_back("");
		for(int x=0; x<window->getGamePlay_X_Grids(); x++)
			templevel[y] = templevel[y] + "."; 
	}

	std::vector<SDL_Rect> playerdest;
	playerdest.push_back(level->getPlayerDestinationAtBottomRect());
	MapEditorEngine m = MapEditorEngine(envcomponents, templevel, components, playerdest, level->getPlayerComponent());
	//test end
	while(m.quit==false)
	{
		while(SDL_PollEvent(&_event) != 0)
		{
			SDL_GetMouseState(&this->mouse_X_cor, &this->mouse_Y_cor);

			//this is to ensure if left mouse button was clicked in gameplay grid and released elsewhere,
			//then when the mouse is taken back to gameplay grid nothing renders
			if(m.renderingOnGameplayGrids == true && (_event.type==SDL_MOUSEBUTTONUP))
				m.renderingOnGameplayGrids = false;

			//quit if user presses red on top right
			if(_event.type == SDL_QUIT)
			{
				m.quit = true;
				destinationInt = -1;
			}

			//for right button click target selected is false all parameters get reset
			if((_event.type == SDL_MOUSEBUTTONUP)&&(_event.button.button == SDL_BUTTON_RIGHT) && (m.targetselected == true))
			{
				m.targetselected = false;
				m.targetisplayer = false;
				m.targetTexture = nullptr;
				m.ontargetfirsttime = false;
				level->renderAllNonGameplayGridPortions();
				window->displayWindow();
			}

			//for gameplaygrid alphablend on select grids NOTE the -1 as are to give a 1pixel line buffer between the gameplay grid rectangle and rest of the window
			if((mouse_Y_cor<=(((window->getGamePlay_Y_Grids())*window->getGridY_Length()-1))) && (mouse_X_cor<=(((window->getGamePlay_X_Grids())*window->getGridX_Length())-1)))
			{
				m.onGameplayGrids(level->getLevelWindow(), level, &_event); 
			}

			//check if mouse is in bottom grid section only if a target is not selected
			else if((mouse_Y_cor>(window->getGamePlay_Y_Grids())*window->getGridY_Length()) && (m.targetselected == false))
			{
				//check if mouse is on environment grid
				if(mouse_X_cor < level->getEnvironmentPortionEnd_X_Xor())
					m.onEnvironmentGrid(level->getLevelWindow(), level, &_event);

				//check if mouse is on character grid
				else if(mouse_X_cor < level->getCharacterPortionEnd_X_Cor())
				{
					level->renderEnvironmentAtBottom();
					m.onCharacterGrid(level->getLevelWindow(), level, &_event);
				}
			}

			//check is mouse is on right hand menu
			else if(mouse_X_cor > (window->getGamePlay_X_Grids() * window->getGridX_Length()) && (m.targetselected == false))
			{
				destinationInt = m.onRightHandMenuGrid(level, &_event);

				switch(destinationInt)
				{
				case 0:
					destinationInt = -1;
					m.quit = true;
					break;

				case 1:
					break;
				
				case 2:
					if(m.checkEnvironmentValidity() == true)
						m.quit = true;
				}
			}
		}
	}

	//if main menu was quit without a valid level then, the level will not be saved
	if(destinationInt != -1)
	{
		templevel = m.getEnvironmentTextLevel();
		std::cout<<std::endl<<std::endl;
	
		std::ofstream file;
		file.open(_userCreatedLevelPath + _userCreatedLevelFileName);

		for(int x=0; x<templevel.size(); x++)
		{
			file<<templevel[x]<<std::endl;
			std::cout<<templevel[x]<<std::endl;
		}
		file.close();

		//save the level on text file
		level->setEnvironmentTextVector(templevel);
		level->saveLevel(_userCreatedLevelFileName);
	}

		destroyLevel(level);
		level = nullptr;
	
	return destinationInt;
}*/