/**
*@file FighterOnMapView.cpp
*@brief Provides implementation of FighterOnMapView methods, which ensure that any Fighter movements lead to
* updates of the map
*/

#include "FighterOnMapView.h"
#include "PreBuiltLevel.h"

/**
* Parameterized Constructor. Ensures that the tracking of the Character's position is set up properly.
* Also ensures that the pointer to the Level is set, which will be used to help updating the map
*/
FighterOnMapView::FighterOnMapView(Characters* theChar, PreBuiltLevel* theMap) : CharacterObserver(theChar) {
	_prevVectPos = _sub->getVectPos();
	_prevCharPos = _sub->getCharPos();
	_theMap = theMap;
}

/**
* Method which indicates to the Observer that an update has been made. Will update the Fighter's position on the Map
*/
void FighterOnMapView::Update(){
	SDL_Rect dest;
	SDL_Rect currentGrid;
	std::vector<std::string> temp = _theMap->getMapStringVersiion();
	if (_sub->getIsDead()){
		// ENTER WHAT TO DO IF CHARACTER DIES
		cout << "The fighter has DIED!" << endl;
	} else {
		//first render player to floor
		//make the coordinate in map a free path
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
		temp[_sub->getVectPos()].at(_sub->getCharPos()) = SimplifiedMapSymbols::_Player_;
		_prevVectPos = _sub->getVectPos();
		_prevCharPos = _sub->getCharPos();
		_theMap->setMainMapVector(temp);

		//update the two destination rectangles in subject
		_theMap->setDestRectsForObserver(dest, currentGrid);

		//call the observer update and render and display, also lets all LevelObservers know the level has changed
		_theMap->setRecentUpdateFlag(ThePlayer);
		_theMap->Notify();
	}
}
