//!@file userinputandstringmanager.cpp
//!@brief Provides implementation of SingletonInputsAndStringManager class
#include "userinputandstringmanager.h"

//!singleton static instance variable
SingletonInputsAndStringManager* SingletonInputsAndStringManager::_inputAndStringInstance = nullptr;

//!returns singleton instance, creates new already not already created
SingletonInputsAndStringManager* SingletonInputsAndStringManager::getInstance()
{
	if(SingletonInputsAndStringManager::_inputAndStringInstance == nullptr)
		SingletonInputsAndStringManager::_inputAndStringInstance = new SingletonInputsAndStringManager();
	return SingletonInputsAndStringManager::_inputAndStringInstance;
}

//!private default constructor
SingletonInputsAndStringManager::SingletonInputsAndStringManager()
{
}

//!take an integer input within given range
int SingletonInputsAndStringManager::takeIntInput(std::string message, int min, int max)
{
	int temp = min-1;
	std::cout<<message.c_str();

	while(temp<min || temp>max)
	{
		while(!(cin >> temp))
		{
			std::cout<<"Please input a valid integer.\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		if(temp<min || temp>max)
			std::cout<<"Please input a number between "<<min<<" and "<<max<<endl;
	}
	return temp;
}

//!take string input of a maximum length
string SingletonInputsAndStringManager::takeStringInput(std::string message, int maxLength)
{
	string temp = "";
	std::cout<<message.c_str();
	bool exit = false;

	while(exit==false)
	{
		cin>>temp;
		if(temp.length()<1 || temp.length()>maxLength)
		{
			std::cout<<"Please input a string of length between 1 and "<<maxLength<<endl;
		}
		else
		{
			exit = true;
		}
	}
	return temp;
}

//! take a string input that is unique, or that is not already in based on the vector of strings already passed
string SingletonInputsAndStringManager::takeUniqueStringInput(std::string message, std::vector<std::string> alreadyIn)
{
	string temp = "";
	bool exit = false;

	while(exit==false)
	{
		temp = takeStringInput(message, _MaximumNameStringSize_);
		if(alreadyIn.size() == 0)
			exit = true;
		for(int x=0; x<alreadyIn.size(); x++)
		{
			if(temp == alreadyIn[x])
				std::cout<<"The name "<<temp<<" already exists in our databse, please enter a unique name."<<std::endl;
			else
				exit = true;
		}
	}
	return temp;
}

//!assigns a string passed to the char pointer passed
void SingletonInputsAndStringManager::assignStringToCharPointer(char* ptr, std::string thestring)
{
	int x=0;
	char temp;
	for(x=0; x<thestring.length(); x++)
	{
		ptr[x] = thestring.at(x);
	}
	
	ptr[x] = '\0';
}

//!converts the chars in the in char pointer, creates a string and returns it
string SingletonInputsAndStringManager::convertCharPointerToString(char* ptr)
{
	string temp = "";
	while(*ptr != '\0')
	{
		temp = temp + *ptr;
		ptr++;
	}
	return temp;
}

//!destructor just destroys the singleton instance
SingletonInputsAndStringManager::~SingletonInputsAndStringManager()
{
	delete SingletonInputsAndStringManager::_inputAndStringInstance;
	SingletonInputsAndStringManager::_inputAndStringInstance = nullptr;
}