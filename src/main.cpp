#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include <wsjcpp_validators.h>

int main(int argc, char* argv[]) {
    std::string TAG = "MAIN";

    if (!WSJCppCore::dirExists(".wsjcpp")) {
        WSJCppCore::makeDir(".wsjcpp");
    }
    std::string appLogPath = ".wsjcpp/logs";
    if (!WSJCppCore::dirExists(appLogPath)) {
        WSJCppCore::makeDir(appLogPath);
    }
    WSJCppLog::setPrefixLogFile("wsjcpp_validators");
    WSJCppLog::setLogDirectory(".wsjcpp/logs");

    WSJCppLog::info(TAG, "Hello");
    WSJCppCore::init(
        argc, argv, 
        std::string(WSJCPP_NAME),
        std::string(WSJCPP_VERSION),
        "Evgenii Sopov",
        ""
    );
    if (argc != 2) {
        std::cout << "Usage " << argv[0] << " something" << std::endl;
        return -1;
    }
    std::string sArg1(argv[1]);

    std::vector<WJSCppValidatorStringBase *> vValidators;
    vValidators.push_back(new WJSCppValidatorStringLength(5, 100));
    vValidators.push_back(new WJSCppValidatorStringLength(1, 5));
    vValidators.push_back(new WJSCppValidatorEmail());
    vValidators.push_back(new WJSCppValidatorUUID());
    vValidators.push_back(new WJSCppValidatorStringListBase("lang", {"en", "de", "ru"}));
    vValidators.push_back(new WJSCppValidatorStringRegexpBase("testre", "^[a-zA-Z]+$"));

    for (int i = 0; i < vValidators.size(); i++) {
        WJSCppValidatorStringBase *pValidator = vValidators[i];
        std::string sError;
        if (pValidator->isValid(sArg1, sError)) {
            WSJCppLog::ok(TAG, "ok -> [" + pValidator->getTypeName() + "]: '" + sArg1 + "'");
        } else {
            WSJCppLog::err(TAG, "fail -> [" + pValidator->getTypeName() + "]: '" + sArg1 + "' - " + sError);
        }
    }

    return 0;
}