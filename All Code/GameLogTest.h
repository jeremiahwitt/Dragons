#include "DiceController.h"
#include "MapController.h"
#include "CharacterController.h"
#include "GameController.h"

struct GameLogTest{

	static int checkInput(int input, int ub)
	{
		while (cin.fail() || (input > ub && input < 0))
		{
			std::cout << "Not a valid option. Try again.\n";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> input;
		}

		return input;
	}

	static void gameLogTest()
	{
		std::cout << "Test for Game Log" << endl;

		int input;

		std::cout << "What would you like to do? (0: Exit)\n";
		std::cout << "1. Toggle Log\n2. View Log\n";
		cin >> input;

		input = checkInput(input,2);
		if (input == 0)
		{
			return;
		}
		else if (input == 1)
			toggleLog();

		else if (input == 2)
		{
			std::cout << "Which log to read? (0: EXIT)\n";
			std::cout << "1. Game\n2. Map\n3. Character\n4. Dice\n5. Unified\n";

			cin >> input;

			input = checkInput(input, 5);

			displayLogChanges(input);
		}
	
		int in2;
		std::cout << "Would you like to continue? (0: No) ";
		cin >> in2;
		while (cin.fail() || in2 != 0)
		{
			cin.clear();
			cin.ignore(256, '\n');
			gameLogTest();
		}
		
	}

	static void toggleLog()
	{
		std::cout << "Which log to toggle? (0: EXIT)\n";
		std::cout << "1. Game (" << boolToString(GameController::getInstance()->getGameToggle())<< ")" << std::endl;
		std::cout << "2. Map (" << boolToString(MapController::getInstance()->getMapToggle()) << ")" << std::endl;
		std::cout << "3. Character (" << boolToString(CharacterController::getInstance()->getCharacterToggle()) << ")" << std::endl;
		std::cout << "4. Dice (" << boolToString(DiceController::getInstance()->getDiceToggle()) << ")" << std::endl;
		int input;
		cin >> input;
		input = checkInput(input, 4);
		if (input != 0)
			toggling(input);
	}


	static string boolToString(bool b)
	{
		return b ? "ON" : "OFF";
	}


	static void toggling(int input)
	{
		string log;
		string toggle;
		switch (input)
		{
		case 1:
			log = "Game";
			GameController::getInstance()->toggleGame();
			toggle = boolToString(GameController::getInstance()->getGameToggle());
			break;
		case 2:
			log = "Map";
			MapController::getInstance()->toggleMap();
			toggle = boolToString(MapController::getInstance()->getMapToggle());
			break;
		case 3:
			log = "Character";
			CharacterController::getInstance()->toggleCharacter();	
			toggle = boolToString(CharacterController::getInstance()->getCharacterToggle());
			break;
		case 4:
			log = "Dice";
			DiceController::getInstance()->toggleDice();
			toggle = boolToString(DiceController::getInstance()->getDiceToggle());
			break;
		}

		std::cout << log << " is now toggled " << toggle << "!\n";
		std::system("pause");
	}


	static void displayLogChanges(int input)
	{
		string log;
		vector<string> lines;
		switch (input)
		{
		case _GameLog_:
			log = "Game";
			lines = SingletonInputOutputManager::getInstance()->readFileLineByLine(GameController::getInstance()->getPath());
			break;
		case _MapLog_:
			log = "Map";
			lines = SingletonInputOutputManager::getInstance()->readFileLineByLine(MapController::getInstance()->getPath());
			break;
		case _CharacterLog_:
			log ="Character";
			lines = SingletonInputOutputManager::getInstance()->readFileLineByLine(CharacterController::getInstance()->getPath());
			break;
		case _DiceLog_:
			log = "Dice";
			lines = SingletonInputOutputManager::getInstance()->readFileLineByLine(DiceController::getInstance()->getPath());
			break;
		case _UnifiedLog_: 
			log = "Unified";
			lines = SingletonInputOutputManager::getInstance()->readFileLineByLine(DiceController::getInstance()->getUnifiedPath());
			break;
		case _ReturnToGame_: 
			return;
		}
		
		std::system("CLS");

		std::cout << log << " Controller log: \n";
		for (int i = 0; i < lines.size(); i++)
			std::cout << lines[i] << endl;

		std::cout << "End of File.\n";
		std::system("pause");
	}
};