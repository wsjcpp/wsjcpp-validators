#ifndef UNIT_TEST_VALIDATOR_UUID_H
#define UNIT_TEST_VALIDATOR_UUID_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorUuid : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorUuid();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_UUID_H

