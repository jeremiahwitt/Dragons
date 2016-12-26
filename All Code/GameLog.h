#pragma once
#include <iostream>
#include "fileIOmanager.h"


using namespace std;

class GameLog
{
protected:
	string _path;
	string _unifiedPath = SingletonFilePathAndFolderManager::getInstance()->_path_to_unifiedLog;
	bool _toggleGame;
	bool _toggleMap;
	bool _toggleCharacter;
	bool _toggleDice;
	//bool _toggleUnified;

public:
	string getPath(){ return _path; }
	string getUnifiedPath(){ return _unifiedPath; }
	bool getGameToggle(){ return _toggleGame; };
	bool getMapToggle(){ return _toggleMap; };
	bool getCharacterToggle(){ return _toggleCharacter; };
	bool getDiceToggle(){ return _toggleDice; };
	void toggleGame()
	{ 
		if (_toggleGame == true)
			_toggleGame = false;
		else
			_toggleGame = true;
	}
	void toggleMap()
	{
		if (_toggleMap == true)
			_toggleMap = false;
		else
			_toggleMap = true;
	}
	void toggleCharacter()
	{
		if (_toggleCharacter == true)
			_toggleCharacter = false;
		else
			_toggleCharacter = true;
	}
	void toggleDice()
	{
		if (_toggleDice == true)
			_toggleDice = false;
		else
			_toggleDice = true;
	}
	virtual void log(string);
	void clearLog();
};

