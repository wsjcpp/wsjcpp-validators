#ifndef UNIT_TEST_VALIDATOR_URL_H
#define UNIT_TEST_VALIDATOR_URL_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorUrl : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorUrl();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_URL_H

