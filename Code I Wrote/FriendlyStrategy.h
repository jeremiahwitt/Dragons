/**
*@file FriendlyStrategy.h
*@brief Provides declaration of FriendlyStrategy class.
*/

#ifndef FRIENDLYSTRATEGY_H
#define FRIENDLYSTRATEGY_H
#include "MovementStrategy.h"
#include "CharacterObserver.h"
#include "Monster.h"
#include "Fighter.h"
#include <vector>
using namespace std;

/**
*@class FriendlyStrategy
*@brief Provides movement strategy that will be used by Friendly Monsters. Does NOT allow for attacking after movement.
*/
class FriendlyStrategy : public MovementStrategy, CharacterObserver {
	friend class AggressorStrategy; // Needed to ensure conversion between the two Strategy types
	friend class Monster;
protected:
	vector<MovementDirection>& _determinePlayerDirection();
	int _playerVectPos; //! Vector position of the Human Player
	int _playerCharPos; //! Char position of the Human Player
public:
	FriendlyStrategy(int speed, Characters* thePlayer);
	virtual bool move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine);
	bool move(int x, int y) { return false; }; //! Allows for movement to a specific location
	bool canMove(int vectI, int charI, MovementDirection dir);
	bool isWithinRange(int vectI, int charI);
	virtual void Update();
	virtual bool _acceptableDestinationSquare(int vectI, int charI);
	Characters* getSubject(){ return _sub; }; //! Returns the subject of the FriendlyStrategy
};

#endif