#ifndef UNIT_TEST_VALIDATOR_NUMBER_H
#define UNIT_TEST_VALIDATOR_NUMBER_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorNumber : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorNumber();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_NUMBER_H

