/**
*@file levels.h
*@brief Allows functionalities to manage components in the LevelWindow
*/

#if !defined (LEVEL_H)
#define LEVEL_H

#include "image.h"
#include "fileIOmanager.h"
#include <vector>
#include <fstream>
#include "levelwindow.h"
#include "environment.h"
#include "filepathandfoldermanager.h"
#include "namespaces.h"
#include "Container.h"
#include "Item.h"
#include "Monster.h"
using namespace SimplifiedMapSymbols;
/*!
*@class Level
* Levels class has a LevelWindow as attributes, and adds functionalities to add
* manage and operate,
* actual environment and player components on the LevelWindow instance.
*/
class Level
{
protected:
	LevelWindow* _level_window;
	Level();
	std::string _environmentComponentPath;
	std::vector<std::string> _environmentComponentNames;
	std::string _playerPath;
	std::string _basicContainerPath;
	std::string _enemyPath;
	std::string _friendPath;
	std::string _directory_path_for_level_file_text_file;
	std::vector<std::string> _level;
	std::vector<SDL_Rect> _gameplayGrids;
	std::vector<Environment*> _environment_components;
	GameComponent* _player;
	Monster* _enemy;
	Monster* _friend;
	Container* _container;
	Container* _corpse;


public:
	Level(std::string path, LevelWindow* window);
	LevelWindow* getLevelWindow();
	virtual void createLevelForTargetWindow();
	void renderAndDisplayLevel();
	void destroyLevel();
	std::vector<SDL_Rect> getGameplayGridsRects();
	std::vector<Environment*> getEnvironmentComponents();
	GameComponent* getPlayerComponent();
	Container* getContainerComponent();
	Monster* getEnemy();
	Monster* getFriend();
	void addRectToGamePlayGrids(SDL_Rect dest);
	SDL_Texture* getEnvironmentTexture(int index);
	std::vector<std::string> getMapStringVersiion();
	std::vector<std::string> getMapSimpleVersion();
	std::vector<std::string>* getMapSimplePtrVersion();
	void setMainMapVector(std::vector<std::string> newmap);
	~Level();
	Container* getCorpseComponent(){
		return _corpse;
	}
};

#endif






