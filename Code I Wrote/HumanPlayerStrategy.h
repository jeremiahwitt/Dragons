/**
*@file HumanPlayerStrategy.h
*@brief Provides declaration of HumanPlayerStrategy class.
*/
#ifndef HUMANPLAYERSTRATEGY_H
#define HUMANPLAYERSTRATEGY_H
#include "MovementStrategy.h"
#include <conio.h>

/**
*@class HumanPlayerStrategy
*@brief Provides MovementStrategy which allows the human player to control the movement and actions of
* the Fighyer on the Map.
*/
class HumanPlayerStrategy : public MovementStrategy {
protected:
	MovementDirection _determineMovementDirection(int vectI, int charI);
public:
	virtual bool move(int vectI, int charI);
	virtual bool move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine);
	bool isWithinRange(int vectI, int charI);
	HumanPlayerStrategy(int speed);
};

#endif