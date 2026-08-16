
#include "wsjcpp_validators.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int found_errors = 0;

  struct local {
    local(const std::string &value, bool expected)
        : value(value), expected(expected) {

          };
    std::string value;
    bool expected;
  };
  std::vector<local> tests;
  tests.push_back(local("https://google.com/?some=1&som24", true));
  tests.push_back(local("https://google.com/?some=1&som24/", true));
  tests.push_back(local("http://foo.com/blah_blah", true));
  tests.push_back(local("http://foo.com/blah_blah/", true));
  tests.push_back(local("http://foo.com/blah_blah_(wikipedia)", true));
  tests.push_back(local("http://foo.com/blah_blah_(wikipedia)_(again)", true));
  tests.push_back(local("http://www.example.com/wpstyle/?p=364", true));
  tests.push_back(local("https://www.example.com/foo/?bar=baz&inga=42&quux", true));
  // tests.push_back(local("http://✪df.ws/123", true));
  tests.push_back(local("http://userid:password@example.com:8080", true));
  tests.push_back(local("http://userid:password@example.com:8080/", true));
  tests.push_back(local("http://userid@example.com", true));
  tests.push_back(local("http://userid@example.com/", true));
  tests.push_back(local("http://userid@example.com:8080", true));
  tests.push_back(local("http://userid@example.com:8080/", true));
  tests.push_back(local("http://userid:password@example.com", true));
  tests.push_back(local("http://userid:password@example.com/", true));
  tests.push_back(local("http://142.42.1.1/", true));
  tests.push_back(local("http://142.42.1.1:8080/", true));
  // tests.push_back(local("http://➡.ws/䨹", true));
  // tests.push_back(local("http://⌘.ws", true));
  // tests.push_back(local("http://⌘.ws/", true));
  tests.push_back(local("http://foo.com/blah_(wikipedia)#cite-1", true));
  tests.push_back(local("http://foo.com/blah_(wikipedia)_blah#cite-1", true));
  tests.push_back(local("http://foo.com/unicode_(✪)_in_parens", true));
  tests.push_back(local("http://foo.com/(something)?after=parens", true));
  // tests.push_back(local("http://☺.damowmow.com/", true));
  tests.push_back(local("http://code.google.com/events/#&product=browser", true));
  tests.push_back(local("http://j.mp", true));
  tests.push_back(local("ftp://foo.bar/baz", true));
  tests.push_back(local("ws://foo.bar/baz", true));
  tests.push_back(local("wss://foo.bar/baz", true));
  tests.push_back(local("http://foo.bar/?q=Test%20URL-encoded%20stuff", true));
  // tests.push_back(local("http://مثال.إختبار", true));
  // tests.push_back(local("http://例子.测试", true));
  // tests.push_back(local("http://उदाहरण.परीक्षा", true));
  tests.push_back(local("http://-.~_!$&'()*+,;=:%40:80%2f::::::@example.com", true));
  tests.push_back(local("http://1337.net", true));
  tests.push_back(local("http://a.b-c.de", true));
  tests.push_back(local("http://223.255.255.254", true));

  // incorrect
  tests.push_back(local("https://foo_bar.example.com/", false));
  tests.push_back(local("some", false));
  tests.push_back(local("ABCD", false));
  tests.push_back(local("http://", false));
  tests.push_back(local("http://.", false));
  tests.push_back(local("http://..", false));
  tests.push_back(local("http://../", false));
  tests.push_back(local("http://?", false));
  tests.push_back(local("http://??", false));
  tests.push_back(local("http://??/", false));
  tests.push_back(local("http://#", false));
  tests.push_back(local("http://##", false));
  tests.push_back(local("http://##/", false));
  tests.push_back(local("http://foo.bar?q=Spaces should be encoded", false));
  tests.push_back(local("http://142.42.1.1:88888/", false));
  tests.push_back(local("//", false));
  tests.push_back(local("//a", false));
  tests.push_back(local("///a", false));
  tests.push_back(local("///", false));
  tests.push_back(local("http:///a", false));
  tests.push_back(local("foo.com", false));
  tests.push_back(local("https://foo.com.", false));
  tests.push_back(local("https://foo..com.", false));
  tests.push_back(local("https://foo.com..", false));
  tests.push_back(local("https://.foo.com", false));
  tests.push_back(local("https://..foo.com", false));
  tests.push_back(local("rdar://1234", false));
  tests.push_back(local("some://1234", false));
  tests.push_back(local("h://test", false));
  tests.push_back(local("http:// shouldfail.com", false));
  tests.push_back(local(":// should fail", false));
  tests.push_back(local("http://foo.bar/foo(bar)baz quux", false));
  tests.push_back(local("ftps://foo.bar/", false));
  tests.push_back(local("http://-error-.invalid/", false));
  tests.push_back(local("http://a.b--c.de/", false));
  tests.push_back(local("http://-a.b.co", false));
  tests.push_back(local("http://a.b-.co", false));
  tests.push_back(local("http://1.1.1.1.1", false));
  tests.push_back(local("http://123.123.123", false));
  tests.push_back(local("http://3628126748", false));
  tests.push_back(local("http://.www.foo.bar/", false));
  tests.push_back(local("http://www.foo.bar./", false));
  tests.push_back(local("http://.www.foo.bar./", false));

  wsjcpp::WsjcppValidatorURL *pValidator = new wsjcpp::WsjcppValidatorURL();

  for (int i = 0; i < tests.size(); i++) {
    local t = tests[i];
    std::string error;
    bool got = pValidator->isValid(t.value, error);
    if (got != t.expected) {
      found_errors++;
      std::cerr << "Expected " << (t.expected ? "true" : "false") << ", but got " << (got ? "true" : "false") << " for "
                << t.value << "error: " << error << std::endl;
    }
  }

  if (found_errors > 0) {
    std::cerr << "FAILED" << std::endl;
    return 1;
  }

  std::cout << "OK" << std::endl;
  return 0;
}
