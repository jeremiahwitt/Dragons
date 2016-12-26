#pragma once
#include <cppunit\CompilerOutputter.h>
#include <cppunit\extensions\TestFactoryRegistry.h>
#include <cppunit\ui\text\TestRunner.h>
#include "game_loops.h"
/*!
* Advance Program design with C++, COMP 345
* Dungeons and Dragons game final demonstration
* Program developed by:
*	Jeremiah
*	Sabin
*	Andres
*	Phil
*	Khatib Tamal
* Course Instructor: Dr Mohammed Taleb
* Program Submission Date: 1st December 2016
*/
int main(int argc, char** argv)
{
	std::cout << "CONCORDIA UNIVERSITY DEPARTMENT OF ENGINEERING AND COMPUTER SCIENCE" << std::endl<<std::endl;
	std::cout << "Advanced Program Design with C++: COMP345" << std::endl;
	std::cout << "Dungeons and Dragons game final demonstration" << std::endl;
	std::cout << "Program Submission Date: 1st December 2016" << std::endl;
	std::cout << "Game developed by: Jeremiah, Sabin, Andres, Phil, Khatib." << std::endl;
	std::cout << "Course Instructor: Dr Mohammed Taleb" << std::endl << std::endl;
	int success = 0;

	std::cout << "Running CPP Unit Test." << std::endl;

	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();


	// Return error code 1 if the one of test failed.
	success = wasSucessful ? 0 : 1;
	if (success == 1)
	{
		std::cout << "cpp unit test failed exiting program with code: " << success << std::endl;
		getch();
		return success;
	}
	std::cout << "CPP unit test successful\n\n." << std::endl;
	std::cout << "press any key to continue with demonstration." << std::endl;
	getch();
	system("cls");

	//! my gameloops class our project driver, therefore we are not driving the demonstration from main
	GameLoops* gl = new GameLoops();
	gl->loopManager();
	system("cls");

	delete gl;
	gl = nullptr;

	std::cout << "Program executed successfully, exiting with code: " << success << std::endl;
	system("pause");
	return success;
}
