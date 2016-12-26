/**
*@file MovementStrategy.h
*@brief Provides declaration of abstract Strategy class, used for Character logic.
*/
#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H
#include <vector>
#include <string>
#include <math.h>
#include "namespaces.h"
#include <SDL.h>

using namespace std;
class PreBuiltLevel;
class GamePlayEngine;

/**
*@enum MovementDirection
*@brief Used to easily specific direction of movement
*/
enum MovementDirection { North, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest, Invalid };

/**
*@class MovementStrategy
*@brief Abstract Strategy. Will allow for its subclasses to move Characters across the map.
*/
class MovementStrategy {
public:
	virtual bool move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine) = 0; //! Determines movement logic
	virtual bool move(int vectPos, int charPos) = 0; //! Moves characters to very specific locations on map
	virtual void setMap(vector<string> *newMap);
	virtual void setPosition(int vectI, int charI);
	virtual bool isWithinRange(int vectI, int charI) = 0;
	virtual int getVectPos();
	virtual int getCharPos();
	int getSpeed() { return _speed; }; //! Returns the speed being used by the Strategy
	MovementStrategy();
	MovementStrategy(int speed);
	virtual ~MovementStrategy() { delete _theMap; }; //! Destructor, ensures the map vector gets deleted
	SDL_Rect* getRecentGrid() { return _recentGrid; }; //! Returns the most recent grid used when moving the Character
protected:
	SDL_Rect* _recentGrid; //! Needed to help re-rendering of map after movement
	vector<string> *_theMap; // Will store the current map
	virtual bool _locationWithinMapBounds(int vectI, int charI);
	virtual bool _acceptableDestinationSquare(int vectI, int charI);
	virtual bool _noObstacleInPath(int vectI, int charI, MovementDirection dir);
	int _vectPos; //! The current vector position of the strategy
	int _charPos; //! The current char position of the strategy
	int _speed; //! The current speed of the strategy
	void logMoveAttempt(int vectI, int charI, GamePlayEngine *engine);
};

#endif