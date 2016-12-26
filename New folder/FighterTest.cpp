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
#include <cppunit/XmlOutputter.h>
using namespace CppUnit;
#include "Characters.h"
#include "Fighter.h"

class FighterTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FighterTest);
	CPPUNIT_TEST(testValidNewCharacter);
	CPPUNIT_TEST(testProficiencyBonus);
	CPPUNIT_TEST(testValidDeath);
	CPPUNIT_TEST(testValidExpGain);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidNewCharacter();
	void testProficiencyBonus();
	void testValidDeath();
	void testValidExpGain();
};


//! test case registration
CPPUNIT_TEST_SUITE_REGISTRATION(FighterTest);

//!Test to validate if character dies when damage exceeds HP
void FighterTest::testValidDeath()
{
	Fighter *conan = new Fighter(1, Dwarf, "Conan");
	conan->receiveDamage(60);
	CPPUNIT_ASSERT(conan->validateDeath());
}

//!Test to validate if character exp gain from monster defeat is correct
void FighterTest::testValidExpGain()
{
	Fighter *conan = new Fighter(1, Dwarf, "Conan");
	conan->gainExperience(200);
	CPPUNIT_ASSERT(conan->getExp()==200);
}

void FighterTest::testValidNewCharacter()
{
	Fighter *conan = new Fighter(1, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateNewCharacter());
}

/*
void FighterTest::testHitPoints()
{
	Fighter *conan = new Fighter(1, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateHitPoints());
	conan = new Fighter(2, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateHitPoints());
}*/

void FighterTest::testProficiencyBonus()
{
	Fighter* conan = new Fighter(3, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateProficiency());
	conan = new Fighter(6, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateProficiency());
	conan = new Fighter(9, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateProficiency());
	conan = new Fighter(12, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateProficiency());
	conan = new Fighter(15, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateProficiency());
	conan = new Fighter(18, Dwarf, "Conan");
	CPPUNIT_ASSERT(conan->validateProficiency());
}
