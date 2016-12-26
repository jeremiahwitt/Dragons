//!@file textbasedwindow.cpp
//!@brief Provides implementation of TextBasedWindow class methods
#include "textbasedwindow.h"

//!default constructor loads all ttf assests
TextBasedWindow::TextBasedWindow()
{
	_title = nullptr;
	_fontIndex = 0;
	_font_types = SingletonFilePathAndFolderManager::getInstance()->loadPathsForAllTTFAssets();
	this->_title = new Text();
}

//!parameterized constructor, loads all ttf assets and then calls super class constructor to generate the window
TextBasedWindow::TextBasedWindow(std::string title, int height, int width)  : SDLWindow(title.c_str(), height, width)
{
	_fontIndex = 0;
	_font_types = SingletonFilePathAndFolderManager::getInstance()->loadPathsForAllTTFAssets();
	this->_title = new Text();
}

//!sets background color of window based on parameters
void TextBasedWindow::setBackgroudColor(unsigned int r, unsigned int g, unsigned int b)
{
	SDL_SetRenderDrawColor(this->getRenderer(), r, g, b, 255);
	SDL_RenderClear(this->_renderer);
}

//!clears existing text lables
void TextBasedWindow::clearTextLabels()
{
	std::vector<Text*> temp;
	temp.push_back(this->_textLabel[0]);
	temp.push_back(this->_textLabel[1]);
	for (int x = 2; x < this->_textLabel.size(); x++)
	{
		if (this->_textLabel[x] != nullptr)
		{
			delete this->_textLabel[x];
			this->_textLabel[x] = nullptr;
		}
	}
	this->_textLabel = temp;
	
	//this->_textLabel.clear();
}
//!sets the font size that is related to the window titles
void TextBasedWindow::setTitleFontSize(int size)
{
	if(_title==nullptr)
	{
		std::cout<<"Trying to set font size without initializing text, exiting program."<<std::endl;
		getch();
		exit(-1);
	}
	this->_title->setFontSize(size);
}

//!sets the font size to the buttons that is related to the window
void TextBasedWindow::setButtonFontSize(int size)
{
	for(int x=0; x<this->_buttons.size(); x++)
		this->_buttons[x]->setFontSize(size);
}

//!sets the font type for all text that is related to the window
void TextBasedWindow::setFontType(int index)
{
	if((index > (this->_font_types.size()-1)) || index < 0)
	{
		std::cout<<"Font index is invalid, exiting program."<<std::endl;
		getch();
		exit(-1);
	}
	this->_fontIndex = index;
	if(_title==nullptr)
	{
		std::cout<<"Trying to set font size without initializing text, exiting program."<<std::endl;
		getch();
		exit(-1);
	}
	this->_title->setFontType(this->_font_types[_fontIndex]);
	for(int x=0; x<this->_buttons.size(); x++)
		this->_buttons[x]->setFontType(this->_font_types[_fontIndex]);
}

//!sets the title text of the window on a specified destination rectangle
void TextBasedWindow::setTitle(std::string text, unsigned int r, unsigned int g, unsigned int b, SDL_Rect destination)
{
	if(_title==nullptr)
	{
		std::cout<<"Trying to set font size without initializing text, exiting program."<<std::endl;
		exit(-1);
	}
	this->_title->setTextColor(r,g,b);
	this->_title->setDestinationRectOnTargetWindow(destination);
	this->_title->setText(text);
	this->_title->createTextTextureOnTargetWindowRenderer(_renderer);
}

//!sets the title text on the window, based on an x and y position, where as height an width is calculate optimally
void TextBasedWindow::setTitle(std::string text, unsigned int r, unsigned int g, unsigned int b, int xpos, int ypos)
{
	if(_title==nullptr)
	{
		std::cout<<"Trying to set font size without initializing text, exiting program."<<std::endl;
		getch();
		exit(-1);
	}
	this->_title->setTextColor(r,g,b);
	this->_title->setText(text);
	this->_title->createTextTextureOnTargetWindowRenderer(_renderer);
	this->_title->setOptimalHeightWidthRect(xpos,ypos);
}

//!sets a string for the path of the font type being used
std::string TextBasedWindow::getCurrentFontTypePath()
{
	return this->_font_types[this->_fontIndex];
}

//!returns the Text pointer of title
Text* TextBasedWindow::getTitleText()
{
	return this->_title;
}

//!adds a button to the window based on destination rectangle
void TextBasedWindow::addButton(std::string text, unsigned int r, unsigned int g, unsigned int b, SDL_Rect destination)
{
	Text* temp = new Text();
	temp->setTextColor(r,g,b);
	temp->setFontType(this->_font_types[_fontIndex]);
	temp->setDestinationRectOnTargetWindow(destination);
	temp->setText(text);
	temp->createTextTextureOnTargetWindowRenderer(_renderer);
	this->_buttons.push_back(temp);
}

//!adds a button to the window based on x and y position, heigh and width is calucalted optimally
void TextBasedWindow::addButton(std::string text, unsigned int r, unsigned int g, unsigned int b, int xpos, int ypos)
{
	Text* temp = new Text();
	temp->setTextColor(r,g,b);
	temp->setFontType(this->_font_types[_fontIndex]);
	temp->setText(text);
	temp->createTextTextureOnTargetWindowRenderer(_renderer);
	temp->setOptimalHeightWidthRect(xpos, ypos);
	this->_buttons.push_back(temp);
}

//!changes a specific window button color
void TextBasedWindow::changeButtonColor(int index, int r, int g, int b)
{
	//set the color
	this->_buttons[index]->setTextColor(r,g,b);

	//create the texture
	this->_buttons[index]->createTextTextureOnTargetWindowRenderer(_renderer);

	//copy renderer
	SDL_RenderCopy(_renderer, this->_buttons[index]->getTextTexture(), nullptr, &this->_buttons[index]->getTargetOnWindowRectangle());

	//display the menu
	displayWindow();
}

//!adds a text label to the window based on destination rectangle
void TextBasedWindow::addTextLabel(std::string text, unsigned int r, unsigned int g, unsigned int b, SDL_Rect destination)
{
	Text* temp = new Text();
	temp->setTextColor(r,g,b);
	temp->setFontType(this->_font_types[_fontIndex]);
	temp->setDestinationRectOnTargetWindow(destination);
	temp->setText(text);
	temp->createTextTextureOnTargetWindowRenderer(_renderer);
	this->_textLabel.push_back(temp);
}

//!adds a text label to the window based on x and y position, heigh and width is calucalted optimally
void TextBasedWindow::addTextLabel(std::string text, unsigned int r, unsigned int g, unsigned int b, int xpos, int ypos)
{
	Text* temp = new Text();
	temp->setTextColor(r,g,b);
	temp->setFontType(this->_font_types[_fontIndex]);
	temp->setText(text);
	temp->createTextTextureOnTargetWindowRenderer(_renderer);
	temp->setOptimalHeightWidthRect(xpos,ypos);
	this->_textLabel.push_back(temp);
}

//!sets the fontsize for all text labels related to the window
void TextBasedWindow::setTextLabelFontSize(int size)
{
	for(int x=0; x<this->_textLabel.size(); x++)
		this->_textLabel[x]->setFontSize(size);
}

//!sets all the text options in the window on the window renderer
void TextBasedWindow::setMenuOnRenderer()
{
	if(this->_title->getTextTexture() != nullptr)
		loadTextureOnRenderer(this->_title->getTextTexture(), nullptr, &this->_title->getTargetOnWindowRectangle());
	for(int x=0; x<this->_buttons.size(); x++)
		loadTextureOnRenderer(this->_buttons[x]->getTextTexture(), nullptr, &this->_buttons[x]->getTargetOnWindowRectangle());
	for(int x=0; x<this->_textLabel.size(); x++)
		loadTextureOnRenderer(this->_textLabel[x]->getTextTexture(), nullptr, &this->_textLabel[x]->getTargetOnWindowRectangle());
}

//!returns index of the button based on button poisiton on window and the x and y coordinates pased
int TextBasedWindow::getButtonIndexThatMouseIsOn(int x, int y)
{
	for(int z=0; z<this->_buttons.size(); z++)
		if(this->_buttons[z]->checkIfMouseOnText(x,y) == true)
			return z;
	return -1;
}

//!destroy the text based window
void TextBasedWindow::destroyMenu()
{
	if(this->_title!=nullptr)
	{
		delete this->_title;
		this->_title = nullptr;
	}
	for(int x=0; x<this->_buttons.size(); x++)
	{
		if(this->_buttons[x]!=nullptr)
		{
			delete this->_buttons[x];
			this->_buttons[x] = nullptr;
		}
	}
}

//!destructor just invokes the destroy menu method
TextBasedWindow::~TextBasedWindow()
{
	destroyMenu();
}