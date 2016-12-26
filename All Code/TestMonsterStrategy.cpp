//! @file MonsterTest.cpp
//! @brief Implementation file for the Monster Testing class  
//! <p> This document includes the test suite which is used to test the Monster class
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
#include "MovementStrategy.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include <iostream>
using namespace CppUnit;

//! Test Class for the Monster class
class MonsterTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MonsterTest);
	CPPUNIT_TEST(testSettingMonsterPosition);
	CPPUNIT_TEST(testWhenFriendlyAttacked);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testSettingMonsterPosition();
	void testUnderAttack();
	void testWhenFriendlyAttacked();
};

//! test case registration
CPPUNIT_TEST_SUITE_REGISTRATION(MonsterTest);

/**
* This test will ensure that setting the position of the Monster is working properly, and that new values
* of position can be retrieved accurently.
*/
void MonsterTest::testSettingMonsterPosition(){
	// We will first create a new Monster and then set its position
	Fighter* testFighter = new Fighter(1, Dwarf, "");
	Monster* testCharacter = new Monster("Test", Beast, Small, 1, 1, 1, 1, 1, 1, 1, 1, 1, new Weapon(), testFighter);
	int newVect = 25;
	int newChar = 36;
	testCharacter->setPosition(newVect, newChar);

	// Now, we will assert that its position has been changed
	CPPUNIT_ASSERT(testCharacter->getVectPos() == newVect);
	CPPUNIT_ASSERT(testCharacter->getCharPos() == newChar);

	// We will change the position again, and assert that it has been updated accordingly
	newVect = 205;
	newChar = 306;
	testCharacter->setPosition(newVect, newChar);
	CPPUNIT_ASSERT(testCharacter->getVectPos() == newVect);
	CPPUNIT_ASSERT(testCharacter->getCharPos() == newChar);

}

/**
* This test will ensure that if a Friendly monster is attacked, its strategy switches to Aggressive
*/
void MonsterTest::testWhenFriendlyAttacked(){
	// We will first create a new Monster and then set its position
	Fighter* testFighter = new Fighter(1, Dwarf, "");
	Monster* testCharacter = new Monster("Test", Humanoid, Small, 1, 1, 1, 1, 1, 1, 1, 1, 1, new Weapon(), testFighter);
	// We will assert that its strategy has been set to friendly
	CPPUNIT_ASSERT(testCharacter->getCharType() == Friendly);
	CPPUNIT_ASSERT(typeid(*(testCharacter->getStrategy())) == typeid(FriendlyStrategy));

	// Next, we will attack it, and then assert that its strategy is now aggressive
	testFighter->attack(testCharacter);
	CPPUNIT_ASSERT(testCharacter->getCharType() == Aggressor);
}