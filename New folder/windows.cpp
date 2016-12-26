//!@file Windows.cpp
#include "windows.h"

SDLWindow::SDLWindow()
{
}

//!constructor creates the window 
SDLWindow::SDLWindow(const char* title, int windowHeight, int windowWidth)
{
	//set private pointers to null poniters and assign the title
	_window_title = title;
	_window_width = windowWidth;
	_window_height = windowHeight;
	_window = nullptr;
	_renderer = nullptr;
	_red = 0;
	_green = 0;
	_blue = 100;

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
	std::cout<<"Window renderer successfully created."<<std::endl;
}


//!load a texture on the renderer with additinal angle point and flip parameters
void SDLWindow::loadTextureOnRenderer(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	if(texture == nullptr)
	{
		std::cout<<"Null texture rendering attempted."<<std::endl;
		SDL_RenderPresent(_renderer);
		return;
	}
	SDL_RenderCopyEx(this->getRenderer(), texture, source, destination, angle, center, flip);
}

//!load a simple texture on the renderer
void SDLWindow::loadTextureOnRenderer(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination)
{
	if(texture == nullptr)
	{
		std::cout<<"Null texture rendering attempted."<<std::endl;
		SDL_RenderPresent(_renderer);
		return;
	}
	SDL_RenderCopy(_renderer, texture, source, destination);
}

//!hide the window
void SDLWindow::hideWindow()
{
	SDL_HideWindow(this->_window);
}

//!display window and then re render
void SDLWindow::unHideWindow()
{
	SDL_ShowWindow(this->_window);
	SDL_RenderPresent(_renderer);
}

//!clear the window renderer
void SDLWindow::clearWindowRenderer()
{
	SDL_RenderClear(_renderer);
}

//!re rendering window
void SDLWindow::displayWindow()
{
	SDL_RenderPresent(_renderer);
}

//!set the current drawing color on renderer
void SDLWindow::setDrawColor(int r, int g, int b)
{
	_red = r;
	_green = g;
	_blue = b;
	SDL_SetRenderDrawColor(_renderer, _red, _green, _blue, 0);
}


//!access window renderer
SDL_Renderer* SDLWindow::getRenderer()
{
	return this->_renderer;
}


//!access window height
unsigned int SDLWindow::getWindowHeight()
{
	return _window_height;
}


//!access window width
unsigned int SDLWindow::getWindowWidth()
{
	return _window_width;
}

//!access window title
const char* SDLWindow::getWindowTitle()
{
	return this->_window_title;
}

//!destroy window
void SDLWindow::destroyWindow()
{
	if(_window!=nullptr)
		SDL_DestroyWindow(_window);
	if(_renderer!=nullptr)
		SDL_DestroyRenderer(_renderer);
	_window = nullptr;
	_renderer = nullptr;
}


//!destructor
SDLWindow::~SDLWindow()
{
	destroyWindow();
}








