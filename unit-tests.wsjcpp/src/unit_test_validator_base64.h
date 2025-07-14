#ifndef UNIT_TEST_VALIDATOR_BASE64_H
#define UNIT_TEST_VALIDATOR_BASE64_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorBase64 : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorBase64();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_BASE64_H

