#ifndef UNIT_TEST_VALIDATOR_INTEGER_MAX_VALUE_H
#define UNIT_TEST_VALIDATOR_INTEGER_MAX_VALUE_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorIntegerMaxValue : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorIntegerMaxValue();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_INTEGER_MAX_VALUE_H

