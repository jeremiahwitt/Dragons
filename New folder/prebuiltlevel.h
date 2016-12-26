/**
*@file prebuiltlevel.h
*@brief Allows use of pre built levels
*/
#pragma once
#ifndef PREBUILTLEVEL_H
#define PREBUILTLEVEL_H

#include "levels.h"
#include "Fighter.h"
#include "containerOnMap.h"
#include "ContainerGenerator.h"
#include "enemyonmap.h"
#include "MonsterFactory.h"
#include "Subject.h"
#include "FighterOnMapView.h"
#include "MonsterOnMapView.h"
#include <queue> // Will be used to keep track of Character turns

/*!
*@class PreBuiltLevel
* Inherits from levels, not much specific functionalities added except for just loading a text file from a path and creating a graphical
* level out of it on the LevelWindow instance that it would contain. Extends Subject so that Characters can observe the Level for any
* changes and update their own Map.
*/
class PreBuiltLevel : public Level, public Subject
{
	friend class GamePlayEngine;
	friend class MapObserver;
protected:
	MapUpdateFlag _recentFlag;
	std::vector<SDL_Rect*> _levelComponentRects;
	SDL_Rect _inventoryPaneDest;
	SDL_Rect _movePlayerDest;
	SDL_Rect _exitPlay;
	SDL_Rect _interact;
	SDL_Rect _attack;
	SDL_Rect _savePlayer;
	SDL_Rect _endTurn;
	SDL_Rect _gameLog;
	SDL_Rect _dest1ForObserver;
	SDL_Rect _dest2ForObserver;
	int _loggerYend;
	Fighter* _player;
	std::vector<ContainerOnMap*> _containersOnMap;
	std::vector<Monster*> _enemisOnMap; //! vector storing ALL monsters on Map who are alive
	priority_queue<Characters, vector<Characters*>> _initiativeCharacterQueue; //! PQ which is used to manage turn execution during each round

public:
	
	PreBuiltLevel();
	PreBuiltLevel(std::string path, Fighter* player);
	void loadUserCreatedLevel(std::string name);
	Environment* _environmentForObserver;
	std::vector<SDL_Rect*> getLevelComponentRects();
	void setLevelOnTargetWindow();
	void createLevelForTargetWindow();
	std::string getEnvironmentComponentsPath() const;
	std::string getDirectoryPathForLevelTextFile() const;
	std::string getPlayerPath() const;
	std::string getEnemyPath() const;
	std::string getFriendPath() const;
	std::vector<std::string> getBuiltLevelFile() const;
	Fighter* getPlayer();
	void setupContainersOnMap();
	void setupEnemiesOnMap();
	void addContainerOnTheMap(ContainerOnMap* prolly_a_dead_dude);
	std::vector<ContainerOnMap*> getContainersOnMap();
	void removeContainerOnMap(int index);
	std::vector<Monster*> getEnemiesOnMap();
	std::vector<SDL_Rect> getAllButtonDestinations();
	void setDestRectsForObserver(SDL_Rect dest1, SDL_Rect dest2);
	void getDestRectsForObserver(SDL_Rect* dest1, SDL_Rect* dest2);
	~PreBuiltLevel();
	void setRecentUpdateFlag(MapUpdateFlag newUpdate) { _recentFlag = newUpdate; }; //! Sets the recent update flag to indicate how the Map should render

	// Methods for Turn Management
	void setAllInitiative();
	void setupInitiativeQueue();
	bool isInitiativeQueueEmpty() { return _initiativeCharacterQueue.empty(); };
	//void runTurn();
	
};

#endif;