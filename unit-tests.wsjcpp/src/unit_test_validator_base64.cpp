#include "unit_test_validator_base64.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_UNIT_TEST(UnitTestValidatorBase64)

UnitTestValidatorBase64::UnitTestValidatorBase64()
    : WSJCppUnitTestBase("UnitTestValidatorBase64") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorBase64::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorBase64::run() {
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
    
    WSJCppValidatorBase64 *pValidator = new WSJCppValidatorBase64();
    tests.push_back(new LTestVld("O2Rrc2Y7YXNsa2RmMQ==", true));
    tests.push_back(new LTestVld("O2Rrc2Y7YXNsa2Rm", true));
    tests.push_back(new LTestVld("O2Rrc2Y7YXNsa2Rm==", false));
    tests.push_back(new LTestVld("1898-01-01", false));
    tests.push_back(new LTestVld("+/11", true));
    tests.push_back(new LTestVld("%$", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
    return bTestSuccess;
}

