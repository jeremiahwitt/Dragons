/**
*@file AggressorStrategy.h
*@brief Provides declaration of AggressorStrategy class.
*/

#ifndef AGGRESSORSTRATEGY_H
#define AGGRESSORSTRATEGY_H
#include "MovementStrategy.h"
#include "CharacterObserver.h"
#include "Monster.h"
#include "Fighter.h"
#include <vector>
using namespace std;

class FriendlyStrategy; // Forward declaration of FriendlyStrategy, to prevent cyclic dependencies caused by include

/**
*@class AggressorStrategy
*@brief Provides movement strategy used by Aggressive Monsters. This strategy ensures that the Monster attacks the player
* after they move, if they are able to do so.
*/
class AggressorStrategy : public MovementStrategy, CharacterObserver {
	friend class Monster;
protected:
	vector<MovementDirection>& _determinePlayerDirection();
	int _playerVectPos; //! Vector position of the Human Player
	int _playerCharPos; //! Char position of the Human Player
	bool isWithinRange(int vectIndex, int charIndex);
public:
	AggressorStrategy(int speed, Characters* thePlayer);
	AggressorStrategy(FriendlyStrategy* otherStrat);
	bool move(int x, int y) { return false; };
	virtual bool _acceptableDestinationSquare(int vectI, int charI);
	virtual bool move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine);
	bool canMove(int vectI, int charI, MovementDirection dir);
	virtual void Update();
};

#endif