//!@file text.cpp
//!@brief Provides implementation of Text methods
#include "text.h"

//!default constructor
Text::Text()
{
	this->_font = nullptr;
	this->_source = nullptr;
	this->_texture = nullptr;
	this->_red = 255;
	this->_green = 0;
	this->_blue = 0;
	this->_font_size = 64;
	this->_text = "default";
}

//!sets the font size
void Text::setFontSize(int size)
{
	this->_font_size = size;
}

//!sets the ttf type based on a path, from where the .ttf file can be loaded
void Text::setFontType(std::string path)
{
	this->_font = TTF_OpenFont(path.c_str(), this->_font_size);
	if(this->_font == nullptr)
	{
		std::cout<<"Could not load ttf font."<<std::endl;
		exit(-1);
		system("pause");
	}
}

//!creates a text texture for the target window renderer
void Text::createTextTextureOnTargetWindowRenderer(SDL_Renderer* targetWindowRenderer)
{
	SDL_Color color = {this->_red, this->_green, this->_blue};
	
	if(this->_font == nullptr)
		std::cout<<"Font not set: "<<std::endl;

	_source = TTF_RenderText_Solid(this->_font, this->_text.c_str(), color);
	
	if( _source == nullptr )
	{
		std::cout<<"Could not create text surface."<<SDL_GetError()<<std::endl;
		system("pause");
		exit(-1);
	}

	this->_texture = SDL_CreateTextureFromSurface(targetWindowRenderer, this->_source);
	
	if(this->_texture == nullptr)
	{
		std::cout<<"Could not create text texture. "<<SDL_GetError()<<std::endl;
		system("pause");
		exit(-1);
	}

	SDL_FreeSurface(_source);
	_source = nullptr;
}

//!checks to see based on position of the text texture on window, is the coordinates passed would lie on the text
bool Text::checkIfMouseOnText(int x, int y)
{
	//check if below y coordinate
	if((y>=this->_target_on_window.y) && (y<=(this->_target_on_window.y+this->_target_on_window.h)))
		//check if within width
		if((x>=this->_target_on_window.x) && (x<=(this->_target_on_window.x+this->_target_on_window.w)))
			return true;
	return false;
}

//!access text texture
SDL_Texture* Text::getTextTexture()
{
	return this->_texture;
}

//!access the destination rectangle where the text would lie on the window
SDL_Rect Text::getTargetOnWindowRectangle()
{
	return this->_target_on_window;
}

//!sets the destination on the window where the text is desired to be rendered
void Text::setDestinationRectOnTargetWindow(SDL_Rect target)
{
	this->_target_on_window = target;
}

//!based on an x and y coordinate, this function calculates height and width that is
//!most optimal for the text
void Text::setOptimalHeightWidthRect(int xpos, int ypos)
{
	SDL_QueryTexture(this->_texture, nullptr, nullptr, &this->_width, &this->_height);
	this->_target_on_window.x = xpos;
	this->_target_on_window.y = ypos;
	this->_target_on_window.w = this->_width;
	this->_target_on_window.h = this->_height;
}

//!set the text height and width manually
void Text::setManualWidthHeight(int width, int height)
{
	this->_target_on_window.h = height;
	this->_target_on_window.w = width;
}

//!set the actual string for the text
void Text::setText(std::string text)
{
	this->_text = text;
}

//!set the text color
void Text::setTextColor(unsigned int r, unsigned int g, unsigned int b)
{
	this->_red = r;
	this->_green = g;
	this->_blue = b;
}

//!destroy the text
void Text::destroyText()
{
	if(this->_source != nullptr)
	{
		SDL_FreeSurface(_source);
		_source = nullptr;
	}
	if(this->_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
	if(this->_font != nullptr)
	{
		TTF_CloseFont(this->_font);
		this->_font = nullptr;
	}
}
//!destructor just calls the destroy text function
Text::~Text()
{
	this->destroyText();
}