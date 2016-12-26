/**
*@file userinputandstringmanager.h
*@brief Provides access to SingletonInputsAndStringManager class, used to manage input from the user
*/
#if !defined (USER_INPUT_AND_STRING_MANAGER_H)
#define USER_INPUT_AND_STRING_MANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "namespaces.h"
using namespace CampaignMaximums;
using namespace std;
/*!
*@class SingletonInputsAndStringManager
*singleton class designed to manages User Inputs and also manage string to char pointer and vice
*versa manipulation.
*/
class SingletonInputsAndStringManager
{
private:
	static SingletonInputsAndStringManager* _inputAndStringInstance;
	SingletonInputsAndStringManager();
public:
	int takeIntInput(std::string message, int min, int max);
	string takeStringInput(std::string message, int maxLength);
	string takeUniqueStringInput(std::string message, std::vector<std::string> alreadyIn);
	void assignStringToCharPointer(char* ptr, std::string thestring);
	string convertCharPointerToString(char* ptr);
	static SingletonInputsAndStringManager* getInstance();
	~SingletonInputsAndStringManager();
};

#endif