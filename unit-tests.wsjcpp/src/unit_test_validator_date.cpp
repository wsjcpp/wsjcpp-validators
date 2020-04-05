#include "unit_test_validator_date.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorDate)

UnitTestValidatorDate::UnitTestValidatorDate()
    : WsjcppUnitTestBase("UnitTestValidatorDate") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorDate::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorDate::run() {
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
    
    WsjcppValidatorDate *pValidator = new WsjcppValidatorDate();
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("2020-01-01", true));
    tests.push_back(new LTestVld("2020-12-00", false));
    tests.push_back(new LTestVld("0000-00-00", false));
    tests.push_back(new LTestVld("0000-01-01", true));
    tests.push_back(new LTestVld("2020-12-31", true));
    tests.push_back(new LTestVld("2020-02-29", true));
    tests.push_back(new LTestVld("2021-02-29", false));
    tests.push_back(new LTestVld("1898-01-01", true));
    tests.push_back(new LTestVld("1898-15-01", false));
    tests.push_back(new LTestVld("1898-01-32", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
    return bTestSuccess;
}

