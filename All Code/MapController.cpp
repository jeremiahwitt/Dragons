#include "MapController.h"
#include "filepathandfoldermanager.h"

MapController* MapController::_mapController = nullptr;

MapController::MapController()
{
	_path = SingletonFilePathAndFolderManager::getInstance()->_path_to_mapController;
	SingletonInputOutputManager::getInstance()->clearFile(_path);
	_toggleMap = true;
}

void MapController::log(string input)
{
	if (this->_toggleMap == true)
	{
		//log for game controller
		SingletonInputOutputManager::getInstance()->appendToFile(_path, input);
		//log for unified by calling parent log
		GameLog::log(input);
	}
}

MapController* MapController::getInstance()
{
	if (_mapController == nullptr)
		_mapController = new MapController();
	return _mapController;
}

MapController::~MapController()
{
	delete _mapController;
	_mapController = nullptr;
}