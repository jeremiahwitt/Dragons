/**
*@file FighterOnMapView.h
*@brief Provides definition of FighterOnMapView class, which will be used to render the Human Playable Character
*/
#pragma once
#include "CharacterObserver.h"
#ifndef FIGHTERONMAPVIEW_H
#define FIGHTERONMAPVIEW_H

class PreBuiltLevel;

/**
*@class FighterOnMapView
*@brief FighterOnMapView allows rendering of the Fighter character on the map, ensuring that any changes to its position
* are displayed to the user during play.
*<p> FighterOnMapView will ensure that the Character's position on the map gets updated correctly.
*/
class FighterOnMapView : public CharacterObserver {
protected:
	int _prevVectPos; //! The last known vector position of the Player
	int _prevCharPos; //! The last known char position of the Player
	PreBuiltLevel* _theMap; //! The Level that the game is being played on
public:
	FighterOnMapView(Characters* myChar, PreBuiltLevel* theMap);
	~FighterOnMapView() {};
	virtual void Update();
};

#endif