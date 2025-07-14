#ifndef UNIT_TEST_VALIDATOR_INTEGER_MIN_VALUE_H
#define UNIT_TEST_VALIDATOR_INTEGER_MIN_VALUE_H

#include <wsjcpp_unit_tests.h>

class UnitTestValidatorIntegerMinValue : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorIntegerMinValue();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_INTEGER_MIN_VALUE_H

