/**
*@file leveleditor.h
*@brief Provides declaration of LevelEditor class, used to edit levels
*/

#if !defined( LEVEL_EDITOR_H )
#define LEVEL_EDITOR_H

#include "levels.h"
#include "prebuiltlevel.h"
/*!
*@class LevelEditor
* This class inherits from level, the main spesific functionalities of
* this class include attributes and behaviours that would facilitate the mangement
* of portions beyond the main gameplay grid.
* at the bottom will be gameplay components that user can use to create the map
* at bottom right will be description of the game components
* and on the right hand side will be a small menu system
*/
class LevelEditor : public Level
{
protected:
	int _bottom_Y_start;
	int _X_Cor_EnvironmentPortionEnd_ItemPortionStart;
	int _X_Cor_ItemPortionEnd_CharacterPortionStart;
	int _X_Cor_CharacterPortionEnd_DescriptionPortionStart;
	std::vector<Text*> _tempText;
	int _ypixels;
	int _yportion;
	int _themeIndex;
	int _y_init;
	int _y_height;
	int _y_space;

	//text labels
	SDL_Rect _environmentTextDestination;
	SDL_Rect _itemsTextDestination;
	SDL_Rect _characterTextDestination;
	SDL_Rect _descriptionRect;

	//buttons for menu
	SDL_Rect _backToMainMenu;
	SDL_Rect _instructions;
	SDL_Rect _acceptmap;

	std::vector<SDL_Rect> levelComponentRects;
	std::vector<SDL_Rect> _bottomMenuRects;
	std::vector<SDL_Rect> _sideMenuRects;
	SDL_Rect _playerDestinationAtBottom;
	SDL_Rect _enemyDestinationAtBottom;
	SDL_Rect _friendDestinationAtBottom;
	SDL_Rect _basicContainerAtBottom;
public:
	LevelEditor(LevelWindow* window, int themIndex);
	void setEnvironmentTextVector(std::vector<std::string> environmentVector);
	std::vector<std::string> getEnvironmentTextVector();
	void takeComponentsFromPreBuiltLevel(PreBuiltLevel* pbLevel);
	void renderEnvironmentAtBottom();
	void renderItemsAtBottom();
	void renderCharactersAtBottom();
	void renderDescriptionAtBottomRIght(GameComponent* component);
	void renderAllNonGameplayGridPortions();
	int getEnvironmentPortionEnd_X_Xor();
	int getItemPortionEnd_X_Cor();
	int getCharacterPortionEnd_X_Cor();
	void createLevelForTargetWindow();
	void saveLevel(std::string levelname);
	std::vector<SDL_Rect> getLevelComponentRects();
	SDL_Rect getPlayerDestinationAtBottomRect();
	SDL_Rect getContainerDestinationAtBottomRect();
	SDL_Rect getEnemyDestinationAtBottomRect();
	SDL_Rect getFriendDestinationAtBottomRect();
	int get_Y_start();
	int getThemeIndex() const;
	std::vector<std::string> getLevelMapVector() const;
	~LevelEditor();
};

#endif