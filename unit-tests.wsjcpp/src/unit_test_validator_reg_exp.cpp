#include "unit_test_validator_reg_exp.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorRegExp)

UnitTestValidatorRegExp::UnitTestValidatorRegExp()
    : WsjcppUnitTestBase("UnitTestValidatorRegExp") {
}

bool UnitTestValidatorRegExp::doBeforeTest() {
    return true;
}

void UnitTestValidatorRegExp::executeTest() {
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

    WsjcppValidatorStringRegexpBase *pValidator = new WsjcppValidatorStringRegexpBase("simpleregexp", "^[A-Z]*$");
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("ABCD", true));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compare("Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
}

bool UnitTestValidatorRegExp::doAfterTest() {
    return true;
}
