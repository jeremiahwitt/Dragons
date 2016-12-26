/**
*@file menus.h
*@brief  Provides abstract class for building windows that are ONLY menus
*/
#if !defined ( MENUS_H )
#define MENUS_H
#include "textbasedwindow.h"
#include "fileIOmanager.h"
#include "namespaces.h"
using namespace WindowHeightWidthDivideAspect;
/*!
*@class Menus
*abstract class, desgined for building windows that are solely menus and would not 
*have image components. The functions are designed to facilitate the usage of the menu engine
*/
class Menus
{
protected:
	TextBasedWindow* _menuWindow;
	std::string _menuName;
	std::vector<RGB_C*> _baseMenuColors; 

public:
	Menus();
	Menus(std::string title);
	virtual void setupMenu() = 0;
	virtual int destinationMap(int index) = 0;
	void displayMenu() const;
	void hideMenu() const;
	TextBasedWindow* getMenuWindow() const;
	RGB_C* getAMenuComponentColor(int index) const;
	void setAMenuComponentColor(const int r, const int g, const int b, const int index);
	int textWidthCalculator(std::string subject, std::string base, int basewidth);
	static int textWidthCalculator2(std::string subject, std::string base, int basewidth);
	~Menus();
};

#endif