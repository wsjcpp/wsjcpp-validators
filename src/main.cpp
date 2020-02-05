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

    // WSJCppLog::info(TAG, "Hello");
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

    std::vector<WSJCppValidatorStringBase *> vValidators;
    // vValidators.push_back(new WSJCppValidatorStringLength(5, 100));
    // vValidators.push_back(new WSJCppValidatorStringLength(1, 5));
    vValidators.push_back(new WSJCppValidatorEmail());
    vValidators.push_back(new WSJCppValidatorUUID());
    vValidators.push_back(new WSJCppValidatorStringListBase("lang", {"en", "de", "ru"}));
    vValidators.push_back(new WSJCppValidatorStringRegexpBase("testre", "^[a-zA-Z]+$"));
    vValidators.push_back(new WSJCppValidatorJWT());
    vValidators.push_back(new WSJCppValidatorDate());
    vValidators.push_back(new WSJCppValidatorTimeH24());
    vValidators.push_back(new WSJCppValidatorDateTime());
    // vValidators.push_back(new WSJCppValidatorURL());
    vValidators.push_back(new WSJCppValidatorBase64());
    vValidators.push_back(new WSJCppValidatorNumber());
    vValidators.push_back(new WSJCppValidatorHex());

    std::string sResult = "";
    for (int i = 0; i < vValidators.size(); i++) {
        WSJCppValidatorStringBase *pValidator = vValidators[i];
        std::string sError;
        if (sResult.size() > 0) {
            sResult += ",";
        }
        if (pValidator->isValid(sArg1, sError)) {
            sResult += " +" + pValidator->getTypeName();
            // WSJCppLog::ok(TAG, "ok -> [" + pValidator->getTypeName() + "]: '" + sArg1 + "'");
        } else {
            sResult += " -" + pValidator->getTypeName();
            // WSJCppLog::err(TAG, "fail -> [" + pValidator->getTypeName() + "]: '" + sArg1 + "' - " + sError);
        }
    }
    std::cout << sResult << std::endl;
    return 0;
}
