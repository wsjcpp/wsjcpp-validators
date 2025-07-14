#include "unit_test_validator_date_time.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorDateTime)

UnitTestValidatorDateTime::UnitTestValidatorDateTime()
    : WsjcppUnitTestBase("UnitTestValidatorDateTime") {
}

bool UnitTestValidatorDateTime::doBeforeTest() {
    return true;
}

void UnitTestValidatorDateTime::executeTest() {
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

    WsjcppValidatorDateTime *pValidator = new WsjcppValidatorDateTime();
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("2020-01-01T00:00:00", true));
    tests.push_back(new LTestVld("2020-12-01T00:00:00", true));
    tests.push_back(new LTestVld("1898-01-01T00:00:00", true));
    tests.push_back(new LTestVld("1898-15-01T00:00:00", false));
    tests.push_back(new LTestVld("1898-01-32T00:00:00", false));
    tests.push_back(new LTestVld("1898-01-01X00:00:00", false));
    tests.push_back(new LTestVld("18a8-01-01T00:00:00", false));
    tests.push_back(new LTestVld("1838-01-01T25:00:00", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compare("Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }
}

bool UnitTestValidatorDateTime::doAfterTest() {
    return true;
}
