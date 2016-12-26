/**
*@file sdl_initialize.h
*@brief Provides access to SDLSetup class
*/
#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <iostream>
/*!
*@class SDLSetup
*This class is designed to abstract the process of initializing
*sdl functionalities for the game
*/
class SDLSetup
{
public:
	void SDL_Initialize();
	void SDL_TTF_Initialize();
	void SDL_Sound_Initialize();
	void SDL_Initialize_PNG_Loading();
	void SDL_Initialize_All_Functionalities();
};