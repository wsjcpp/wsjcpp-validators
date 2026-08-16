/*
MIT License

Copyright (c) 2020-2025 wsjcpp

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <algorithm>
#include <iostream>
#include <string.h>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

int main(int argc, char *argv[]) {
  std::string TAG = "MAIN";

  if (!wsjcpp::dir_exists(".wsjcpp")) {
    WsjcppCore::makeDir(".wsjcpp");
  }
  std::string appLogPath = ".wsjcpp/logs";
  if (!wsjcpp::dir_exists(appLogPath)) {
    WsjcppCore::makeDir(appLogPath);
  }
  WsjcppLog::setPrefixLogFile("wsjcpp_validators");
  WsjcppLog::setLogDirectory(".wsjcpp/logs");

  // WsjcppLog::info(TAG, "Hello");
  WsjcppCore::init(argc, argv, std::string(WSJCPP_APP_NAME), std::string(WSJCPP_APP_VERSION), "Evgenii Sopov", "");
  if (argc != 2) {
    std::cout << "Usage " << argv[0] << " something" << std::endl;
    return -1;
  }
  std::string sArg1(argv[1]);

  std::vector<wsjcpp::validator<std::string> *> validators;
  // validators.push_back(new validator_strlen(5, 100));
  // validators.push_back(new validator_strlen(1, 5));
  validators.push_back(new wsjcpp::validator_email());
  validators.push_back(new wsjcpp::validator_uuid());
  validators.push_back(new wsjcpp::validator_str_list("lang", {"en", "de", "ru"}));
  validators.push_back(new wsjcpp::validator_regexp("testre", "^[a-zA-Z]+$"));
  validators.push_back(new wsjcpp::validator_jwt());
  // validators.push_back(new wsjcpp::validator_date());
  validators.push_back(new wsjcpp::validator_time24());
  validators.push_back(new wsjcpp::validator_datetime());
  validators.push_back(new wsjcpp::validator_url());
  validators.push_back(new wsjcpp::validator_base64());
  validators.push_back(new wsjcpp::validator_int());
  validators.push_back(new wsjcpp::validator_hex());

  std::string sResult = "";
  for (int i = 0; i < validators.size(); i++) {
    wsjcpp::validator<std::string> *pValidator = validators[i];
    std::string sError;
    if (sResult.size() > 0) {
      sResult += ",";
    }
    if (pValidator->is_valid(sArg1, sError)) {
      sResult += " +" + pValidator->name();
      // WsjcppLog::ok(TAG, "ok -> [" + pValidator->name() + "]: '" + sArg1 + "'");
    } else {
      sResult += " -" + pValidator->name();
      // WsjcppLog::err(TAG, "fail -> [" + pValidator->name() + "]: '" + sArg1 + "' - " + sError);
    }
  }
  std::cout << sResult << std::endl;
  return 0;
}
