/**
*@file windows.h
*@brief Provides access to SDLWindow class
*/
#pragma once

#include <SDL.h>
#include <iostream>
#include <cstring>
#include <vector>
/*!
*@class SDLWindow
* This is the primary base class of generating SDL windows and setting up renderers
* also consists of basic functions such as hide and display window, setting renderer
* colors and loading texture on the window renderers
*/
class SDLWindow
{
protected:
	unsigned int _window_height;
	unsigned int _window_width;
	int _red;
	int _green;
	int _blue;
	const char* _window_title;
	SDL_Renderer* _renderer;
	SDL_Window* _window;

public:
	SDLWindow();
	SDLWindow(const char* title, int windowHeight, int windowWidth);
	unsigned int getWindowHeight();
	unsigned int getWindowWidth();
	SDL_Renderer* getRenderer();
	void setDrawColor(int r, int g, int b);
	void loadTextureOnRenderer(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination, double angle, SDL_Point* center, SDL_RendererFlip flip);
	void loadTextureOnRenderer(SDL_Texture* texture, SDL_Rect* source, SDL_Rect* destination);
	void clearWindowRenderer();
	void displayWindow();
	void hideWindow();
	void unHideWindow();
	virtual void destroyWindow();
	const char* getWindowTitle();
	~SDLWindow();
};





