#include "unit_test_validator_integer_min_value.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorIntegerMinValue)

UnitTestValidatorIntegerMinValue::UnitTestValidatorIntegerMinValue()
    : WsjcppUnitTestBase("UnitTestValidatorIntegerMinValue") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorIntegerMinValue::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorIntegerMinValue::run() {
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

    WsjcppValidatorIntegerMinValue *pValidator = new WsjcppValidatorIntegerMinValue(1);
    tests.push_back(new LTestVld(1, true));
    tests.push_back(new LTestVld(1000, true));
    tests.push_back(new LTestVld(-10, false));
    tests.push_back(new LTestVld(0, false));
    tests.push_back(new LTestVld(1001, true));
    tests.push_back(new LTestVld(100100000, true));
    
    for (unsigned int i = 0; i < tests.size(); i++) {
        int nValue = tests[i]->m_nValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(nValue, sError);
        compareB(bTestSuccess, "Test '" + std::to_string(nValue) + "' error: " + sError, bGotResult, bExpectedResult);
    }
    return bTestSuccess;
}

