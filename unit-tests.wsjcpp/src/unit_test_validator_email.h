#ifndef UNIT_TEST_VALIDATOR_EMAIL_H
#define UNIT_TEST_VALIDATOR_EMAIL_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorEmail : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorEmail();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_EMAIL_H

