#pragma once
#include "GameLog.h"

class GameLog;

class MapController : public GameLog
{
private:
	MapController();
	static MapController* _mapController;
public:
	static MapController* getInstance();
	void log(string);
	~MapController();


};