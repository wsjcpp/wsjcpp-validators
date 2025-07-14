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

#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";

    if (!WsjcppCore::dirExists(".wsjcpp")) {
        WsjcppCore::makeDir(".wsjcpp");
    }
    std::string appLogPath = ".wsjcpp/logs";
    if (!WsjcppCore::dirExists(appLogPath)) {
        WsjcppCore::makeDir(appLogPath);
    }
    WsjcppLog::setPrefixLogFile("wsjcpp_validators");
    WsjcppLog::setLogDirectory(".wsjcpp/logs");

    // WsjcppLog::info(TAG, "Hello");
    WsjcppCore::init(
        argc, argv, 
        std::string(WSJCPP_APP_NAME),
        std::string(WSJCPP_APP_VERSION),
        "Evgenii Sopov",
        ""
    );
    if (argc != 2) {
        std::cout << "Usage " << argv[0] << " something" << std::endl;
        return -1;
    }
    std::string sArg1(argv[1]);

    std::vector<WsjcppValidatorStringBase *> vValidators;
    // vValidators.push_back(new WsjcppValidatorStringLength(5, 100));
    // vValidators.push_back(new WsjcppValidatorStringLength(1, 5));
    vValidators.push_back(new WsjcppValidatorEmail());
    vValidators.push_back(new WsjcppValidatorUUID());
    vValidators.push_back(new WsjcppValidatorStringListBase("lang", {"en", "de", "ru"}));
    vValidators.push_back(new WsjcppValidatorStringRegexpBase("testre", "^[a-zA-Z]+$"));
    vValidators.push_back(new WsjcppValidatorJWT());
    vValidators.push_back(new WsjcppValidatorDate());
    vValidators.push_back(new WsjcppValidatorTimeH24());
    vValidators.push_back(new WsjcppValidatorDateTime());
    // vValidators.push_back(new WsjcppValidatorURL());
    vValidators.push_back(new WsjcppValidatorBase64());
    vValidators.push_back(new WsjcppValidatorNumber());
    vValidators.push_back(new WsjcppValidatorHex());

    std::string sResult = "";
    for (int i = 0; i < vValidators.size(); i++) {
        WsjcppValidatorStringBase *pValidator = vValidators[i];
        std::string sError;
        if (sResult.size() > 0) {
            sResult += ",";
        }
        if (pValidator->isValid(sArg1, sError)) {
            sResult += " +" + pValidator->getTypeName();
            // WsjcppLog::ok(TAG, "ok -> [" + pValidator->getTypeName() + "]: '" + sArg1 + "'");
        } else {
            sResult += " -" + pValidator->getTypeName();
            // WsjcppLog::err(TAG, "fail -> [" + pValidator->getTypeName() + "]: '" + sArg1 + "' - " + sError);
        }
    }
    std::cout << sResult << std::endl;
    return 0;
}
