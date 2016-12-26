#include "levelwindow.h"

//!constructor creates the window 
//!number of gameplay grids is 85% of window width and 80% of window height
LevelWindow::LevelWindow(const char* title, int num_of_horizontal_grids, int num_of_vertical_grids)
{
	//set private pointers to null poniters and assign the title
	_window_title = title;
	_window = nullptr;
	_renderer = nullptr;
	_red = 0;
	_green = 0;
	_blue = 100;

	//check for number of grids validity
	if(num_of_horizontal_grids < 1 || num_of_vertical_grids < 1)
	{
		std::cout<<"Attempted grid dimension is too low, failed to create window. Exiting program."<<std::endl;
		system("pause");
		exit(-1);
	}

	_X_grids_for_gameplay = num_of_horizontal_grids;
	_Y_grids_for_gameplay = num_of_vertical_grids;

	//setup window height and width based on monitor height and width
	SDL_DisplayMode monitor;
	if(SDL_GetCurrentDisplayMode(0, &monitor) != 0)
	{
		std::cout<<"Failed to create an SDL window."<<std::endl;
		system("pause");
		exit(-1);
	}
	
	_X_grids_for_gameplay = num_of_horizontal_grids;
	_Y_grids_for_gameplay = num_of_vertical_grids;

	//set window height and width based on monitor
	_window_height = ((int)((float)(monitor.h)/_WindowHeightDivideAspect_));
	_window_width = ((int)((float)(monitor.w)/_WindowWidthDivideAspect_));
	_grid_X_length = (this->getWindowWidth()*(0.85)) / _X_grids_for_gameplay;
	_grid_Y_length = (this->getWindowHeight()*(0.80)) / _Y_grids_for_gameplay;


	//now initialize the window
	_window = SDL_CreateWindow(_window_title, 30,30, _window_width, _window_height, SDL_WINDOW_SHOWN);

	//initialize window renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(_renderer == nullptr)
	{
		std::cout<<"Failed to create renderer for window: "<<SDL_GetError()<<std::endl;
		system("pause");
		exit(-1);
	}
}

//!get length of grid width
int LevelWindow::getGridX_Length()
{
	return _grid_X_length;
}

//!get length of grid height
int LevelWindow::getGridY_Length()
{
	return _grid_Y_length;
}

//!get total number of gameplay grids horizontally
int LevelWindow::getGamePlay_X_Grids()
{
	return _X_grids_for_gameplay;
}

//!get total number of gameplay grids vertically
int LevelWindow::getGamePlay_Y_Grids()
{
	return _Y_grids_for_gameplay;
}

//!destroy the window
LevelWindow::~LevelWindow()
{
	destroyWindow();
}