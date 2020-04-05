#include "unit_test_validator_string_length.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorStringLength)

UnitTestValidatorStringLength::UnitTestValidatorStringLength()
    : WsjcppUnitTestBase("UnitTestValidatorStringLength") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorStringLength::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorStringLength::run() {
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

    WsjcppValidatorStringLength *pValidator = new WsjcppValidatorStringLength(5,10);
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("dkljs", true));
    tests.push_back(new LTestVld("hello", true));
    tests.push_back(new LTestVld("hellohello", true));
    tests.push_back(new LTestVld("hellohello1", false));
    tests.push_back(new LTestVld("hellohellossssssssssss1", false));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }

    return bTestSuccess;
}

