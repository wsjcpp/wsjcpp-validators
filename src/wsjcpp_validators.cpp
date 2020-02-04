#include "wsjcpp_validators.h"

// ----------------------------------------------------------------------
// WJSCppValidatorStringBase

WJSCppValidatorStringBase::WJSCppValidatorStringBase(const std::string &sTypeName) {
    TAG = "WJSCppValidatorStringBase";
    m_sTypeName = sTypeName;
}

// ----------------------------------------------------------------------

WJSCppValidatorType WJSCppValidatorStringBase::getBaseType() {
    return WJSCppValidatorType::WJSCPP_VALIDATOR_STRING;
}

// ----------------------------------------------------------------------

std::string WJSCppValidatorStringBase::getTypeName() {
    return m_sTypeName;
}

// ----------------------------------------------------------------------
// WJSCppValidatorStringRegexpBase

WJSCppValidatorStringRegexpBase::WJSCppValidatorStringRegexpBase(const std::string &typeName, const std::string &sValidator)
: WJSCppValidatorStringBase(typeName) {
    TAG = "ValidatorStringRegexpBase"; 
    m_sValidator = sValidator;
    m_rxValidator = std::regex(sValidator);
}

// ----------------------------------------------------------------------

bool WJSCppValidatorStringRegexpBase::isValid(const std::string &sValue, std::string &sError) {
    if (!std::regex_match(sValue, m_rxValidator)) {
        sError = getTypeName() + " - Value must match regular expression " + m_sValidator;
        return false;
    }
    return true;
}

// ----------------------------------------------------------------------
// WJSCppValidatorStringListBase

WJSCppValidatorStringListBase::WJSCppValidatorStringListBase(const std::string &sTypeName, const std::vector<std::string> &vListValues)
: WJSCppValidatorStringBase(sTypeName) {
    m_vListValues = vListValues;
}

// ----------------------------------------------------------------------

bool WJSCppValidatorStringListBase::isValid(const std::string &sValue, std::string &sError) {
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
// WJSCppValidatorEmail

WJSCppValidatorEmail::WJSCppValidatorEmail()
: WJSCppValidatorStringRegexpBase(
    "email",
    "^[0-9a-zA-Z]{1}[0-9a-zA-Z-._]*[0-9a-zA-Z]{1}@[0-9a-zA-Z]{1}[-.0-9a-zA-Z]*[0-9a-zA-Z]{1}\\.[a-zA-Z]{2,6}$"
) {
    TAG = "WJSCppValidatorEmail";
}

// ----------------------------------------------------------------------
// WJSCppValidatorUUID

WJSCppValidatorUUID::WJSCppValidatorUUID()
: WJSCppValidatorStringRegexpBase(
    "uuid",
    "^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$"
) {
    TAG = "WJSCppValidatorUUID";
}

// ----------------------------------------------------------------------
// WJSCppValidatorStringLenght

WJSCppValidatorStringLength::WJSCppValidatorStringLength(int nMinLength, int nMaxLength) 
: WJSCppValidatorStringBase("string_length") {
    TAG = "WJSCppValidatorStringLenght";
    m_nMinLength = nMinLength;
    m_nMaxLength = nMaxLength;
}

// ----------------------------------------------------------------------

bool WJSCppValidatorStringLength::isValid(const std::string &sValue, std::string &sError) {
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