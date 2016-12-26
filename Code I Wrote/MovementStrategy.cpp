/**
*@file MovementStrategy.cpp
*@brief Implementation of concrete methods shared by all Strategies
*/
#include "MovementStrategy.h"
#include "prebuiltlevel.h"
#include "gameplayengine.h"

/**
* Sets the map of the Strategy so that it can reference what locations are, and are not, accessible.
* @param newMap vector of strings with obstacles indicated
*/
void MovementStrategy::setMap(vector<string> *newMap){
	vector<string>* temp = NULL;
	// Check to see if _theMap is not NULL. If it is not, then delete old map
	if (_theMap != NULL) {
		temp = _theMap;
	}

	// Will make _theMap a new vector using the vector copy constructor
	_theMap = new vector<string>(*newMap);
	delete temp;
}

/**
* Default Constructor - Creates a movement strategy with a null map
*/
MovementStrategy::MovementStrategy(){
	_theMap = NULL;
}

/**
* Creates a movement strategy with the speed provided and a null map.
*/
MovementStrategy::MovementStrategy(int speed){
	_theMap = NULL;
	_speed = speed;
}

/**
* Sets the position being tracked by the Movement Strategy.
*/
void MovementStrategy::setPosition(int vectI, int charI){
	_vectPos = vectI;
	_charPos = charI;
}

void MovementStrategy::logMoveAttempt(int vectI, int charI, GamePlayEngine *engine){
	string message = dynamic_cast<Monster*>(engine->getCurrentMovingMonster())->getName() + " has moved from (X: " + to_string(_charPos) + " Y: " + to_string(_vectPos) + ")";
	message += " to (X: " + to_string(charI) + " Y: " + to_string(vectI) + ").";
	MapController::getInstance()->log(message);

	// Now log for CharacterCOntroller
	message = dynamic_cast<Monster*>(engine->getCurrentMovingMonster())->getName() + " has moved.";
	CharacterController::getInstance()->log(message);
}

/**
* Confirms if the location the Character is trying to move to is within the bounds of the map.
*@param vectI integer representing the index within the vector
*@param charI integer representing the char index within the string
*/
bool MovementStrategy::_locationWithinMapBounds(int vectI, int charI){

	// Check to see if move will go outside of the map's vertical
	if (vectI < 0 || vectI >= _theMap->size()){
		return false;
	}
	// Check to see if move will go outside of the map's horizontal bounds
	else if (charI < 0 || charI >= _theMap->at(0).size()){
		return false;
	}

	// If this point has been reached, then the Character is moving to a location within the map's bounds
	return true;
}

/**
* Confirms if the square the Character is trying to land on is an acceptable destination.
*<p>In other words, this method attempts to determine whether or not the destination is an obstruction.
*@param vectI index in the vector of the vertical position the character is moving to
*@param charI index in the string of the horizonal char the character is moving to
*@return bool, True if NOT an obstacle, False if IS an obstacle
*/
bool MovementStrategy::_acceptableDestinationSquare(int vectI, int charI){
	// Retrieve the position to be analyzed
	char posInQuestion = _theMap->at(vectI).at(charI);

	// Check if position is an obstruction
	if (posInQuestion == SimplifiedMapSymbols::_Obstruction_)
		return false;

	// Check if position is a container
	if (posInQuestion == SimplifiedMapSymbols::_BasicContainer_)
		return false;
	// Check if position is an enemy
	if (posInQuestion == SimplifiedMapSymbols::_Enemies_)
		return false;
	if (posInQuestion == SimplifiedMapSymbols::_Player_)
		return false;
	if (posInQuestion == SimplifiedMapSymbols::_Friend_)
		return false;

	// If position is none of these things, then the player can theoretically stand on this square
	return true;
}

/**
* Will be used to determine if there are any obstacles in the path between where the Character is currently
* and their destination.
*@param vectI the vector index of the destination square
*@param charI the character index of the destination square
*@param dir MovementDirection representing which way the character is trying to move
*@return bool True if there are no obstacles, false otherwise
*/
bool MovementStrategy::_noObstacleInPath(int vectI, int charI, MovementDirection dir){
	int dist = abs(charI - _charPos); // Will be used for diagonal movement
	switch (dir){
	case North:
		// Will start at square directly north of Character and continue until we get to destination
		for (int i = _vectPos - 1; i > vectI; --i) {
			// Will determine if each square the character is trying to move to can be landed on.
			// Destination does not have to be verified, as this is done already
			if (!_acceptableDestinationSquare(i, _charPos)) {
				return false;
			}
		}
		return true;
	case South:
		// Will start at square directly south of Character and continue until we get to destination
		for (int i = _vectPos + 1; i < vectI; ++i) {
			// Will determine if each square the character is trying to move to can be landed on.
			// Destination does not have to be verified, as this is done already
			if (!_acceptableDestinationSquare(i, _charPos)) {
				return false;
			}
		}
		return true;
	case East:
		// Will start at square directly east of Character and continue until we reach the destination
		for (int i = _charPos + 1; i < charI; ++i){
			// WIll determine if the current square in the path is valid
			if (!_acceptableDestinationSquare(_vectPos, i)) {
				return false;
			}
		}
		return true;
	case West:
		// Will start at square directly west of Character and continue until we reach the destination
		for (int i = _charPos - 1; i > charI; --i){
			// WIll determine if the current square in the path is valid
			if (!_acceptableDestinationSquare(_vectPos, i)) {
				return false;
			}
		}
		return true;
	case NorthEast:
		// Start at square directly north-east of Character and continue until destination
		for (int i = 1; i < dist; ++i){
			// Will determine if current square in path is valid
			if (!_acceptableDestinationSquare(_vectPos - i, _charPos + i)) {
				return false;
			}
		}
		return true;
	case SouthEast:
		// Start at square directly south-east of Character and continue until destination
		for (int i = 1; i < dist; ++i){
			// Will determine if current square in path is valid
			if (!_acceptableDestinationSquare(_vectPos + i, _charPos + i)) {
				return false;
			}
		}
		return true;
	case SouthWest:
		// Start at square directly south-east of Character and continue until destination
		for (int i = 1; i < dist; ++i){
			// Will determine if current square in path is valid
			if (!_acceptableDestinationSquare(_vectPos + i, _charPos - i)) {
				return false;
			}
		}
		return true;
	case NorthWest:
		// Start at square directly south-east of Character and continue until destination
		for (int i = 1; i < dist; ++i){
			// Will determine if current square in path is valid
			if (!_acceptableDestinationSquare(_vectPos - i, _charPos - i)) {
				return false;
			}
		}
		return true;
	default:
		return false;
	}
	// If this point has been reached, something has seriously gone wrong so False is returned
	return false;
}

/**
* Will return the vector position of the strategy
*/
int MovementStrategy::getVectPos(){
	return _vectPos;
}

/**
* Will return the char position of the strategy
*/
int MovementStrategy::getCharPos(){
	return _charPos;
}