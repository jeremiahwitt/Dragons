#pragma once
#include "GameLog.h"

class GameLog;

class DiceController : public GameLog
{
private:
	DiceController();
	static DiceController* _diceController;
public:
	static DiceController* getInstance();
	void log(string);
	~DiceController();


};