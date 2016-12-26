/**
*@file MonsterOnMapView.cpp
*@brief Provides implementation of MonsterOnMapView methods, which ensure that any Monster movements lead to
* updates of the map
*/

#include "MonsterOnMapView.h"
#include "PreBuiltLevel.h"

/**
* Parameterized Constructor. Ensures that the tracking of the Monsters's position is set up properly.
* Also ensures that the pointer to the Level is set, which will be used to help updating the map
*/
MonsterOnMapView::MonsterOnMapView(Characters* theChar, PreBuiltLevel* theMap, CharacterType theirType) : CharacterObserver(theChar) {
	_theType = theirType;
	_prevVectPos = _sub->getVectPos();
	_prevCharPos = _sub->getCharPos();
	_theMap = theMap;
}

/**
* Method which indicates to the Observer that an update has been made. Will update the Fighter's position on the Map
*/
void MonsterOnMapView::Update(){

	// If the type has changed, we will need to re-render with the appropriate new symbol
	if (dynamic_cast<Monster*>(_sub)->getCharType() != _theType){
		_theType = dynamic_cast<Monster*>(_sub)->getCharType();
	}

	SDL_Rect dest;
	SDL_Rect currentGrid;
	std::vector<std::string> temp = _theMap->getMapStringVersiion();
	if (_sub->getIsDead()){
		this->renderDead();
	}
	else {
		//first render player to floor
		//make the coordinate in map a free path
		//this->_level->getMapStringVersiion()[y].at(x) = SimplifiedMapSymbols::_FreePath_;
		for (int k = 0; k < _theMap->getEnvironmentComponents().size(); k++)
		{
			//render the floor
			if (_theMap->getEnvironmentComponents()[k]->getComponentName() == "floor")
			{
				dest.x = _prevCharPos*_theMap->getLevelWindow()->getGridX_Length();
				dest.y = _prevVectPos*_theMap->getLevelWindow()->getGridY_Length();
				dest.h = _theMap->getLevelWindow()->getGridY_Length();
				dest.w = _theMap->getLevelWindow()->getGridX_Length();

				//now update the environment for the observer
				_theMap->_environmentForObserver = _theMap->getEnvironmentComponents()[k];

				//make the x y of loop a free path
				temp[_prevVectPos].at(_prevCharPos) = _theMap->getEnvironmentComponents()[k]->getComponentChar();
				_theMap->setMainMapVector(temp);
				goto DONE_FLOOR;
			}

		}//done putting player to floor
		DONE_FLOOR:

		// Now set the grid for the update
		currentGrid.x = _sub->getCharPos()*_theMap->getLevelWindow()->getGridX_Length();
		currentGrid.y = _sub->getVectPos()*_theMap->getLevelWindow()->getGridY_Length();
		currentGrid.h = _theMap->getLevelWindow()->getGridY_Length();
		currentGrid.w = _theMap->getLevelWindow()->getGridX_Length();

		// Update map and set new position!
		if (_theType == Aggressor){
			temp[_sub->getVectPos()].at(_sub->getCharPos()) = SimplifiedMapSymbols::_Enemies_;
			_theMap->setRecentUpdateFlag(Enemy);
		}
		else { //!! NEED TO UPDATE SO THAT DISPLAYS FRIENDLY TO MAP
			temp[_sub->getVectPos()].at(_sub->getCharPos()) = SimplifiedMapSymbols::_Friend_;
			_theMap->setRecentUpdateFlag(Nice);
		}
			//temp[_sub->getVectPos()].at(_sub->getCharPos()) = SimplifiedMapSymbols::_Friendly_;

		_prevVectPos = _sub->getVectPos();
		_prevCharPos = _sub->getCharPos();
		_theMap->setMainMapVector(temp);

		//update the two destination rectangles in subject
		_theMap->setDestRectsForObserver(dest, currentGrid);

		//call the observer update and render and display, also lets all LevelObservers know the level has changed
		_theMap->Notify();
	}
}

void MonsterOnMapView::renderDead(){
	SDL_Rect dest;
	SDL_Rect currentGrid;
	std::vector<std::string> temp = _theMap->getMapStringVersiion();

	//first render player to floor
	//make the coordinate in map a free path
	//this->_level->getMapStringVersiion()[y].at(x) = SimplifiedMapSymbols::_FreePath_;
	for (int k = 0; k < _theMap->getEnvironmentComponents().size(); k++)
	{
		//render the floor
		if (_theMap->getEnvironmentComponents()[k]->getComponentName() == "floor")
		{
			dest.x = _prevCharPos*_theMap->getLevelWindow()->getGridX_Length();
			dest.y = _prevVectPos*_theMap->getLevelWindow()->getGridY_Length();
			dest.h = _theMap->getLevelWindow()->getGridY_Length();
			dest.w = _theMap->getLevelWindow()->getGridX_Length();

			//now update the environment for the observer
			_theMap->_environmentForObserver = _theMap->getEnvironmentComponents()[k];

			//make the x y of loop a free path
			temp[_prevVectPos].at(_prevCharPos) = _theMap->getEnvironmentComponents()[k]->getComponentChar();
			_theMap->setMainMapVector(temp);
		}

	}//done putting player to floor

	// Now set the grid for the update
	currentGrid.x = _sub->getCharPos()*_theMap->getLevelWindow()->getGridX_Length();
	currentGrid.y = _sub->getVectPos()*_theMap->getLevelWindow()->getGridY_Length();
	currentGrid.h = _theMap->getLevelWindow()->getGridY_Length();
	currentGrid.w = _theMap->getLevelWindow()->getGridX_Length();

	// Here, we can either indicate to the MapObserver that we are updatting with a Dead character, in which case we only render the environment
	// and no other assets. Then outside of here we manage adding the new Container

	//_theMap->setRecentUpdateFlag(Dead); TEMP if we go with option above

	//  OR we Create some sort of new Container that gets placed at the same location in the map, inserted into ContainersOnMap vector, then setup
	// a new Observer for it. Its constructor will need to know the position right off the bat so that it can edit the level and notify MapObserver
	// with the correct flag, in order to have the new container rendered to screen.


	_theMap->setRecentUpdateFlag(Dead);
	temp[_prevVectPos].at(_prevCharPos) = SimplifiedMapSymbols::_BasicContainer_;
	_theMap->setMainMapVector(temp);
	
	//update the two destination rectangles in subject
	_theMap->setDestRectsForObserver(dest, currentGrid);

	//call the observer update and render and display, also lets all LevelObservers know the level has changed
	_theMap->Notify();
}