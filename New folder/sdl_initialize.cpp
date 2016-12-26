//!@file sdl_initialize.cpp
//!@brief Provides implementation of SDLSetup members
#include "sdl_initialize.h"

//!initializes general SDL functionalities
void SDLSetup::SDL_Initialize()
{
if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
{
	std::cout<<"Failed to initialize SDL: "<<SDL_GetError()<<std::endl;
	system("pause");
	exit(-1);
}
std::cout<<"SDL successfully initialized."<<std::endl;
}

//!initializes SDL text functionalities
void SDLSetup::SDL_TTF_Initialize()
{
if(TTF_Init() != 0)
{
	std::cout<<"Failed to initialize TTF: "<<SDL_GetError()<<std::endl;
	system("pause");
	exit(-1);
}
std::cout<<"SDL TTF successfully initialized."<<std::endl;
}

//!initializes SDL sound functionalities
void SDLSetup::SDL_Sound_Initialize()
{
if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0)
{
	std::cout<<"Failed to initialize SDL sound systems: "<<SDL_GetError()<<std::endl;
	system("pause");
	exit(-1);
}
std::cout<<"SDL sound systems successfully initialized."<<std::endl;
}

//!initialize PNG image loading functionalities
void SDLSetup::SDL_Initialize_PNG_Loading()
{
if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
{
	std::cout<<"Failed to initialize PNG loading: "<<SDL_GetError()<<std::endl;
	system("pause");
	exit(-1);
}
std::cout<<"PNG loading successfully initialized."<<std::endl;
}

//!initialize all SDL functionalities
void SDLSetup::SDL_Initialize_All_Functionalities()
{
	SDL_Initialize();
	SDL_TTF_Initialize();
	SDL_Sound_Initialize();
	SDL_Initialize_PNG_Loading();
}