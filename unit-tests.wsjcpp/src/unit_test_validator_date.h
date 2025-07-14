#ifndef UNIT_TEST_VALIDATOR_DATE_H
#define UNIT_TEST_VALIDATOR_DATE_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorDate : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorDate();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_DATE_H

