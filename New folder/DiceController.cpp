#include "DiceController.h"

DiceController* DiceController::_diceController = nullptr;

DiceController::DiceController()
{
	_path = SingletonFilePathAndFolderManager::getInstance()->_path_to_diceController;
	SingletonInputOutputManager::getInstance()->clearFile(_path);
	_toggleDice = true;
}

void DiceController::log(string input)
{
	if (this->_toggleDice == true)
	{
		//log for game controller
		SingletonInputOutputManager::getInstance()->appendToFile(_path, input);
		//log for unified by calling parent log
		GameLog::log(input);
	}
}

DiceController* DiceController::getInstance()
{
	if (_diceController == nullptr)
		_diceController = new DiceController();
	return _diceController;
}

DiceController::~DiceController()
{
	delete _diceController;
	_diceController = nullptr;
}

