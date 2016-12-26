/**
*@file MonsterOnMapView.h
*@brief Provides definition of MonsterOnMapView class, which will be used to render Monsters on the map
*/
#pragma once
#include "CharacterObserver.h"
#ifndef MONSTERONMAPVIEW_H
#define MONSTERONMAPVIEW_H

class PreBuiltLevel;
/**
*@class MonsterOnMapView
*@brief MonsterOnMapView allows rendering of the Monsters on the map, ensuring that any changes to their position
* are displayed to the user during play.
*<p> Monster OnMapView will ensure that the Monster's position on the map gets updated correctly.
*/
class MonsterOnMapView : public CharacterObserver {
protected:
	int _prevVectPos; //! The last known vector position of the Monster
	int _prevCharPos; //! The last known char position of the Monster
	PreBuiltLevel* _theMap; //! The Level that the game is being played on
	CharacterType _theType; //! The type of the Character
	void renderDead();
public:
	MonsterOnMapView(Characters* myChar, PreBuiltLevel* theMap, CharacterType theirType);
	~MonsterOnMapView() {};
	virtual void Update();
};

#endif