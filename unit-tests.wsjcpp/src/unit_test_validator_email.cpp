#include "unit_test_validator_email.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_UNIT_TEST(UnitTestValidatorEmail)

UnitTestValidatorEmail::UnitTestValidatorEmail()
    : WSJCppUnitTestBase("UnitTestValidatorEmail") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorEmail::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorEmail::run() {
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
    
    WJSCppValidatorEmail *pValidatorEmail = new WJSCppValidatorEmail();
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("some@some", false));
    tests.push_back(new LTestVld("some@some.rr", true));
    tests.push_back(new LTestVld("01@some.com", true));
    tests.push_back(new LTestVld("s_s-some@test.com", true));
    tests.push_back(new LTestVld("s_s-some@test.c", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidatorEmail->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }

    return bTestSuccess;
}
