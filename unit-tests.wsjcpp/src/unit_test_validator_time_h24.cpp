#include "unit_test_validator_time_h24.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_UNIT_TEST(UnitTestValidatorTimeH24)

UnitTestValidatorTimeH24::UnitTestValidatorTimeH24()
    : WSJCppUnitTestBase("UnitTestValidatorTimeH24") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorTimeH24::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorTimeH24::run() {
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
    
    WSJCppValidatorTimeH24 *pValidator = new WSJCppValidatorTimeH24();
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("00:00:00", true));
    tests.push_back(new LTestVld("00:0+:-0", false));
    tests.push_back(new LTestVld("01:02:03", true));
    tests.push_back(new LTestVld("12:24:45", true));
    tests.push_back(new LTestVld("23:59:59", true));
    tests.push_back(new LTestVld("23:64:04", false));
    tests.push_back(new LTestVld("23:59:61", false));
    tests.push_back(new LTestVld("24:00:00", false));
    tests.push_back(new LTestVld("25:90:00", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
    return bTestSuccess;
}

