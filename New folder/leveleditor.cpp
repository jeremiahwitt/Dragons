#include "leveleditor.h"

//!parameterized constructor that sets the level window and theme for environment components
LevelEditor::LevelEditor(LevelWindow* window, int themeIndex) 
{
	this->_themeIndex = themeIndex;
	this->_level_window = window;

	_tempText.push_back(nullptr);
	_tempText.push_back(nullptr);

	SDL_Rect dest;
	dest.h = window->getGridY_Length();
	dest.w = window->getGridX_Length();
	dest.x = 0;
	dest.y = 0;

	//for(int y=0; y<window->getNumberOfGrids_Y(); y++)
	for(int y=0; y<window->getGamePlay_Y_Grids(); y++)
	{
		dest.y = y * window->getGridY_Length();
		//for(int x=0; x<=window->getNumberOfGrids_X(); x++)
		for(int x=0; x<=window->getGamePlay_X_Grids(); x++)
		{
			dest.x = x * window->getGridX_Length();
			this->addRectToGamePlayGrids(dest);
		}
	}
}

//!accessor for theme index
int LevelEditor::getThemeIndex() const
{
	return this->_themeIndex;
}

//!accessor for map text vector
std::vector<std::string> LevelEditor::getLevelMapVector() const
{
	return this->_level;
}

//!set components from a prebuilt level
void LevelEditor::takeComponentsFromPreBuiltLevel(PreBuiltLevel* pbLevel)
{
	if(pbLevel == nullptr)
	{
		std::cout<<"Could not load prebuilt map for editing. \n";
		exit(-1);
	}
	//set theme index to -1 so that we know that the setup was not new
	this->_themeIndex = -1;

	this->_environmentComponentPath = pbLevel->getEnvironmentComponentsPath();
	this->_directory_path_for_level_file_text_file = pbLevel->getDirectoryPathForLevelTextFile();
	this->_playerPath = pbLevel->getPlayerPath();
	this->_enemyPath = pbLevel->getEnemyPath();
	this->_friendPath = pbLevel->getFriendPath();
	this->_basicContainerPath = SingletonFilePathAndFolderManager::getInstance()->_path_to_basic_container;
	this->_level = pbLevel->getBuiltLevelFile();
}

//!sets up image an text components for the level on the target window renderer
void LevelEditor::createLevelForTargetWindow()
{
	//first open input output and ensure the component path is correct
	//if _themeIndex is -1, it means component path was already set, no need to load again
	if(_themeIndex != -1)
	{
		std::string comppath = SingletonFilePathAndFolderManager::getInstance()->getComponentPathForIndex(_themeIndex);
		this->_environmentComponentPath = comppath;
	}
	this->_environmentComponentNames = SingletonInputOutputManager::getInstance()->readFileLineByLine(this->_environmentComponentPath + SingletonFilePathAndFolderManager::getInstance()->getNameofFileContainingAssetNames());

	//first call parents method to render the basics. The basics include rendering container, enemy and player
	Level::createLevelForTargetWindow();

	//now split the bottom rectangles for environment, items, player/enemies
	//the math is there is five extra grids bottom, and 5 extra grids on sides.
	//the minimum is 10 X 10 and maximum is 50 X 50
	//50% horizontal for environment, 30% horizontal for items, balance horizontal for enemy and player

	//draw vertical lines down at bottom rectangle for splits as mentioned above
	SDL_SetRenderDrawColor(this->_level_window->getRenderer(), 0, 255, 0, 0);
	int y = (this->_level_window->getGamePlay_Y_Grids() * this->_level_window->getGridY_Length()) + 1;
	int x;
	this->_bottom_Y_start = y;

	//draw line for environment rectagle
	if((this->_level_window->getGamePlay_X_Grids()%2) == 0)
	{
		x = ((this->_level_window->getGamePlay_X_Grids())*(this->_level_window->getGridX_Length()))/1.2;
	}
	else
	{
		x = ((this->_level_window->getGamePlay_X_Grids())*(this->_level_window->getGridX_Length()))/1.2 + 1;
	}

	this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart = x;
	for(int a=this->_bottom_Y_start; a<=_level_window->getWindowHeight(); a++)
		SDL_RenderDrawPoint(this->_level_window->getRenderer(), this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart, a);

	//draw line for items rectangle
	//math is from whatever is remaining after the environment split, give 35% to items
	int balance = (this->_level_window->getGamePlay_X_Grids())*(this->_level_window->getGridX_Length()) - this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart;
	balance = (balance / 100.00) * 35;
	this->_X_Cor_ItemPortionEnd_CharacterPortionStart = balance + this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart;

	for(int a=y; a<=_level_window->getWindowHeight(); a++)
		SDL_RenderDrawPoint(this->_level_window->getRenderer(), (this->_X_Cor_ItemPortionEnd_CharacterPortionStart), a);

	this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart = (this->_level_window->getGamePlay_X_Grids())*(this->_level_window->getGridX_Length());
	for (int a = y; a <= _level_window->getWindowHeight(); a++)
		SDL_RenderDrawPoint(this->_level_window->getRenderer(), (this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart), a);

	//formula for y_length; note vertical placed is always 2.
	//divede whatever pixels I have by four, 1 portion for header, 2 portions for placement, and 1 portion for spacing 33%
	_ypixels = this->_level_window->getWindowHeight() - this->_bottom_Y_start;
	_yportion = _ypixels/4;
	//Test Start
	//_y_init = this->_bottom_Y_start + _yportion + ((_yportion/100.00) * 33);
	//Test end
	_y_init = this->_bottom_Y_start + ((_yportion / 100.00) * 33);
	_y_height = _yportion;
	_y_space = ((_yportion/100.00) * 33);

	//create the level component header texts
	//environment rectangle for text
	this->_environmentTextDestination.y = this->_bottom_Y_start + ((this->getLevelWindow()->getWindowHeight() - this->_bottom_Y_start) * 0.05);
	this->_environmentTextDestination.w = this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart * 0.7;
	this->_environmentTextDestination.h = _yportion * 0.9;
	this->_environmentTextDestination.x = (this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart / 2) - (this->_environmentTextDestination.w / 2);

	//items rectangle for text
	this->_itemsTextDestination.y = this->_environmentTextDestination.y;
	this->_itemsTextDestination.w = (this->_X_Cor_ItemPortionEnd_CharacterPortionStart - this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart) * 0.7;
	this->_itemsTextDestination.h = this->_environmentTextDestination.h;
	this->_itemsTextDestination.x = this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart + (((this->_X_Cor_ItemPortionEnd_CharacterPortionStart - this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart) / 2) - (this->_itemsTextDestination.w / 2));

	//character rectangle for text
	this->_characterTextDestination.y = this->_environmentTextDestination.y;
	this->_characterTextDestination.h = this->_environmentTextDestination.h;
	this->_characterTextDestination.w = (this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart - this->_X_Cor_ItemPortionEnd_CharacterPortionStart) * 0.7;
	this->_characterTextDestination.x = this->_X_Cor_ItemPortionEnd_CharacterPortionStart + (((this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart - this->_X_Cor_ItemPortionEnd_CharacterPortionStart)/2) - (this->_characterTextDestination.w / 2));

	//destination for back to main menu button
	this->_backToMainMenu.w = (this->_level_window->getWindowWidth() - (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length())) * 0.7;
	this->_backToMainMenu.h = (this->_level_window->getWindowHeight() - this->_bottom_Y_start) * 0.1;
	this->_backToMainMenu.y = this->_level_window->getWindowHeight() * 0.01;
	this->_backToMainMenu.x = (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()) + ((this->_level_window->getWindowWidth() - (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()))/2) - (this->_backToMainMenu.w/2);

	//destination for instructions
	this->_instructions.w = (this->_level_window->getWindowWidth() - (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length())) * 0.8;
	this->_instructions.h = this->_backToMainMenu.h;
	this->_instructions.y = this->_backToMainMenu.y + this->_backToMainMenu.h + (this->_backToMainMenu.h/2);
	this->_instructions.x = (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()) + ((this->_level_window->getWindowWidth() - (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()))/2) - (this->_instructions.w/2);

	//destination for accept level
	this->_acceptmap.w = this->_instructions.w;
	this->_acceptmap.h = this->_instructions.h;
	this->_acceptmap.y = this->_instructions.y + this->_instructions.h + (this->_instructions.h/2);
	this->_acceptmap.x = (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()) + ((this->_level_window->getWindowWidth() - (this->_level_window->getGamePlay_X_Grids() * this->_level_window->getGridX_Length()))/2) - (this->_acceptmap.w/2);

	//render the menu
	this->getLevelWindow()->setFontType(9);

	this->getLevelWindow()->addButton("Main Menu", 255,0,0, this->_backToMainMenu);
	this->getLevelWindow()->addButton("Instructions",255,0,0, this->_instructions);
	this->getLevelWindow()->addButton("Accept Map",255,0,0, this->_acceptmap);

	this->getLevelWindow()->setTitleFontSize(72);
	this->getLevelWindow()->setMenuOnRenderer();
}

SDL_Rect LevelEditor::getEnemyDestinationAtBottomRect()
{
	return this->_enemyDestinationAtBottom;
}

//!function renders the environment components portions
void LevelEditor::renderEnvironmentAtBottom()
{
	//for each environment component there needs to be 50% pixel sapcing on either side, make the math to
	//(total components * 2) + (50% of one component) divisions horizontally
	int totalspacings;
	int horizontallyplaced;
	//TEST
	/*if((this->_environment_components.size()%2)==0)
		horizontallyplaced = (this->_environment_components.size()/2);
	else
		horizontallyplaced = (this->_environment_components.size()/2) + 1;*/
	//END TEST
	if ((this->_environment_components.size() % 3) == 0)
		horizontallyplaced = (this->_environment_components.size() / 3);
	else if ((this->_environment_components.size() % 3) == 2)
		horizontallyplaced = (this->_environment_components.size() / 3) + 2;
	else if ((this->_environment_components.size() % 3) == 1)
		horizontallyplaced = (this->_environment_components.size() / 3) + 1;


	double unit_horizontal_spaces = ((horizontallyplaced*2) + 1) / 2.0;
	double total_units = (horizontallyplaced * 2) + unit_horizontal_spaces;

	//the following will give as half of real igame width on screen
	int individual_unit_pixel_width = this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart / total_units;
	//formula for x_length = x / (horizontalplaced + 1 + ((horizontalplaced-1)/2))
	//int x_length = this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart / (horizontallyplaced + 1 + ((horizontallyplaced-1)/2));
	int x_length = individual_unit_pixel_width * 2;
	int x_init = x_length/2;
	int x_space = x_length/2;


	SDL_Rect dest;
	dest.x = x_init;
	dest.y = _y_init;
	dest.h = _y_height;
	dest.w = x_length;


	//render the entire environment image vector at the bottom 2 per column
	//iterate the columns
	for(int j=0; j<this->_environment_components.size(); j++)
	{
		//pushback the detination rect
		this->levelComponentRects.push_back(dest);

		
		//TEST
		//render top
		/*if(j%2 == 0)
		{
			this->_level_window->loadTextureOnRenderer(this->_environment_components[j]->getImageDetails()->getImageTexture(), nullptr, &dest);
			dest.y = dest.y + _y_space + dest.h;
		}
		
		//render bottom
		else
		{
			this->_level_window->loadTextureOnRenderer(this->_environment_components[j]->getImageDetails()->getImageTexture(), nullptr, &dest);
			dest.y = _y_init;
			dest.x = dest.x + x_space + dest.w;
		}*/
		//TEST END

		//render top
		if (j % 3 == 0)
		{
			this->_level_window->loadTextureOnRenderer(this->_environment_components[j]->getImageDetails()->getImageTexture(), nullptr, &dest);
			dest.y = dest.y + _y_space + dest.h;
		}

		else if (j % 3 == 1)
		{
			this->_level_window->loadTextureOnRenderer(this->_environment_components[j]->getImageDetails()->getImageTexture(), nullptr, &dest);
			dest.y = dest.y + _y_space + dest.h;
		}

		//render bottom
		else if (j % 3 == 2)
		{
			this->_level_window->loadTextureOnRenderer(this->_environment_components[j]->getImageDetails()->getImageTexture(), nullptr, &dest);
			dest.y = _y_init;
			dest.x = dest.x + x_space + dest.w;
		}
	}

	//render player image
	dest.y = _y_init;
	dest.h = (this->_level_window->getWindowHeight() - dest.y ) * 0.7;
	dest.w = (this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart - this->_X_Cor_ItemPortionEnd_CharacterPortionStart)* 0.23;
	//dest.x = this->_X_Cor_ItemPortionEnd_CharacterPortionStart + ((this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart - this->_X_Cor_ItemPortionEnd_CharacterPortionStart)/2) - dest.w/2;
	dest.x = this->_X_Cor_ItemPortionEnd_CharacterPortionStart + ((this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart - this->_X_Cor_ItemPortionEnd_CharacterPortionStart) * 0.15);
	this->_level_window->loadTextureOnRenderer(this->_player->getImageDetails()->getImageTexture(), nullptr, &dest);
	this->_playerDestinationAtBottom = dest;

	//redner enemy
	dest.x = dest.x + dest.w + dest.w * 0.1;
	this->_level_window->loadTextureOnRenderer(this->_enemy->getImageDetails()->getImageTexture(), nullptr, &dest);
	this->_enemyDestinationAtBottom = dest;

	//redner friend
	dest.x = dest.x + dest.w + dest.w * 0.1;
	this->_level_window->loadTextureOnRenderer(this->_friend->getImageDetails()->getImageTexture(), nullptr, &dest);
	this->_friendDestinationAtBottom = dest;

	//render basic container
	dest.w = (this->_X_Cor_ItemPortionEnd_CharacterPortionStart - this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart) * 0.8;
	dest.x = this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart + ((this->_X_Cor_ItemPortionEnd_CharacterPortionStart - this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart)/2) - dest.w/2;
	this->_level_window->loadTextureOnRenderer(this->_container->getImageDetails()->getImageTexture(), nullptr, &dest);
	this->_basicContainerAtBottom = dest;

	//now use y and x to render the environment text
	//this->getLevelWindow()->setFontType(9);
	//this->getLevelWindow()->addTextLabel("Environment", 255,0,0, this->_environmentTextDestination);
	//this->getLevelWindow()->setTitleFontSize(72);
	this->getLevelWindow()->setMenuOnRenderer();
}

//!this will be implemented later on in the project
void LevelEditor::renderItemsAtBottom()
{
	//first render the text
	//this->getLevelWindow()->setFontType(9);
	//this->getLevelWindow()->addTextLabel("Container", 255,0,0, this->_itemsTextDestination);
	//this->getLevelWindow()->setTitleFontSize(72);
	//this->getLevelWindow()->setMenuOnRenderer();
	this->_level_window->loadTextureOnRenderer(this->_container->getImageDetails()->getImageTexture(), nullptr, &this->_basicContainerAtBottom);
}

//!function renders the character on the bottom
void LevelEditor::renderCharactersAtBottom()
{
	//first render the text
	//this->getLevelWindow()->setFontType(9);
	//this->getLevelWindow()->addTextLabel("Characters", 255,0,0, this->_characterTextDestination);
	//this->getLevelWindow()->setTitleFontSize(72);
	//this->getLevelWindow()->setMenuOnRenderer();

	//render player
	this->_level_window->loadTextureOnRenderer(this->_player->getImageDetails()->getImageTexture(), nullptr, &this->_playerDestinationAtBottom);

	//redner enemy
	this->_level_window->loadTextureOnRenderer(this->_enemy->getImageDetails()->getImageTexture(), nullptr, &this->_enemyDestinationAtBottom);

	//render friend
	this->_level_window->loadTextureOnRenderer(this->_friend->getImageDetails()->getImageTexture(), nullptr, &this->_friendDestinationAtBottom);
}

//!function renders the description of the gamecomponent parameter on the bottom right
void LevelEditor::renderDescriptionAtBottomRIght(GameComponent* component)
{
	if(_tempText.size() == 0)
		return;

	//if nullptr means nothing selected, render black and return
	if(component == nullptr)
	{
		for(int x=0; x<_tempText.size(); x++)
		{
			if(_tempText[x] != nullptr)
			{
				_tempText[x]->setTextColor(0,0,0);
				_tempText[x]->createTextTextureOnTargetWindowRenderer(this->getLevelWindow()->getRenderer());
				this->getLevelWindow()->loadTextureOnRenderer(_tempText[x]->getTextTexture(), nullptr, &_tempText[x]->getTargetOnWindowRectangle());
				this->getLevelWindow()->displayWindow();
			}
		}
		return;
	}

	this->getLevelWindow()->setFontType(9);
	this->getLevelWindow()->setTitleFontSize(250);

	_descriptionRect.x = this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart + ((this->getLevelWindow()->getWindowWidth() - this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart) * 0.1);
	_descriptionRect.y = this->_bottom_Y_start + ((this->getLevelWindow()->getWindowHeight() - this->_bottom_Y_start) * 0.1);
	_descriptionRect.h = (this->getLevelWindow()->getWindowHeight() - this->_bottom_Y_start) * 0.2;
	_descriptionRect.w = (this->getLevelWindow()->getWindowHeight() - this->_bottom_Y_start)-(((this->getLevelWindow()->getWindowWidth() - this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart) * 0.1) * 2);

	//check to see if it is environment
	Environment* env = dynamic_cast<Environment*>(component);
	if(env != nullptr)
	{
		for(int x=0; x<_tempText.size(); x++)
		{
			if(_tempText[x]!=nullptr)
			{
				delete _tempText[x];
				_tempText[x] = nullptr;
			}
			_tempText[x] = new Text();
			_tempText[x]->setFontType(this->getLevelWindow()->getCurrentFontTypePath());
			_tempText[x]->setFontSize(250);
		}

		_tempText[0]->setText(env->getComponentName());
		std::string s = "Obstruction: ";
		if(env->isComponentObstructionToPlayer() == true)
			s = s + "Yes";
		else
			s = s + "No";
		_tempText[1]->setText(s);

		_tempText[0]->setDestinationRectOnTargetWindow(_descriptionRect);

		_descriptionRect.w = _descriptionRect.w + (_descriptionRect.w * 0.3);
		_descriptionRect.y = _descriptionRect.y + _descriptionRect.h + 5;

		_tempText[1]->setDestinationRectOnTargetWindow(_descriptionRect);

		for(int x=0; x<_tempText.size(); x++)
		{
			_tempText[x]->setTextColor(255,0,0);
			_tempText[x]->createTextTextureOnTargetWindowRenderer(this->getLevelWindow()->getRenderer());
			this->getLevelWindow()->loadTextureOnRenderer(_tempText[x]->getTextTexture(), nullptr, &_tempText[x]->getTargetOnWindowRectangle());
		}
		
		this->getLevelWindow()->displayWindow();
		return;
	}

	//check if it is container
	Container* cont = dynamic_cast<Container*>(component);
	if(cont != nullptr)
	{
		//delete all temp text first
		for(int x=0; x<_tempText.size(); x++)
		{
			if(_tempText[x]!=nullptr)
			{
				delete _tempText[x];
				_tempText[x] = nullptr;
			}
		}
		_tempText[0] = new Text();
		_tempText[0]->setFontType(this->getLevelWindow()->getCurrentFontTypePath());
		_tempText[0]->setFontSize(250);
		_tempText[0]->setText(cont->getComponentName());

		_tempText[1] = new Text();
		_tempText[1]->setFontType(this->getLevelWindow()->getCurrentFontTypePath());
		_tempText[1]->setFontSize(250);
		std::string s = "Obstruction: ";
		if(cont->isComponentObstructionToPlayer() == true)
			s = s + "Yes";
		else
			s = s + "No";
		_tempText[1]->setText(s);

		_tempText[0]->setDestinationRectOnTargetWindow(_descriptionRect);

		_descriptionRect.w = _descriptionRect.w + (_descriptionRect.w * 0.3);
		_descriptionRect.y = _descriptionRect.y + _descriptionRect.h + 5;

		_tempText[1]->setDestinationRectOnTargetWindow(_descriptionRect);

		for(int x=0; x<_tempText.size(); x++)
		{
			if(_tempText[x] != nullptr)
			{
				_tempText[x]->setTextColor(255,0,0);
				_tempText[x]->createTextTextureOnTargetWindowRenderer(this->getLevelWindow()->getRenderer());
				this->getLevelWindow()->loadTextureOnRenderer(_tempText[x]->getTextTexture(), nullptr, &_tempText[x]->getTargetOnWindowRectangle());
			}
		}
		this->getLevelWindow()->displayWindow();
		return;
	}


	//try enemy
	Monster* mons = dynamic_cast<Monster*>(component);
	if (mons != nullptr)
	{
		//delete all temp text first
		for (int x = 0; x<_tempText.size(); x++)
		{
			if (_tempText[x] != nullptr)
			{
				delete _tempText[x];
				_tempText[x] = nullptr;
			}
		}
		_tempText[0] = new Text();
		_tempText[0]->setFontType(this->getLevelWindow()->getCurrentFontTypePath());
		_tempText[0]->setFontSize(250);
		_tempText[0]->setText(component->getComponentName());
		_tempText[0]->setDestinationRectOnTargetWindow(_descriptionRect);
		_tempText[0]->setTextColor(255, 0, 0);
		_tempText[0]->createTextTextureOnTargetWindowRenderer(this->getLevelWindow()->getRenderer());
		this->getLevelWindow()->loadTextureOnRenderer(_tempText[0]->getTextTexture(), nullptr, &_tempText[0]->getTargetOnWindowRectangle());

		std::string s = "Obstruction: ";
		if (mons->isComponentObstructionToPlayer() == true)
			s = s + "Yes";
		else
			s = s + "No";

		_descriptionRect.w = _descriptionRect.w + (_descriptionRect.w * 0.3);
		_descriptionRect.y = _descriptionRect.y + _descriptionRect.h + 5;

		_tempText[1] = new Text();
		_tempText[1]->setFontType(this->getLevelWindow()->getCurrentFontTypePath());
		_tempText[1]->setFontSize(250);
		_tempText[1]->setText(s);
		_tempText[1]->setTextColor(255, 0, 0);
		_tempText[1]->setDestinationRectOnTargetWindow(_descriptionRect);
		_tempText[1]->createTextTextureOnTargetWindowRenderer(this->getLevelWindow()->getRenderer());
		this->getLevelWindow()->loadTextureOnRenderer(_tempText[1]->getTextTexture(), nullptr, &_tempText[1]->getTargetOnWindowRectangle());
		return;
	}

	//if it is not environment and container then it is parent gamecomponent so player
	for(int x=0; x<_tempText.size(); x++)
	{
		if(_tempText[x]!=nullptr)
		{
			delete _tempText[x];
			_tempText[x] = nullptr;
		}
	}
	_tempText[0] = new Text();
	_tempText[0]->setFontType(this->getLevelWindow()->getCurrentFontTypePath());
	_tempText[0]->setFontSize(250);
	_tempText[0]->setText(component->getComponentName());
	_tempText[0]->setDestinationRectOnTargetWindow(_descriptionRect);
	_tempText[0]->setTextColor(255,0,0);
	_tempText[0]->createTextTextureOnTargetWindowRenderer(this->getLevelWindow()->getRenderer());
	this->getLevelWindow()->loadTextureOnRenderer(_tempText[0]->getTextTexture(), nullptr, &_tempText[0]->getTargetOnWindowRectangle());
	this->getLevelWindow()->displayWindow();
	delete _tempText[0];
	_tempText[0] = nullptr;
	
}

//!access the destination rectangle on which player is rendered at the bottom
SDL_Rect LevelEditor::getPlayerDestinationAtBottomRect()
{
	return this->_playerDestinationAtBottom;
}

//!access friend destination at bottom
SDL_Rect LevelEditor::getFriendDestinationAtBottomRect()
{
	return this->_friendDestinationAtBottom;
}

SDL_Rect LevelEditor::getContainerDestinationAtBottomRect()
{
	return this->_basicContainerAtBottom;
}

//!render all portions that are not part of the main gameplay grids
void LevelEditor::renderAllNonGameplayGridPortions()
{
	renderEnvironmentAtBottom();
	renderItemsAtBottom();
	renderCharactersAtBottom();
	renderDescriptionAtBottomRIght(nullptr);
}

//!setter for the environment component image paths
void LevelEditor::setEnvironmentTextVector(std::vector<std::string> environmentVector)
{
	this->_level = environmentVector;
}

//!level text vector accessor
std::vector<std::string> LevelEditor::getEnvironmentTextVector()
{
	return this->_level;
}

//!accessor for the Y coordinate from which gameplay grids end
int LevelEditor::get_Y_start()
{
	return this->_bottom_Y_start;
}

//!accessor for the rectangles of the level components
std::vector<SDL_Rect> LevelEditor::getLevelComponentRects()
{
	return this->levelComponentRects;
}

//!X coordinate accessor for where the environment portion ends
int LevelEditor::getEnvironmentPortionEnd_X_Xor()
{
	return this->_X_Cor_EnvironmentPortionEnd_ItemPortionStart;
}

//!X coordinate accessor for where the items portion end
int LevelEditor::getItemPortionEnd_X_Cor()
{
	return this->_X_Cor_ItemPortionEnd_CharacterPortionStart;
}

//!X coordinate accessor from where the player portion ends
int LevelEditor::getCharacterPortionEnd_X_Cor()
{
	return this->_X_Cor_CharacterPortionEnd_DescriptionPortionStart;
}

//!saves level based on the path passed
void LevelEditor::saveLevel(std::string levelpath)
{
	//saving
	for (int x = 0; x < this->_level.size(); x++)
	{
		std::cout << this->_level[x] << std::endl;
	}
	cout<<std::endl;
	SingletonFilePathAndFolderManager::getInstance()->saveUserCreatedLevel(this->_level, this->_environmentComponentPath, levelpath);
}

//!destroys all dynamically allocated memory
LevelEditor::~LevelEditor()
{
	for(int x=0; x< _tempText.size(); x++)
	{
		if(_tempText[x]!= nullptr)
		{
			delete _tempText[x];
			_tempText[x] = nullptr;
		}
	}
}