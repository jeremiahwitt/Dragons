#include "menus.h"

//!default constructor, this is used only for test purposes, not going to play a part the main project
Menus::Menus()
{
	this->_menuName = "test";
	this->_menuWindow = nullptr;
}

//!paramerized constructor, the constructor that wil be used for the main project, apart from setting the window
//!this also takes care of setting the primary color for tile, text labels, buttons and background
Menus::Menus(std::string title)
{
	this->_menuName = title;
	SDL_DisplayMode monitor;
	if(SDL_GetCurrentDisplayMode(0, &monitor) != 0)
	{
		std::cout<<"Failed to create an SDL window."<<std::endl;
		system("pause");
		exit(-1);
	}
	//create window based on window height and width
	this->_menuWindow = new TextBasedWindow(this->_menuName, (int)(monitor.h/_WindowHeightDivideAspect_), (int)(monitor.w/_WindowWidthDivideAspect_));

	//setup based on name space declared
	/*const int _MenuBackground_ = 0;
	const int _YesButtonSelect_ = 1;
	const int _NoButtonSelect_ = 2;
	const int _Title_ = 3;
	const int _OtherText = 4;*/

	//background at index 0
	this->_baseMenuColors.push_back(new RGB_C(100,35,45));

	//yes button at index 1
	this->_baseMenuColors.push_back(new RGB_C(101,204,204));

	//no button at index 2
	this->_baseMenuColors.push_back(new RGB_C(255,255,255));

	//title at index 3
	this->_baseMenuColors.push_back(new RGB_C(255,255,255));

	//other text at index 4
	this->_baseMenuColors.push_back(new RGB_C(255,200,0));

	//label text at index 5
	this->_baseMenuColors.push_back(new RGB_C(150, 150, 150));
}

//!menu window accessor
TextBasedWindow* Menus::getMenuWindow() const
{
	return this->_menuWindow;
}

//!a menu component color accessor
RGB_C* Menus::getAMenuComponentColor(int index) const
{
	if(index<0 || index> this->_baseMenuColors.size())
		return nullptr;
	return this->_baseMenuColors[index];
}

//!calculates and return text width in pixels for a subject text, based on a base string and base width passed
int Menus::textWidthCalculator(std::string subject, std::string base, int basewidth)
{
	int charwidth = basewidth / base.length();
	return charwidth*subject.length();
}
//!calculates text width, only this one is static
int Menus::textWidthCalculator2(std::string subject, std::string base, int basewidth)
{
	int charwidth = basewidth / base.length();
	return charwidth*subject.length();
}

//!sets the color for a specific menu component
void Menus::setAMenuComponentColor(const int r, const int g, const int b, const int index)
{
	if(index<0 || index> this->_baseMenuColors.size())
		return;

	this->_baseMenuColors[index]->red = r;
	this->_baseMenuColors[index]->green = g;
	this->_baseMenuColors[index]->blue = b;
}

//!displays menu
void Menus::displayMenu() const
{
	this->_menuWindow->unHideWindow();
}

//!hides the menu
void Menus::hideMenu() const
{
	this->_menuWindow->hideWindow();
}

//!destructor destroy all dynamically allocated data for the menu
Menus::~Menus()
{
	if(this->_menuWindow != nullptr)
	{
		this->_menuWindow->destroyMenu();
		this->_menuWindow = nullptr;
	}

	for(int x=0; x<this->_baseMenuColors.size(); x++)
	{
		if(this->_baseMenuColors[x] != nullptr)
		{
			delete this->_baseMenuColors[x];
			this->_baseMenuColors[x] = nullptr;
		}
	}
}
