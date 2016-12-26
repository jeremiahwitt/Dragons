/**
*@file mapeditorengine.h
*@brief Provides declaration of MapEditorEngine class, used to edit maps
*/

#if !defined( MAPENGINE_H )
#define MAPENGINE_H
#include "game_loops.h"
#include "leveleditor.h"
#include "namespaces.h"
#include "routing.h"
#include "Monster.h"
using namespace SimplifiedMapSymbols;
/*!
*@class MapEditorEngine
* The main map editor class for this assignment.
* manages all functionalities of map creation.
* Primarily handles user inputs based on where the mouse cursor is on window
* also validates map when the user wants the map to be accepted.
* I have a separate singleton class for Routing, details in the class header file
*/
class MapEditorEngine
{
private:
	SDL_Texture* targetTexture;
	bool quit;
	bool ontargetfirsttime;
	bool targetselected;
	bool wasAtGamePlayGrids;
	bool renderingOnGameplayGrids;
	bool canDelete;
	bool targetisplayer;
	bool targetisexit;
	bool targetiscontainer;
	bool targetisenemy;
	
	SDL_Rect target;
	Environment* currentenvcomponent;
	GameComponent* player;
	Monster* enemy;
	Monster* friends;
	Container* container;
	LevelEditor* level;
	int lastButtonIndex;
	int playercounter;
	int exitdoorcounter;
	int targetIndex;
	std::vector<Environment*> envcomponents;
	std::vector<std::string> templevel;
	std::vector<std::string> simplemap;
	std::vector<SDL_Rect> components;
	std::vector<SDL_Rect> characterTarget;
	std::vector<SDL_Rect> containerTarget;
	std::vector<SDL_Rect> enemytarget;
	std::vector<SDL_Rect> friendtarget;
	

public:
	void setTargetTexture(SDL_Texture* t);
	SDL_Texture* getTargetTexture();
	bool targetisfriend;
	void setQuit(bool q);
	bool getQuit();
	void setOnTargetFirstTime(bool o);
	bool getOnTargetFirstTime();
	void setTargetSelected(bool t);
	bool getTargetSelected();
	void setWasAtGameplayGrids(bool w);
	bool getWasAtGameplayGrids();
	void setRenderingOnGameplayGrids(bool r);
	bool getRenderingOnGameplayGrids();
	void setCanDelete(bool c);
	bool getCanDelete();
	void setTargetIsPlayer(bool s);
	bool setTargetIsPlayer();
	void setTargetIsExit(bool e);
	bool getTargetIsExit();
	void setTargetisContainer(bool c);
	void setTargetisEnemy(bool e);
	MapEditorEngine();
	MapEditorEngine(LevelEditor* level_);
	SDL_Rect checkMousePosition(std::vector<SDL_Rect> components, int* targetIndex);
	bool checkIfMouseOnARectangle(SDL_Rect* target);
	SDL_Rect getRectGridOfMouse(LevelWindow* window);
	std::vector<std::string> getEnvironmentTextLevel();	
	void fillCell(int x, int y, char component);
	bool isOccupied(int x, int y);
	bool validateMap();
	bool isOccupied();
	bool isPlayerOnCell(int x, int y);
	bool isCellAnObstruction(int x, int y);
	void setMapForTest(std::vector<std::string> test);
	void onGameplayGrids(SDL_Event* _event);
	void onEnvironmentGrid(SDL_Event* _event);
	void onContainerGrid(SDL_Event* _event);
	void onCharacterGrid(SDL_Event* _event);
	int onRightHandMenuGrid(SDL_Event* _event);
};

#endif 