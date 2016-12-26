#include "game_components.h"

//!default constructor for testing purposes only
GameComponent::GameComponent()
{
}

//FOLLOWING IS TEMPORAY FOR TEST ONLY
bool GameComponent::isComponentObstructionToPlayer()
{
	return this->_obstructionToPlayer;
}
void GameComponent::setObstructionToPlayer(bool isobstructiontoplayer)
{
	this->_obstructionToPlayer = isobstructiontoplayer;
}

//!parameterized constructor sets everything but the component image is only to nullptr, it is setup later on
GameComponent::GameComponent(std::string componentname, char componentchar, gameplayGridComponentTypes componenttype, std::string imagepath)
{
	this->_componentChar = componentchar;
	this->_componentImage = nullptr;
	this->_obstructionToPlayer = false;
	this->_componentName = componentname;
	this->_componentType = componenttype;
	this->_image_path = imagepath;
}

//!set the image path manually
void GameComponent::setImagePath(std::string newpath)
{
	this->_image_path = newpath;
}

//!set the component char manuall
void GameComponent::setComponentChar(char thechar)
{
	this->_componentChar = thechar;
}

//!set the name of component
void GameComponent::setComponentName(std::string friends)
{
	this->_componentName = friends;
}

//!sets the component on target window rendered after loading the image
void GameComponent::setupComponentOnTargetWindowRenderer(SDL_Renderer* window_renderer)
{
	if (this->_componentImage != nullptr)
	{
		delete this->_componentImage;
		this->_componentImage = nullptr;
	}
	_componentImage = new SDL_Image(_image_path);
	_componentImage->setupImageOnTargetWindowRenderer(window_renderer);
}

//!returns the image details of the component
SDL_Image* GameComponent::getImageDetails()
{
	return this->_componentImage;
}

//!returns the caracter associated with the component
char GameComponent::getComponentChar()
{
	return this->_componentChar;
}

//!returns the name of the component
std::string GameComponent::getComponentName()
{
	return this->_componentName;
}

//!destroys image portion of the component
void GameComponent::destroyComponent()
{
	if(this->_componentImage!=nullptr)
		delete this->_componentImage;
	_componentImage = nullptr;
}

//!destructor invokes the destroy component method
GameComponent::~GameComponent()
{
	destroyComponent();
}




