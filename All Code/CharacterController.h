#pragma once
#include "GameLog.h"
class GameLog;
class CharacterController : public GameLog
{
private:
	CharacterController();
	static CharacterController* _characterController;
public:
	static CharacterController* getInstance();
	void log(string);
	~CharacterController();


};