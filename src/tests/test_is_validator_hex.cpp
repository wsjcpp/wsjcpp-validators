
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
  tests.push_back(local("2020", true));
  tests.push_back(local("abcdef0123456789ABCDEF", true));
  tests.push_back(local("0123J", false));

  wsjcpp::validator_hex *pValidator = new wsjcpp::validator_hex();

  for (int i = 0; i < tests.size(); i++) {
    local t = tests[i];
    std::string error;
    bool got = pValidator->is_valid(t.value, error);
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
