#pragma once
class TC_TestInit : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TC_TestInit );
    CPPUNIT_TEST( Test );
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() override;
    void tearDown() override;

    void Test();
};