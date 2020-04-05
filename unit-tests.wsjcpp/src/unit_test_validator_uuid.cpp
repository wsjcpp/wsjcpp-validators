#include "unit_test_validator_uuid.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorUuid)

UnitTestValidatorUuid::UnitTestValidatorUuid()
    : WsjcppUnitTestBase("UnitTestValidatorUuid") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorUuid::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorUuid::run() {
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

    WsjcppValidatorUUID *pValidatorUUID = new WsjcppValidatorUUID();
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("00000000-0000-0000-1000-000000000001", true));
    tests.push_back(new LTestVld("abcdef01-ABCD-EF23-1000-000000000001", true));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidatorUUID->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
    return bTestSuccess;
}

