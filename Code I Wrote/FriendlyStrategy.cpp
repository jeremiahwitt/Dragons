/**
*@file FriendlyStrategy.cpp
*@brief Implementation of the FriendlyStrategy class
*/

#include "FriendlyStrategy.h"
#include "prebuiltlevel.h"
#define M_PI 3.141592653589 //! Representation of PI used for calculations

/**
* Parameterized Constructor. Takes the speed of the Friendly as a parameter and passes it to the parent
* super constructor
*/
FriendlyStrategy::FriendlyStrategy(int speed, Characters* thePlayer) : MovementStrategy(speed), CharacterObserver(thePlayer) {}

/**
* Movement logic algorithm.
*<p>Attempts to move the Monster to an appropriate direction. Will determine directions that will help the monster move toward the character,
* and will then try moving in each of those directions SPEED steps or less. Updates position after movement.
*/
bool FriendlyStrategy::move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine){
	// Determine order of directions to attempt moving in
	vector<MovementDirection> *dirToTry = &_determinePlayerDirection();
	_theMap = level->getMapSimplePtrVersion();
	bool iMoved = false;
	// Will iterate through each direction, trying to move either SPEED or fewer squares in that direction. If cannot, will move onto the next direction
	for (int i = 0; i < dirToTry->size(); ++i){
		MovementDirection direction = dirToTry->at(i);
		for (int j = _speed; j > 0; --j){
			switch (direction){
			case North:
				if (canMove(_vectPos - j, _charPos, North)){
					logMoveAttempt(_vectPos - j, _charPos, engine);
					setPosition(_vectPos - j, _charPos);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			case South:
				if (canMove(_vectPos + j, _charPos, South)){
					logMoveAttempt(_vectPos + j, _charPos, engine);
					setPosition(_vectPos + j, _charPos);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			case East:
				if (canMove(_vectPos, _charPos + j, East)){
					logMoveAttempt(_vectPos, _charPos + j, engine);
					setPosition(_vectPos, _charPos + j);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			case West:
				if (canMove(_vectPos, _charPos - j, West)){
					logMoveAttempt(_vectPos, _charPos - j, engine);
					setPosition(_vectPos, _charPos - j);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			case NorthEast:
				if (canMove(_vectPos - j, _charPos + j, NorthEast)){
					logMoveAttempt(_vectPos - j, _charPos + j, engine);
					setPosition(_vectPos - j, _charPos + j);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			case NorthWest:
				if (canMove(_vectPos - j, _charPos - j, NorthWest)){
					logMoveAttempt(_vectPos - j, _charPos - j, engine);
					setPosition(_vectPos - j, _charPos - j);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			case SouthEast:
				if (canMove(_vectPos + j, _charPos + j, SouthEast)){
					logMoveAttempt(_vectPos + j, _charPos + j, engine);
					setPosition(_vectPos + j, _charPos + j);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			case SouthWest:
				if (canMove(_vectPos + j, _charPos - j, SouthWest)){
					logMoveAttempt(_vectPos + j, _charPos - j, engine);
					setPosition(_vectPos + j, _charPos - j);
					iMoved = true;
					goto AFTER_ATTEMPT;
				}
				break;
			}
		}
	}
AFTER_ATTEMPT:
	_recentGrid = currentGrid;
	return iMoved;
}

/**
* Determines if the Monster is able to move to the requested position in the indicated direction.
*<p>First, makes sure that the location is within the map's bounds.
*<p>Second, checks if the destination can be landed on.
*<p>Third, checks if there are any obstacles in the path that the character will have to follow.
*<p>If all is successful, then the player can move there.
*/
bool FriendlyStrategy::canMove(int vectI, int charI, MovementDirection dir){
	if (!_locationWithinMapBounds(vectI, charI)){ // Validate requested location actually within bounds of map
		return false;
	}

	if (!_acceptableDestinationSquare(vectI, charI)){ // Validate requested location can be jumped to (AKA destination is not an obstruction)
		return false;
	}

	if (!_noObstacleInPath(vectI, charI, dir)){ // Looks for any obstacles in the direction of movement
		return false;
	}

	// If this point has been reached, then the Character is entirely allowed to move to this destination. Their new position will be set
	// and True will be returned.

	return true;
}

/**
* Confirms if the square the Character is trying to land on is an acceptable destination.
*<p>In other words, this method attempts to determine whether or not the destination is an obstruction.
*<p>Adds in functionality to make sure exit door is not valid!
*@param vectI index in the vector of the vertical position the character is moving to
*@param charI index in the string of the horizonal char the character is moving to
*@return bool, True if NOT an obstacle, False if IS an obstacle
*/
bool FriendlyStrategy::_acceptableDestinationSquare(int vectI, int charI){
	char posInQuestion = _theMap->at(vectI).at(charI);
	return(posInQuestion != SimplifiedMapSymbols::_ExitDoor_ && MovementStrategy::_acceptableDestinationSquare(vectI, charI));
}

/**
* Based on the current possition that the player is at, will generate a vector with all directions
* the monster should try moving, from best to worst.
* Starts with the 'primary' direction that the character is in, and then blooms out (ie if character is North, then should try North first,
* followed by NorthEast and NorthWest, then West and East, etc.)
*/
vector<MovementDirection>& FriendlyStrategy::_determinePlayerDirection(){
	vector<MovementDirection> *directionSequence = new vector<MovementDirection>();
	directionSequence->reserve(8);
	int vectDiff = _playerVectPos - _vectPos; // Difference in vector axis
	int charDiff = _playerCharPos - _charPos; // Different in char axis

	// Check player directly north : charDiff is 0 and vectDiff is NEGATIVE
	if ((charDiff == 0) && (vectDiff < 0)){
		directionSequence->push_back(North); // Primary direction is NORTH, so it will be added first
	}
	else

		// Check player directly south : charDiff is 0 and vectDiff is POSITIVE
	if ((charDiff == 0) && (vectDiff > 0)){
		directionSequence->push_back(South); // Primary direction is SOUTH, so it will be added first
	}
	else

		// Check moving east : vectDiff is 0 and charDiff is POSITIVE
	if ((vectDiff == 0) && (charDiff > 0)){
		directionSequence->push_back(East);
	}
	else

		// Check moving west : vectDiff is 0 and charDiff is NEGATIVE
	if ((vectDiff == 0) && (charDiff < 0)){
		directionSequence->push_back(West);
	}
	else {

		// We have now checked the four cardinal directions. If the player is not DIRECTLY in any of them,
		// we'll just have to do some math

		double opp = (double)charDiff;
		double adj = (double)vectDiff;
		double angle = atan(opp / adj);

		// Primary direction is north:
		if (abs(angle) < M_PI / 8 || vectDiff < 0)
			directionSequence->push_back(North);

		// Primary direction is NE:
		else if (abs(angle) >= M_PI / 8 && abs(angle) < 3 * M_PI / 8 && vectDiff < 0)
			directionSequence->push_back(NorthEast);

		// Primary direction is east:
		else if((abs(angle) >= 3 * M_PI / 8 && abs(angle < M_PI / 2 && vectDiff < 0) || (angle >= 3 * M_PI / 8 && angle < M_PI / 2 && vectDiff > 0)))
			directionSequence->push_back(East);

		// Primary direction is south-east
		else if(angle >= M_PI / 8 && angle < 3 * M_PI / 8 && vectDiff > 0)
			directionSequence->push_back(SouthEast);

		// Primary direction is south
		else if(abs(angle) < M_PI / 8 && vectDiff > 0)
			directionSequence->push_back(South);

		// Primary direction is south-west
		else if(abs(angle) >= M_PI / 8 && abs(angle) < 3 * M_PI / 8 && vectDiff > 0)
			directionSequence->push_back(SouthWest);

		// Primary Direction is west
		else if((abs(angle) >= 3 * M_PI / 8 && abs(angle < M_PI / 2 && vectDiff > 0) || (angle >= 3 * M_PI / 8 && angle < M_PI / 2 && vectDiff < 0)))
			directionSequence->push_back(West);

		// Primary direction is north-west
		else if(angle >= M_PI / 8 && angle < 3 * M_PI / 8 && vectDiff < 0)
			directionSequence->push_back(NorthWest);
	}

	// Now set all other directions in order
	switch (directionSequence->at(0)){
	case North:
		// Now, add NorthEast and NorthWest
		directionSequence->push_back(NorthEast);
		directionSequence->push_back(NorthWest);
		// Now add East and West
		directionSequence->push_back(East);
		directionSequence->push_back(West);
		// Finally, all southern directions
		directionSequence->push_back(SouthEast);
		directionSequence->push_back(SouthWest);
		directionSequence->push_back(South);
		return *directionSequence;
	case South:
		directionSequence->push_back(SouthEast);
		directionSequence->push_back(SouthWest);
		// Now add East and West
		directionSequence->push_back(East);
		directionSequence->push_back(West);
		// Finally, all northern directions
		directionSequence->push_back(NorthEast);
		directionSequence->push_back(NorthWest);
		directionSequence->push_back(North);
		return *directionSequence;
	case East:
		directionSequence->push_back(NorthEast);
		directionSequence->push_back(SouthEast);
		directionSequence->push_back(North);
		directionSequence->push_back(South);
		directionSequence->push_back(NorthWest);
		directionSequence->push_back(SouthWest);
		directionSequence->push_back(West);
		return *directionSequence;
	case West:
		directionSequence->push_back(NorthWest);
		directionSequence->push_back(SouthWest);
		directionSequence->push_back(North);
		directionSequence->push_back(South);
		directionSequence->push_back(NorthEast);
		directionSequence->push_back(SouthEast);
		directionSequence->push_back(East);
		return *directionSequence;
	case NorthEast:
		directionSequence->push_back(North);
		directionSequence->push_back(East);
		directionSequence->push_back(NorthWest);
		directionSequence->push_back(SouthEast);
		directionSequence->push_back(West);
		directionSequence->push_back(South);
		directionSequence->push_back(SouthWest);
		return *directionSequence;
	case SouthEast:
		directionSequence->push_back(South);
		directionSequence->push_back(East);
		directionSequence->push_back(NorthEast);
		directionSequence->push_back(SouthWest);
		directionSequence->push_back(North);
		directionSequence->push_back(West);
		directionSequence->push_back(NorthWest);
		return *directionSequence;
	case SouthWest:
		directionSequence->push_back(South);
		directionSequence->push_back(West);
		directionSequence->push_back(NorthWest);
		directionSequence->push_back(SouthEast);
		directionSequence->push_back(North);
		directionSequence->push_back(East);
		directionSequence->push_back(NorthEast);
		return *directionSequence;
	}

	// If this point is reached, something has gone wrong
	return *directionSequence;
}

/**
* Will be called any time a change has been made to the Player character. Will check if position has changed, and if it has,
* will then update in the Monster
*/
void FriendlyStrategy::Update(){
	if ((_sub->getVectPos() != _playerVectPos) || (_sub->getCharPos() != _playerCharPos)){
		_playerVectPos = _sub->getVectPos();
		_playerCharPos = _sub->getCharPos();
	}
}

/**
* Determines if the square the player is trying to jump to is within the player's range.
*@param vectI of desired location
*@param charI of desired location
*@return bool, True if destination is within range, False otherwise
*/
bool FriendlyStrategy::isWithinRange(int vectI, int charI){
	int absVectDiff = abs(vectI - _vectPos); // Absolute difference in vector axis
	int absCharDiff = abs(charI - _charPos); // Absolute difference in char axis
	// Check to make sure that any movement in vect and char axes is less than or equal to speed (irregardless of sign).
	if ((absVectDiff <= _speed) && (absCharDiff <= _speed)){
		return true;
	}

	// If greater than _speed, then character cannot move this far, so we return false
	return false;
}