#include "stdafx.h"
#include <cppunit/TextOutputter.h>
#include <filesystem>

int main( int argc, char * argv[ ] )
{
    CPPUNIT_NS::TestResult testResult;
    CPPUNIT_NS::TestResultCollector collectedResults;
    testResult.addListener( &collectedResults );
    CPPUNIT_NS::TestRunner testRunner;
    testRunner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
    testRunner.run( testResult );

    std::ofstream xmlFileOut( "UT_log.xml" );
    CPPUNIT_NS::XmlOutputter xmlOut( &collectedResults, xmlFileOut );
    xmlOut.write();

    CPPUNIT_NS::TextOutputter consoleOut( &collectedResults, CPPUNIT_NS::stdCOut() );
    consoleOut.write();

    return collectedResults.wasSuccessful() ? 0 : 1;
}