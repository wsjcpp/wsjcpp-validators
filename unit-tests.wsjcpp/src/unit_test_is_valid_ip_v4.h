#ifndef UNIT_TEST_IS_VALID_IP_V4_H
#define UNIT_TEST_IS_VALID_IP_V4_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestisValidIpV4 : public WsjcppUnitTestBase {
    public:
        UnitTestisValidIpV4();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_IS_VALID_IP_V4_H

