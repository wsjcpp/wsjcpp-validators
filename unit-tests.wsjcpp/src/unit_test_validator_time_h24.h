#ifndef UNIT_TEST_VALIDATOR_TIME_H24_H
#define UNIT_TEST_VALIDATOR_TIME_H24_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorTimeH24 : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorTimeH24();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_TIME_H24_H

