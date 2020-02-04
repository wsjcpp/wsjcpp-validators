#include "unit_test_validator_string_list.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_UNIT_TEST(UnitTestValidatorStringList)

UnitTestValidatorStringList::UnitTestValidatorStringList()
    : WSJCppUnitTestBase("UnitTestStringList") {
}

// ---------------------------------------------------------------------

void UnitTestValidatorStringList::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestValidatorStringList::run() {
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

    WJSCppValidatorStringListBase *pValidator = new WJSCppValidatorStringListBase("test", {"some1", "some2", "some3", "hello"});
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("dkljsfld", false));
    tests.push_back(new LTestVld("hello", true));
    tests.push_back(new LTestVld("some1", true));
    tests.push_back(new LTestVld("some2", true));
    tests.push_back(new LTestVld("some3", true));

    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compareB(bTestSuccess, "Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
    }

    return bTestSuccess;
}

