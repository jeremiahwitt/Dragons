#include "GameLog.h"	


void GameLog::log(string input)
{
		SingletonInputOutputManager::getInstance()->appendToFile(_unifiedPath, input);
}

void GameLog::clearLog()
{
	SingletonInputOutputManager::getInstance()->clearFile(_path);
	SingletonInputOutputManager::getInstance()->clearFile(_unifiedPath);
}