/**
*@file HumanPlayerStrategy.cpp
*@brief Implementation of the HumanPlayerStrategy class
*/

#include "HumanPlayerStrategy.h"
#include <iostream>
#include "gameplayengine.h"
#include "prebuiltlevel.h"

HumanPlayerStrategy::HumanPlayerStrategy(int speed) : MovementStrategy(speed){}

/**
* Allows the user to choose which direction they want to move in. Checks the direction the player wants to go
* to see if it is valid. If it is valid, the player is moved to there
*/
bool HumanPlayerStrategy::move(PreBuiltLevel* level, SDL_Rect *currentGrid, GamePlayEngine* engine){
	_theMap = level->getMapSimplePtrVersion();
	SDL_Rect dest;
	int mouseIndex = 0;
	std::vector<std::string> temp = level->getMapStringVersiion();
	currentGrid = &engine->checkMousePosition(level->getGameplayGridsRects(), &mouseIndex);
	int charIndex = currentGrid->x / level->getLevelWindow()->getGridX_Length();
	int vectorIndex = currentGrid->y / level->getLevelWindow()->getGridY_Length();
	bool canMove = move(vectorIndex, charIndex);


	if (canMove)
	{
		if ((engine->getEvent()->type == SDL_MOUSEBUTTONDOWN) && (engine->getEvent()->button.button == SDL_BUTTON_LEFT))
		{
			string message = level->getPlayer()->getName() + " has moved from (X: " + to_string(_charPos) + " Y: " + to_string(_vectPos) + ")";
			message += " to (X: " + to_string(vectorIndex) + " Y: " + to_string(charIndex) + ").";
			MapController::getInstance()->log(message);
			// Update the Character position
			_vectPos = vectorIndex;
			_charPos = charIndex;
			_recentGrid = currentGrid;
			
			// Set true if Character has reached exit
			if ((vectorIndex == engine->_exitStringIndex) && (charIndex == engine->_exitCharacterIndex))
			{
				engine->_mapExit = true;
			}
			return true;
			}
		} 
	return false;
}
	

/**
* Allows the player to attempt to move to a new location on the map.
*<p> First, checks if the location is within the bounds of the map.
*<p> Second, checks if the location is within the range of the player. (Not applicable for this assignment, but required for the way
* movement is implemented in my group project).
*<p> Third, checks to see if the destination can be landed on.
*<p> Fourth, checks if the direction the player is going in is valid (again, not applicable for here but required for group project).
*<p> Last, checks if there are any obstacles in the path.
*@param vectI index in the vector the Player is attempting to move to
*@param charI index in the string the Player is attempting to move to
*@return bool, True if the player can move to this new location, False otherwise
*/
bool HumanPlayerStrategy::move(int vectI, int charI){
	MovementDirection attemptedDirection = Invalid; // Will be used later in algorithm

	if (!_locationWithinMapBounds(vectI, charI)){ // Validate requested location actually within bounds of map
		cout << "In here1" << endl;
		return false;
	}

	if (!isWithinRange(vectI, charI)){ // Validate requested location is within player range
		cout << "In here2" << endl;
		return false;
	}

	if (!_acceptableDestinationSquare(vectI, charI)){ // Validate requested location can be jumped to (AKA destination is not an obstruction)
		cout << "In here3" << endl;
		return false;
	}

	attemptedDirection = _determineMovementDirection(vectI, charI); // Determine direction of jump
	if (attemptedDirection == Invalid){ // If direction is invalid, return false
		cout << "In here4" << endl;
		return false;
	}

	if (!_noObstacleInPath(vectI, charI, attemptedDirection)){ // Looks for any obstacles in the direction ove movement
		cout << "In here5" << endl;
		return false;
	}

	// If this point has been reached, then the Character is entirely allowed to move to this destination. Their new position will be set
	// and True will be returned.

	return true;
}

/**
* Determines if the square the player is trying to jump to is within the player's range.
*@param vectI of desired location
*@param charI of desired location
*@return bool, True if destination is within range, False otherwise
*/
bool HumanPlayerStrategy::isWithinRange(int vectI, int charI){
	int absVectDiff = abs(vectI - _vectPos); // Absolute difference in vector axis
	int absCharDiff = abs(charI - _charPos); // Absolute difference in char axis

	// Check to make sure that any movement in vect and char axes is less than or equal to speed (irregardless of sign).
	if ((absVectDiff <= _speed) && (absCharDiff <= _speed)){
		return true;
	}

	// If greater than _speed, then character cannot move this far, so we return false
	return false;
}

/**
* Used to determine which cardinal direction the player is trying to move in.
*<p>Given that the system cannot know exactly which direction the player is moving in when they select a destination,
*   it must mathematically calculate what the player is trying to do. This function will analyze the requested destination
*   in relation to the Character's current position. It will then return the direction the player is trying to move in,
*   or 'Invalid' if this is not one of the allowed directions.
*@param vectI vector index of destination square
*@param charI char index of destination square
*@return MovementDirection, enum value representing which way the player is trying to go
*/
MovementDirection HumanPlayerStrategy::_determineMovementDirection(int vectI, int charI){

	int vectDiff = vectI - _vectPos; // Difference in vector axis
	int charDiff = charI - _charPos; // Difference in char axis

	// Check moving north : charDiff is 0 and vectDiff is NEGATIVE
	if ((charDiff == 0) && (vectDiff < 0)){
		return North;
	}

	// Check moving south : charDiff is 0 and vectDiff is POSITIVE
	if ((charDiff == 0) && (vectDiff > 0)){
		return South;
	}

	// Check moving east : vectDiff is 0 and charDiff is POSITIVE
	if ((vectDiff == 0) && (charDiff > 0)){
		return East;
	}

	// Check moving west : vectDiff is 0 and charDiff is NEGATIVE
	if ((vectDiff == 0) && (charDiff < 0)){
		return West;
	}

	// If we have reached this point, then we are either moving diagonally or an invalid direction.
	// To reduce extra comparisons, we will immediately check if abs(vectDiff) == abs(charDiff). We will
	// return invalid if this is not true, as it means we are not moving in an accepted direction no matter what.
	if (abs(vectDiff) != abs(charDiff)){
		return Invalid;
	}

	// Check moving north-east : vectDiff is NEGATIVE, charDiff is POSITIVE
	if ((vectDiff < 0) && (charDiff > 0)){
		return NorthEast;
	}

	// Check moving south-east : vectDiff is POSITIVE, charDiff is POSITIVE
	if ((vectDiff > 0) && (charDiff > 0)){
		return SouthEast;
	}

	// Check moving south-west : vectDiff is POSITIVE, charDiff is NEGATIVE
	if ((vectDiff > 0) && (charDiff < 0)){
		return SouthWest;
	}

	// Check moving north-west: vectDiff is NEGATIVE, charDiff is NEGATIVE
	if ((vectDiff < 0) & (charDiff < 0)){
		return NorthWest;
	}

	// If we have reached here, somehow the character is doing something wrong so invalid is returned
	return Invalid;
}