#include "unit_test_is_valid_ip_v4.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestisValidIpV4)

UnitTestisValidIpV4::UnitTestisValidIpV4()
    : WsjcppUnitTestBase("UnitTestisValidIpV4") {
}

bool UnitTestisValidIpV4::doBeforeTest() {
    return true;
}

void UnitTestisValidIpV4::executeTest() {
    struct TestIPv4 {
        TestIPv4(const std::string &sIPv4, bool bExpected) :
            m_sIPv4(sIPv4), m_bExpected(bExpected) {

            };
        std::string m_sIPv4;
        bool m_bExpected;
    };
    std::vector<TestIPv4> vIPv4s;
    vIPv4s.push_back(TestIPv4("127.0.0.1", true));
    vIPv4s.push_back(TestIPv4("10.0.0.1", true));
    vIPv4s.push_back(TestIPv4("0.0.0.0", true));
    vIPv4s.push_back(TestIPv4("300.200.100.100", false));
    vIPv4s.push_back(TestIPv4("223.255.255.254", true));

    vIPv4s.push_back(TestIPv4("aaaa", false));
    vIPv4s.push_back(TestIPv4("100.0.0.x", false));
    vIPv4s.push_back(TestIPv4("10033.1289.0.0", false));
    vIPv4s.push_back(TestIPv4("10033.1289.0.0.0.0.0", false));

    for (int i = 0; i < vIPv4s.size(); i++) {
        TestIPv4 t = vIPv4s[i];
        std::string sError;
        bool bGotResult = WsjcppValidators::isValidIPv4(t.m_sIPv4, sError);
        compare("Test[" + t.m_sIPv4 + ", error=" + sError + "]", bGotResult, t.m_bExpected);
    }
}

bool UnitTestisValidIpV4::doAfterTest() {
    return true;
}
