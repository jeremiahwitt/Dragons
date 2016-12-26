/**
*@file text.h
*@brief Provides access to Text class, used for management of rendering text to screen
*/

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include "windows.h"
#include "filepathandfoldermanager.h"
/*!
*@class Text
*This class is designed to abstract the process of detailing the text funtionalities of sdl.
*primary responsibility is to create a text based texture for a target window renderer, based
*on a specific true type font
*/
class Text
{
private:
	TTF_Font* _font;
	SDL_Surface* _source;
	SDL_Texture* _texture;
	SDL_Rect _target_on_window;
	unsigned int _red;
	unsigned int _green;
	unsigned int _blue;
	unsigned int _font_size;
	int _height;
	int _width;
	std::string _text;

public:
	Text();
	void createTextTextureOnTargetWindowRenderer(SDL_Renderer* targetWindowRenderer);
	void setFontSize(int size);
	void setFontType(std::string path);
	void setOptimalHeightWidthRect(int xpos, int ypos);
	void setManualWidthHeight(int width, int height);
	void setDestinationRectOnTargetWindow(SDL_Rect target);
	void setText(std::string text);
	void setTextColor(unsigned int r, unsigned int g, unsigned int b);
	SDL_Texture* getTextTexture();
	SDL_Rect getTargetOnWindowRectangle();
	bool checkIfMouseOnText(int x, int y);
	void destroyText();
	~Text();
};