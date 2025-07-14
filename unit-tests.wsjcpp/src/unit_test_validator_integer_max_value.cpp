#include "unit_test_validator_integer_max_value.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorIntegerMaxValue)

UnitTestValidatorIntegerMaxValue::UnitTestValidatorIntegerMaxValue()
    : WsjcppUnitTestBase("UnitTestValidatorIntegerMaxValue") {
}

bool UnitTestValidatorIntegerMaxValue::doBeforeTest() {
    return true;
}

void UnitTestValidatorIntegerMaxValue::executeTest() {
    bool bTestSuccess = true;
    struct LTestVld {
        LTestVld(int nValue, bool bExpectedResult) {
            m_nValue = nValue;
            m_bExpectedResult = bExpectedResult;
        }
        int m_nValue;
        int m_bExpectedResult;
    };
    std::vector<LTestVld *> tests;

    WsjcppValidatorIntegerMaxValue *pValidator = new WsjcppValidatorIntegerMaxValue(1000);
    tests.push_back(new LTestVld(1, true));
    tests.push_back(new LTestVld(1000, true));
    tests.push_back(new LTestVld(-10, true));
    tests.push_back(new LTestVld(1001, false));
    tests.push_back(new LTestVld(100100000, false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        int nValue = tests[i]->m_nValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(nValue, sError);
        compare("Test '" + std::to_string(nValue) + "' error: " + sError, bGotResult, bExpectedResult);
    }
}

bool UnitTestValidatorIntegerMaxValue::doAfterTest() {
    return true;
}
