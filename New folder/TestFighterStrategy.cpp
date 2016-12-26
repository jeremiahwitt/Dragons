//! @file FighterTest.cpp
//! @brief Implementation file for the Fighter Testing class  
//! <p> This document includes the test suite which is used to test the Fighter class
//!     and its components.

#include <cppunit/TestCase.h>
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
#include "Characters.h"
#include "Fighter.h"
#include "Monster.h"
#include <iostream>
using namespace CppUnit;

//! Test Class for the Fighter class
class FighterTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FighterTest);
	CPPUNIT_TEST(testSettingFighterPosition);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testSettingFighterPosition();
};

//! test case registration
CPPUNIT_TEST_SUITE_REGISTRATION(FighterTest);

/**
* This test will ensure that setting the position of the Fighter is working properly, and that new values
* of position can be retrieved accurently.
*/
void FighterTest::testSettingFighterPosition(){
	// We will first create a new Fighter and then set its position
	Fighter* testFighter = new Fighter(1, Dwarf, "");
	int newVect = 25;
	int newChar = 36;
	testFighter->setPosition(newVect, newChar);

	// Now, we will assert that its position has been changed
	CPPUNIT_ASSERT(testFighter->getVectPos() == newVect);
	CPPUNIT_ASSERT(testFighter->getCharPos() == newChar);

	// We will change the position again, and assert that it has been updated accordingly
	newVect = 205;
	newChar = 306;
	testFighter->setPosition(newVect, newChar);
	CPPUNIT_ASSERT(testFighter->getVectPos() == newVect);
	CPPUNIT_ASSERT(testFighter->getCharPos() == newChar);
}
