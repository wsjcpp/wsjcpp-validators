
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
  tests.push_back(local("some", false));
  tests.push_back(local("00:00:00", true));
  tests.push_back(local("00:0+:-0", false));
  tests.push_back(local("01:02:03", true));
  tests.push_back(local("12:24:45", true));
  tests.push_back(local("23:59:59", true));
  tests.push_back(local("23:64:04", false));
  tests.push_back(local("23:59:61", false));
  tests.push_back(local("24:00:00", false));
  tests.push_back(local("25:90:00", false));

  WsjcppValidatorTimeH24 *pValidator = new WsjcppValidatorTimeH24();

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
