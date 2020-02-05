#include "wsjcpp_validators.h"


bool WSJCppValidators::isValidDate(const std::string &sValue, std::string &sError) {
    int nSize = sValue.size();
    if (nSize != 10) {
        sError = "Invalid size format expected length 10";
        return false;
    }

    for (int i = 0; i < 10; i++) {
        char c = sValue[i];
        if (i == 4 || i == 7) {
            if (c != '-') {
                sError = "Expected '-' in " + std::to_string(i) + " position, but got '";
                sError += c;
                sError += "'";
                return false;
            }
            continue;
        }
        if (c < '0' || c > '9') {
            sError = "Unexpected char '";
            sError += c;
            sError += "' in " + std::to_string(i) + " position";
            return false;
        }

    }
    // 2020-01-01
    std::string sYear = sValue.substr(0,4);
    int nYear = std::atoi(sYear.c_str());

    std::string sMonth = sValue.substr(5,2);
    int nMonth = std::atoi(sMonth.c_str());
    if (nMonth < 1 || nMonth > 12) {
        sError = "Invalid value nunber of month '" + std::to_string(nMonth) + "' expected 01..12";
        return false;
    }

    int nMaxDay = 0;
    if (nMonth == 1 || nMonth == 3 || nMonth == 5 || nMonth == 7 || nMonth == 8 || nMonth == 10 || nMonth == 12) {
        nMaxDay = 31;
    } else if (nMonth == 4 || nMonth == 6 || nMonth == 9 || nMonth == 11) {
        nMaxDay = 30;
    } else if (nMonth == 2 && nYear % 4 == 0) {
        nMaxDay = 29;
    } else if (nMonth == 2 && nYear % 4 != 0) {
        nMaxDay = 28;
    }

    std::string sDay = sValue.substr(8,2);
    int nDay = std::atoi(sDay.c_str());
    if (nDay < 1 || nDay > nMaxDay) {
        sError = "Invalid value number of day '" + std::to_string(nDay) + "' expected 01.." + std::to_string(nMaxDay);
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------

bool WSJCppValidators::isValidTimeH24(const std::string &sValue, std::string &sError) {
    int nSize = sValue.size();
    if (nSize != 8) {
        sError = "Invalid size format expected length 8 ";
        return false;
    }

    for (int i = 0; i < 8; i++) {
        char c = sValue[i];
        if (i == 2 || i == 5) {
            if (c != ':') {
                sError = "Expected ':' in " + std::to_string(i) + " position, but got '";
                sError += c;
                sError += "'";
                return false;
            }
            continue;
        }
        if (c < '0' || c > '9') {
            sError = "Unexpected char '";
            sError += c;
            sError += "' in " + std::to_string(i) + " position";
            return false;
        }

    }

    std::string sHours = sValue.substr(0,2);
    int nHours = std::atoi(sHours.c_str());
    if (nHours > 23) {
        sError = "Invalid value of hours '" + std::to_string(nHours) + "' expected 00..23";
        return false;
    }
    std::string sMinutes = sValue.substr(3,2);
    int nMinutes = std::atoi(sMinutes.c_str());
    if (nMinutes > 59) {
        sError = "Invalid value of minutes '" + std::to_string(nMinutes) + "' expected 00..59";
        return false;
    }

    std::string sSeconds = sValue.substr(6,2);
    int nSeconds = std::atoi(sSeconds.c_str());
    if (nSeconds > 59) {
        sError = "Invalid value of seconds '" + std::to_string(nSeconds) + "' expected 00..59";
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------
// WSJCppValidatorStringBase

WSJCppValidatorStringBase::WSJCppValidatorStringBase(const std::string &sTypeName) {
    TAG = "WSJCppValidatorStringBase";
    m_sTypeName = sTypeName;
}

// ----------------------------------------------------------------------

WSJCppValidatorType WSJCppValidatorStringBase::getBaseType() {
    return WSJCppValidatorType::WSJCPP_VALIDATOR_STRING;
}

// ----------------------------------------------------------------------

std::string WSJCppValidatorStringBase::getTypeName() {
    return m_sTypeName;
}

// ----------------------------------------------------------------------
// WSJCppValidatorStringRegexpBase

WSJCppValidatorStringRegexpBase::WSJCppValidatorStringRegexpBase(const std::string &typeName, const std::string &sValidator)
: WSJCppValidatorStringBase(typeName) {
    TAG = "ValidatorStringRegexpBase"; 
    m_sValidator = sValidator;
    m_rxValidator = std::regex(sValidator);
}

// ----------------------------------------------------------------------

bool WSJCppValidatorStringRegexpBase::isValid(const std::string &sValue, std::string &sError) {
    if (!std::regex_match(sValue, m_rxValidator)) {
        sError = getTypeName() + " - Value must match regular expression " + m_sValidator;
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------
// WSJCppValidatorStringListBase

WSJCppValidatorStringListBase::WSJCppValidatorStringListBase(const std::string &sTypeName, const std::vector<std::string> &vListValues)
: WSJCppValidatorStringBase(sTypeName) {
    m_vListValues = vListValues;
}

// ----------------------------------------------------------------------

bool WSJCppValidatorStringListBase::isValid(const std::string &sValue, std::string &sError) {
    if (std::find(m_vListValues.begin(), m_vListValues.end(), sValue) != m_vListValues.end()) {
        return true;
    }
    sError = getTypeName() + " expected one of [";
    for (int i = 0; i < m_vListValues.size(); i++) {
        sError += "'" + m_vListValues[i] + "'";
        if (i < m_vListValues.size() - 1) {
            sError += ", ";
        }
    }
    sError += "]";
    return false;
}

// ----------------------------------------------------------------------
// WSJCppValidatorEmail

WSJCppValidatorEmail::WSJCppValidatorEmail()
: WSJCppValidatorStringRegexpBase(
    "email",
    "^[0-9a-zA-Z]{1}[0-9a-zA-Z-._]*[0-9a-zA-Z]{1}@[0-9a-zA-Z]{1}[-.0-9a-zA-Z]*[0-9a-zA-Z]{1}\\.[a-zA-Z]{2,6}$"
) {
    TAG = "WSJCppValidatorEmail";
}

// ----------------------------------------------------------------------
// WSJCppValidatorUUID

WSJCppValidatorUUID::WSJCppValidatorUUID()
: WSJCppValidatorStringRegexpBase(
    "uuid",
    "^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$"
) {
    TAG = "WSJCppValidatorUUID";
}

// ----------------------------------------------------------------------
// WSJCppValidatorStringLenght

WSJCppValidatorStringLength::WSJCppValidatorStringLength(int nMinLength, int nMaxLength) 
: WSJCppValidatorStringBase("string_length") {
    TAG = "WSJCppValidatorStringLenght";
    m_nMinLength = nMinLength;
    m_nMaxLength = nMaxLength;
}

// ----------------------------------------------------------------------

bool WSJCppValidatorStringLength::isValid(const std::string &sValue, std::string &sError) {
    if (sValue.length() < m_nMinLength) {
        sError = "Value must have more than " + std::to_string(m_nMinLength) + " simbols";
        return false;
    }

    if (sValue.length() > m_nMaxLength) {
        sError = "Value must have less than " + std::to_string(m_nMaxLength) + " simbols";
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------
// WSJCppValidatorJWT

WSJCppValidatorJWT::WSJCppValidatorJWT()
: WSJCppValidatorStringRegexpBase(
    "jwt",
    "^[A-Za-z0-9-_=]+\\.[A-Za-z0-9-_=]+\\.?[A-Za-z0-9-_.+/=]*$"
) {
    TAG = "WSJCppValidatorJWT";
}

// ----------------------------------------------------------------------
// WSJCppValidatorDate

WSJCppValidatorDate::WSJCppValidatorDate()
: WSJCppValidatorStringBase("date") {
    TAG = "WSJCppValidatorDate";
}

// ----------------------------------------------------------------------

bool WSJCppValidatorDate::isValid(const std::string &sValue, std::string &sError) {
    return WSJCppValidators::isValidDate(sValue, sError);
}

// ----------------------------------------------------------------------
// WSJCppValidatorTimeH24

WSJCppValidatorTimeH24::WSJCppValidatorTimeH24()
: WSJCppValidatorStringBase("time_h24") {
    TAG = "WSJCppValidatorTime";
}

// ----------------------------------------------------------------------

bool WSJCppValidatorTimeH24::isValid(const std::string &sValue, std::string &sError) {
    return WSJCppValidators::isValidTimeH24(sValue, sError);
}


// ----------------------------------------------------------------------
// WSJCppValidatorBase64

WSJCppValidatorBase64::WSJCppValidatorBase64() 
: WSJCppValidatorStringBase("base64") {
    TAG = "WSJCppValidatorBase64";
}

// ----------------------------------------------------------------------

bool WSJCppValidatorBase64::isValid(const std::string &sValue, std::string &sError) {
    int nSize = sValue.size();
    if (nSize % 4 != 0) {
        sError = "Value size must be a multiple of 4";
        return false;
    }
    bool bLastChar = false;
    for (int i = 0; i < nSize; i++) {
        char c = sValue[i];
        if (!bLastChar && c == '=') {
            bLastChar = true;
            continue;
        }
        if (bLastChar && c == '=') {
            continue;
        }

        if (bLastChar && c != '=') {
            sError = "Unexpected char '";
            sError += c;
            sError += "' after '=' in " + std::to_string(i) + " position";
            return false;
        }

        if (
            (c < 'A' || c > 'Z')
            && (c < 'a' || c > 'z')
            && (c < '0' || c > '9')
            && c != '+'
            && c != '/'
        ) {
            sError = "Unexpected char '";
            sError += c;
            sError += "' in " + std::to_string(i) + " position";
            return false;
        }
    }
    return true;
}


// ----------------------------------------------------------------------
// WSJCppValidatorNumber

WSJCppValidatorNumber::WSJCppValidatorNumber() 
: WSJCppValidatorStringBase("number") {
    TAG = "WSJCppValidatorNumber";
}

// ----------------------------------------------------------------------

bool WSJCppValidatorNumber::isValid(const std::string &sValue, std::string &sError) {
    int nSize = sValue.size();
    bool bHasOneAndMoreNumbers = false;
    for (int i = 0; i < nSize; i++) {
        char c = sValue[i];
        if (c == '-' && i == 0) {
            continue;
        }
        if (c < '0' || c > '9') {
            sError = "Unexpected char '";
            sError += c;
            sError += "' in " + std::to_string(i) + " position";
            return false;
        }
        bHasOneAndMoreNumbers = true;
    }
    return bHasOneAndMoreNumbers;
}

// ----------------------------------------------------------------------
// WSJCppValidatorHex

WSJCppValidatorHex::WSJCppValidatorHex() 
: WSJCppValidatorStringBase("hex") {
    TAG = "WSJCppValidatorHex";
}

// ----------------------------------------------------------------------

bool WSJCppValidatorHex::isValid(const std::string &sValue, std::string &sError) {
    int nSize = sValue.size();
    if (nSize == 0) {
        sError = "Empty string";
        return false;
    }
    for (int i = 0; i < nSize; i++) {
        char c = sValue[i];
        if (c == '-' && i == 0) {
            continue;
        }
        if ((c < '0' || c > '9') && (c < 'a' || c > 'f') && (c < 'A' || c > 'F')) {
            sError = "Unexpected char '";
            sError += c;
            sError += "' in " + std::to_string(i) + " position";
            return false;
        }
    }
    return true;
}
