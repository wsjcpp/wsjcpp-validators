#include "unit_test_is_valid_ip_v6.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_UNIT_TEST(UnitTestisValidIpV6)

UnitTestisValidIpV6::UnitTestisValidIpV6()
    : WSJCppUnitTestBase("UnitTestisValidIpV6") {
}

// ---------------------------------------------------------------------

void UnitTestisValidIpV6::init() {
    // nothing
}

// ---------------------------------------------------------------------

bool UnitTestisValidIpV6::run() {
    struct TestIPv6 {
        TestIPv6(const std::string &sIPv6, bool bExpected) :
            m_sIPv6(sIPv6), m_bExpected(bExpected) {

            };
        std::string m_sIPv6;
        bool m_bExpected;
        
    };
    std::vector<TestIPv6> vIPv6s;
    vIPv6s.push_back(TestIPv6("3FFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF", true));
    vIPv6s.push_back(TestIPv6("FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF", true));
    vIPv6s.push_back(TestIPv6("2607:f8b0:4002:c08::8b", true));
    vIPv6s.push_back(TestIPv6("2607:f8b0:4002:c08:0:0:0:8b", true));
    vIPv6s.push_back(TestIPv6("2000::", true));
    vIPv6s.push_back(TestIPv6("::1", true));
    vIPv6s.push_back(TestIPv6("aaaa", false));
    vIPv6s.push_back(TestIPv6("100.0.0.1", false));
    vIPv6s.push_back(TestIPv6("100.0.0.x", false));
    vIPv6s.push_back(TestIPv6("10033.1289.0.0", false));
    vIPv6s.push_back(TestIPv6("10033.1289.0.0.0.0.0", false));
    
    bool bTestSuccess = true;
    for (int i = 0; i < vIPv6s.size(); i++) {
        TestIPv6 t = vIPv6s[i];
        std::string sError;
        bool bGotResult = WSJCppValidators::isValidIPv6(t.m_sIPv6, sError);
        compareB(bTestSuccess, "Test[" + t.m_sIPv6 + ", error = " + sError + "]", bGotResult, t.m_bExpected);
    }
    return bTestSuccess;
}

