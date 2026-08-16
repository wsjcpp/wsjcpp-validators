
#include "wsjcpp_validators.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int found_errors = 0;

  struct local {
    local(int value, bool expected)
        : value(value), expected(expected) {

          };
    int value;
    bool expected;
  };
  std::vector<local> tests;
  tests.push_back(local(1, true));
  tests.push_back(local(1000, true));
  tests.push_back(local(-10, false));
  tests.push_back(local(0, false));
  tests.push_back(local(1001, true));
  tests.push_back(local(100100000, true));

  wsjcpp::validator_int_min *pValidator = new wsjcpp::validator_int_min(1);

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
