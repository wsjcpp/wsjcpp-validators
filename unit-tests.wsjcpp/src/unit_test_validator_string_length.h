#ifndef UNIT_TEST_VALIDATOR_STRING_LENGTH_H
#define UNIT_TEST_VALIDATOR_STRING_LENGTH_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorStringLength : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorStringLength();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_STRING_LENGTH_H

