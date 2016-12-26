/**
*@file levelwindow.h
*@brief  Provides ability to acces LevelWindow class
*/

#pragma once
#include "windows.h"
#include "textbasedwindow.h"
#include "namespaces.h"
using namespace WindowHeightWidthDivideAspect;

/*!
*@class LevelWindow
*Derives further from textbased window class and adds in grid like functionalities
*/
class LevelWindow : public TextBasedWindow
{
private:
	int _grid_X_length;
	int _grid_Y_length;
	int _X_grids_for_gameplay;
	int _Y_grids_for_gameplay;

public:
	LevelWindow(const char* title, int num_of_horizontal_grids, int num_of_vertical_grids);
	int getGridX_Length();
	int getGridY_Length();
	int getGamePlay_X_Grids();
	int getGamePlay_Y_Grids();
	~LevelWindow();
};