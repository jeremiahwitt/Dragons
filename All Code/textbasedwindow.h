/**
*@file textbasedwindow.h
*@brief Provides access to TextBasedWindow class
*/

#pragma once
#include "windows.h"
#include "text.h"
/*!
*@class TextBasedWindow
*Child class of windows, adds in text functionalities to the window
*primarily added features include ability to load titles buttons and 
*other text lables on window. Also manipulate the new added features.
*This class has been vigourously used in the project for generating
*windows that are purely menus. But its menu like functionalites has
*also been used in windows that are not completely menus
*/
class TextBasedWindow : public SDLWindow
{
protected:
	Text* _title;
	int _fontIndex;
	std::vector<Text*> _textLabel;
	std::vector<Text*> _buttons;
	std::vector<std::string> _font_types;

public:
	TextBasedWindow();
	TextBasedWindow(std::string title, int height, int width);
	void setBackgroudColor(unsigned int r, unsigned int g, unsigned int b);
	void setFontType(int index);
	void setTitle(std::string text, unsigned int r, unsigned int g, unsigned int b, SDL_Rect destination);
	void setTitle(std::string text, unsigned int r, unsigned int g, unsigned int b, int xpos, int ypos);
	void addButton(std::string text, unsigned int r, unsigned int g, unsigned int b, SDL_Rect destination);
	void addButton(std::string text, unsigned int r, unsigned int g, unsigned int b, int xpos, int ypos);
	void addTextLabel(std::string text, unsigned int r, unsigned int g, unsigned int b, SDL_Rect destination);
	void addTextLabel(std::string text, unsigned int r, unsigned int g, unsigned int b, int xpos, int ypos);
	void clearTextLabels();
	void setTitleFontSize(int size);
	void setButtonFontSize(int size);
	void changeButtonColor(int index, int r, int g, int b);
	void setTextLabelFontSize(int size);
	Text* getTitleText();
	std::vector<Text*> getTextLabelsVector();
	std::vector<Text*> getTextButtonsVector();
	int getButtonIndexThatMouseIsOn(int x, int y);
	std::string getCurrentFontTypePath();
	void setMenuOnRenderer();
	void destroyMenu();
	~TextBasedWindow();
};