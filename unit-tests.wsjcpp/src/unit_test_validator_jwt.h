#ifndef UNIT_TEST_VALIDATOR_JWT_H
#define UNIT_TEST_VALIDATOR_JWT_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorJwt : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorJwt();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_JWT_H

