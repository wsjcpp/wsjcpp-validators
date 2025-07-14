#ifndef UNIT_TEST_STRING_LIST_H
#define UNIT_TEST_STRING_LIST_H

#include <wsjcpp_unit_tests.h>

// Description: TODO
class UnitTestValidatorStringList : public WsjcppUnitTestBase {
    public:
        UnitTestValidatorStringList();
        virtual bool doBeforeTest() override;
        virtual void executeTest() override;
        virtual bool doAfterTest() override;
};

#endif // UNIT_TEST_STRING_LIST_H

