#ifndef UNIT_TEST_VALIDATOR_REG_EXP_H
#define UNIT_TEST_VALIDATOR_REG_EXP_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorRegExp : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorRegExp();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_REG_EXP_H

