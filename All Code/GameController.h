#pragma once
#include "GameLog.h"
class GameLog;
class GameController : public GameLog
{
private:
	GameController();
	static GameController* _gameController;
public:
	static GameController* getInstance();
	void log(string);
	~GameController();


};