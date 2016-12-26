//! @file TestDice.cpp
//! @brief This file provides an implementation for the TestDice class, in order to test using CppUnit. 
//!
#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "Dice.h"
using namespace CppUnit;
using namespace std;

/**
* TestDice is the test class for the Dice class.
*/
class TestDice : public CppUnit::TestFixture {

	// Test suite definition for TestDice
	CPPUNIT_TEST_SUITE(TestDice);

	// My test cases
	CPPUNIT_TEST(testValidDice); // Will test to make sure that only 4, 6, 8, 10, 12, 20 and 100 are allowed for dice values
	CPPUNIT_TEST(testNegativeNumberOfDice);	// tests to make sure that negative numbers of dice (ie -2d6) cannot be rolled
	CPPUNIT_TEST(testDiceLowerBound);	// Will test to make sure that the minimum value is the number of dice rolled (ie, 6 dice rolls have minimum 6)

	// Predefined Test Cases
	CPPUNIT_TEST(testDiceRollInputValidity); //test the validity of the input string
	CPPUNIT_TEST(testDiceRollingBounds); //test the upper bound of the returned value 
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp(void);
	void tearDown(void);

protected:
	void testValidDice(void);
	void testNegativeNumberOfDice(void);
	void testDiceRollInputValidity(void);
	void testDiceRollingBounds(void);
	void testDiceLowerBound(void);
private:

	Dice myDice;

};

//! Regstration for test cases in CppUnit
CPPUNIT_TEST_SUITE_REGISTRATION(TestDice);

/**
* This test will go through and ensure that all members of _VALID_DICE are, in fact, considered to be valid.
* It will test all values between 0 to 100. Any value that should be a member of _VALID_DICE is asserted to be true,
* while all other values are asserted to be false.
*/
void TestDice::testValidDice(void) {
	for (int i = -10; i <= 100; i++) {
		switch (i) {
		case 4:
			CPPUNIT_ASSERT(myDice._validDie(i));
			break;
		case 6:
			CPPUNIT_ASSERT(myDice._validDie(i));
			break;
		case 8:
			CPPUNIT_ASSERT(myDice._validDie(i));
			break;
		case 10:
			CPPUNIT_ASSERT(myDice._validDie(i));
			break;
		case 12:
			CPPUNIT_ASSERT(myDice._validDie(i));
			break;
		case 20:
			CPPUNIT_ASSERT(myDice._validDie(i));
			break;
		case 100:
			CPPUNIT_ASSERT(myDice._validDie(i));
			break;
		default:
			CPPUNIT_ASSERT(!myDice._validDie(i));
		}
	}
}

/**
* This test will ensure that negative multipliers, or in other words negative numbers
* of dice, cannot be rolled.
*/
void TestDice::testNegativeNumberOfDice(void) {
	CPPUNIT_ASSERT(-1 == myDice.roll("-2d6[+12]"));
	CPPUNIT_ASSERT(-1 == myDice.roll("-34d6[+12]"));
	CPPUNIT_ASSERT(-1 == myDice.roll("-43d6[+12]"));
	CPPUNIT_ASSERT(-1 == myDice.roll("-29d6[+12]"));
}

/**
* This test ensures that the minimal value returned is equal to the total number of dice that
* should be rolled. For example, if you roll 6 dice the minimum number is 6 (from 6 dice rolling 1).
* Another example, for rolling 12 dice the minimum number is 12 (from rolling 12 1s).
*/
void TestDice::testDiceLowerBound(void) {
	int result = 0;

	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("2d4");
		CPPUNIT_ASSERT(result >= 2);
	}
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("3d6");
		CPPUNIT_ASSERT(result >= 3);
	}
	for (int j = 1; j <= 100; j++) {
		int result = myDice.roll("4d8");
		CPPUNIT_ASSERT(result >= 4);
	}
	for (int j = 1; j <= 100; j++) {
		int result = myDice.roll("12d10");
		CPPUNIT_ASSERT(result >= 12);
	}
	for (int j = 1; j <= 100; j++) {
		int result = myDice.roll("52d12");
		CPPUNIT_ASSERT(result >= 52);
	}

	for (int j = 1; j <= 100; j++) {
		int result = myDice.roll("34d20");
		CPPUNIT_ASSERT(result >= 34);
	}
	for (int j = 1; j <= 100; j++) {
		int result = myDice.roll("46d100");
		CPPUNIT_ASSERT(result >= 46);
	}
}

//! test method for role function of the Dice class 
//! Test Case: the the validity of input string
void TestDice::testDiceRollInputValidity()
{
	int result = 0;
	// test that if the string is valid, the result is calculated
	result = myDice.roll("4d20");
	CPPUNIT_ASSERT(result > 0);
	result = myDice.roll("3d10+1");
	CPPUNIT_ASSERT(result > 0);

	//test that is the string is invalid, roll() returns -1
	result = myDice.roll("4d");
	CPPUNIT_ASSERT(result == -1);
	result = myDice.roll("d20");
	CPPUNIT_ASSERT(result == -1);
	result = myDice.roll("420");
	CPPUNIT_ASSERT(result == -1);
	result = myDice.roll("4d20+");
	CPPUNIT_ASSERT(result == -1);
}

//! test method for role function of the Dice class 
//! Test Case: the upperbound of all values returned from roll function
void TestDice::testDiceRollingBounds()
{
	int result = 0;
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("1d4");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 4);
	}
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("1d6");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 6);
	}
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("1d8");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 8);
	}
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("1d10");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 10);
	}
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("1d12");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 12);
	}
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("1d20");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 20);
	}
	for (int j = 1; j <= 100; j++) {
		result = myDice.roll("1d100");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 100);
	}
}

/**
* Initializes the Dice object used by the test unit.
*/
void TestDice::setUp(void)

{
	myDice = Dice(true);
}

/**
* Deletes the Dice object used by the test unit.
*/
void TestDice::tearDown(void)
{
	//delete myDice;
}