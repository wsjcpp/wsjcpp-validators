#include "unit_test_validator_hex.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_UNIT_TEST(UnitTestValidatorHex)

UnitTestValidatorHex::UnitTestValidatorHex()
    : WSJCppUnitTestBase("UnitTestValidatorHex") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorHex::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorHex::run() {
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
    
    WSJCppValidatorHex *pValidator = new WSJCppValidatorHex();
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("2020", true));
    tests.push_back(new LTestVld("abcdef0123456789ABCDEF", true));
    tests.push_back(new LTestVld("0123J", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
    return bTestSuccess;
}

