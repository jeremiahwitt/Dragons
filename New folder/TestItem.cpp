//! @file 
//! @brief File containing the Test Class and the Test Methods
//!

#include <iostream>
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
//#include "stdafx.h"
#include "Item.h"
using namespace CppUnit;
using namespace std;

//! Test Class for the Container class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestItem : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestItem);
	CPPUNIT_TEST(testValidItem);
	CPPUNIT_TEST(testInvalidItem);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidItem(void);
	void testInvalidItem();
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);//most important

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on a valid item should return true 
void TestItem::testValidItem(void)
{
	//std::cout << "Test to see whether a valid item can be made...\n";
	CPPUNIT_ASSERT_NO_THROW(Item newItem());
}

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on an invalid item should return true 
void TestItem::testInvalidItem(void)
{
	//std::cout << "Test to see whether an invalid item can be made...\n";
	Item newItem = Item();
	CPPUNIT_ASSERT_THROW(newItem.setWeight(5000), std::exception*);
}

