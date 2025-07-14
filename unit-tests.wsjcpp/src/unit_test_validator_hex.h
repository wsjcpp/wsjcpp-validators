#ifndef UNIT_TEST_VALIDATOR_HEX_H
#define UNIT_TEST_VALIDATOR_HEX_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorHex : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorHex();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_VALIDATOR_HEX_H

