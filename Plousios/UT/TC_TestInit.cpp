#include "stdafx.h"
#include "TC_TestInit.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TC_TestInit );

void TC_TestInit::setUp()
{
    CPPUNIT_NS::stdCOut() << "SetUp" << std::endl;
}

void TC_TestInit::tearDown()
{
    CPPUNIT_NS::stdCOut() << "TearDown" << std::endl;
}

void TC_TestInit::Test()
{
    CPPUNIT_ASSERT( true );
}