#include "unit_test_validator_url.h"
#include <vector>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

REGISTRY_WSJCPP_UNIT_TEST(UnitTestValidatorUrl)

UnitTestValidatorUrl::UnitTestValidatorUrl()
    : WsjcppUnitTestBase("UnitTestValidatorUrl") {
}

bool UnitTestValidatorUrl::doBeforeTest() {
    return true;
}

void UnitTestValidatorUrl::executeTest() {
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

    WsjcppValidatorURL *pValidator = new WsjcppValidatorURL();
    tests.push_back(new LTestVld("https://google.com/?some=1&som24", true));
    tests.push_back(new LTestVld("https://google.com/?some=1&som24/", true));
    tests.push_back(new LTestVld("http://foo.com/blah_blah", true));
    tests.push_back(new LTestVld("http://foo.com/blah_blah/", true));
    tests.push_back(new LTestVld("http://foo.com/blah_blah_(wikipedia)", true));
    tests.push_back(new LTestVld("http://foo.com/blah_blah_(wikipedia)_(again)", true));
    tests.push_back(new LTestVld("http://www.example.com/wpstyle/?p=364", true));
    tests.push_back(new LTestVld("https://www.example.com/foo/?bar=baz&inga=42&quux", true));
    // tests.push_back(new LTestVld("http://✪df.ws/123", true));
    tests.push_back(new LTestVld("http://userid:password@example.com:8080", true));
    tests.push_back(new LTestVld("http://userid:password@example.com:8080/", true));
    tests.push_back(new LTestVld("http://userid@example.com", true));
    tests.push_back(new LTestVld("http://userid@example.com/", true));
    tests.push_back(new LTestVld("http://userid@example.com:8080", true));
    tests.push_back(new LTestVld("http://userid@example.com:8080/", true));
    tests.push_back(new LTestVld("http://userid:password@example.com", true));
    tests.push_back(new LTestVld("http://userid:password@example.com/", true));
    tests.push_back(new LTestVld("http://142.42.1.1/", true));
    tests.push_back(new LTestVld("http://142.42.1.1:8080/", true));
    //tests.push_back(new LTestVld("http://➡.ws/䨹", true));
    //tests.push_back(new LTestVld("http://⌘.ws", true));
    //tests.push_back(new LTestVld("http://⌘.ws/", true));
    tests.push_back(new LTestVld("http://foo.com/blah_(wikipedia)#cite-1", true));
    tests.push_back(new LTestVld("http://foo.com/blah_(wikipedia)_blah#cite-1", true));
    tests.push_back(new LTestVld("http://foo.com/unicode_(✪)_in_parens", true));
    tests.push_back(new LTestVld("http://foo.com/(something)?after=parens", true));
    //tests.push_back(new LTestVld("http://☺.damowmow.com/", true));
    tests.push_back(new LTestVld("http://code.google.com/events/#&product=browser", true));
    tests.push_back(new LTestVld("http://j.mp", true));
    tests.push_back(new LTestVld("ftp://foo.bar/baz", true));
    tests.push_back(new LTestVld("ws://foo.bar/baz", true));
    tests.push_back(new LTestVld("wss://foo.bar/baz", true));
    tests.push_back(new LTestVld("http://foo.bar/?q=Test%20URL-encoded%20stuff", true));
    //tests.push_back(new LTestVld("http://مثال.إختبار", true));
    //tests.push_back(new LTestVld("http://例子.测试", true));
    //tests.push_back(new LTestVld("http://उदाहरण.परीक्षा", true));
    tests.push_back(new LTestVld("http://-.~_!$&'()*+,;=:%40:80%2f::::::@example.com", true));
    tests.push_back(new LTestVld("http://1337.net", true));
    tests.push_back(new LTestVld("http://a.b-c.de", true));
    tests.push_back(new LTestVld("http://223.255.255.254", true));

    // incorrect
    tests.push_back(new LTestVld("https://foo_bar.example.com/", false));
    tests.push_back(new LTestVld("some", false));
    tests.push_back(new LTestVld("ABCD", false));
    tests.push_back(new LTestVld("http://", false));
    tests.push_back(new LTestVld("http://.", false));
    tests.push_back(new LTestVld("http://..", false));
    tests.push_back(new LTestVld("http://../", false));
    tests.push_back(new LTestVld("http://?", false));
    tests.push_back(new LTestVld("http://??", false));
    tests.push_back(new LTestVld("http://??/", false));
    tests.push_back(new LTestVld("http://#", false));
    tests.push_back(new LTestVld("http://##", false));
    tests.push_back(new LTestVld("http://##/", false));
    tests.push_back(new LTestVld("http://foo.bar?q=Spaces should be encoded", false));
    tests.push_back(new LTestVld("http://142.42.1.1:88888/", false));
    tests.push_back(new LTestVld("//", false));
    tests.push_back(new LTestVld("//a", false));
    tests.push_back(new LTestVld("///a", false));
    tests.push_back(new LTestVld("///", false));
    tests.push_back(new LTestVld("http:///a", false));
    tests.push_back(new LTestVld("foo.com", false));
    tests.push_back(new LTestVld("https://foo.com.", false));
    tests.push_back(new LTestVld("https://foo..com.", false));
    tests.push_back(new LTestVld("https://foo.com..", false));
    tests.push_back(new LTestVld("https://.foo.com", false));
    tests.push_back(new LTestVld("https://..foo.com", false));
    tests.push_back(new LTestVld("rdar://1234", false));
    tests.push_back(new LTestVld("some://1234", false));
    tests.push_back(new LTestVld("h://test", false));
    tests.push_back(new LTestVld("http:// shouldfail.com", false));
    tests.push_back(new LTestVld(":// should fail", false));
    tests.push_back(new LTestVld("http://foo.bar/foo(bar)baz quux", false));
    tests.push_back(new LTestVld("ftps://foo.bar/", false));
    tests.push_back(new LTestVld("http://-error-.invalid/", false));
    tests.push_back(new LTestVld("http://a.b--c.de/", false));
    tests.push_back(new LTestVld("http://-a.b.co", false));
    tests.push_back(new LTestVld("http://a.b-.co", false));
    tests.push_back(new LTestVld("http://1.1.1.1.1", false));
    tests.push_back(new LTestVld("http://123.123.123", false));
    tests.push_back(new LTestVld("http://3628126748", false));
    tests.push_back(new LTestVld("http://.www.foo.bar/", false));
    tests.push_back(new LTestVld("http://www.foo.bar./", false));
    tests.push_back(new LTestVld("http://.www.foo.bar./", false));

    int nFailed = 0;
    for (unsigned int i = 0; i < tests.size(); i++) {
        std::string sValue = tests[i]->m_sValue;
        bool bExpectedResult = tests[i]->m_bExpectedResult;
        std::string sError = "";
        bool bGotResult = pValidator->isValid(sValue, sError);
        compare("Test '" + sValue + "' error: " + sError, bGotResult, bExpectedResult);
        if (bGotResult != bExpectedResult) {
            nFailed++;
        }
    }
    if (nFailed > 0) {
        WsjcppLog::err(TAG, "Failed tests " + std::to_string(nFailed) + "/" + std::to_string(tests.size()));
    }
}

bool UnitTestValidatorUrl::doAfterTest() {
    return true;
}
