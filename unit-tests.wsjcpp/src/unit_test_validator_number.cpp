#include "unit_test_validator_number.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorNumber)

UnitTestValidatorNumber::UnitTestValidatorNumber()
    : WsjcppUnitTestBase("UnitTestValidatorNumber") {
}

bool UnitTestValidatorNumber::doBeforeTest() {
    return true;
}

void UnitTestValidatorNumber::executeTest() {
    bool bTestSuccess = true;
    struct LTestVld {
        LTestVld(std::string sValue, bool bExpectedResult) {
            m_sValue = sValue;
            m_bExpectedResult = bExpectedResult;
        }
        std::string m_sValue;
        int m_bExpectedResult;
    };
    std::vector<LTestVld *> tests;

    WsjcppValidatorNumber *pValidator = new WsjcppValidatorNumber();
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("2020-01-01", false));
    tests.push_back(new LTestVld("2020", true));
    tests.push_back(new LTestVld("-2020", true));
    tests.push_back(new LTestVld("-", false));
    tests.push_back(new LTestVld("", false));
    tests.push_back(new LTestVld("+2020", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compare("Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
}

bool UnitTestValidatorNumber::doAfterTest() {
    return true;
}
