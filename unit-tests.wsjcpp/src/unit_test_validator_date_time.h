#ifndef UNIT_TEST_VALIDATOR_DATE_TIME_H
#define UNIT_TEST_VALIDATOR_DATE_TIME_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorDateTime : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorDateTime();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_DATE_TIME_H

