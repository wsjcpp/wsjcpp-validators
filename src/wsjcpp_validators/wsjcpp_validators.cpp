/*
MIT License

Copyright (c) 2020-2026 wsjcpp

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

#include "wsjcpp_validators.h"
#include <arpa/inet.h>
#include <wsjcpp_core.h>

namespace wsjcpp {

bool is_valid_date(const std::string &value, std::string &error) {
  int nSize = value.size();
  if (nSize != 10) {
    error = "Invalid size format expected length 10";
    return false;
  }

  for (int i = 0; i < 10; i++) {
    char c = value[i];
    if (i == 4 || i == 7) {
      if (c != '-') {
        error = "Expected '-' in " + std::to_string(i) + " position, but got '";
        error += c;
        error += "'";
        return false;
      }
      continue;
    }
    if (c < '0' || c > '9') {
      error = "Unexpected char '";
      error += c;
      error += "' in " + std::to_string(i) + " position";
      return false;
    }
  }
  // 2020-01-01
  std::string sYear = value.substr(0, 4);
  int nYear = std::atoi(sYear.c_str());

  std::string sMonth = value.substr(5, 2);
  int nMonth = std::atoi(sMonth.c_str());
  if (nMonth < 1 || nMonth > 12) {
    error = "Invalid value number of month '" + std::to_string(nMonth) + "' expected 01..12";
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

  std::string sDay = value.substr(8, 2);
  int nDay = std::atoi(sDay.c_str());
  if (nDay < 1 || nDay > nMaxDay) {
    error = "Invalid value number of day '" + std::to_string(nDay) + "' expected 01.." + std::to_string(nMaxDay);
    return false;
  }
  return true;
}

bool is_valid_time_h24(const std::string &value, std::string &error) {
  int nSize = value.size();
  if (nSize != 8) {
    error = "Invalid size format expected length 8";
    return false;
  }

  for (int i = 0; i < 8; i++) {
    char c = value[i];
    if (i == 2 || i == 5) {
      if (c != ':') {
        error = "Expected ':' in " + std::to_string(i) + " position, but got '";
        error += c;
        error += "'";
        return false;
      }
      continue;
    }
    if (c < '0' || c > '9') {
      error = "Unexpected char '";
      error += c;
      error += "' in " + std::to_string(i) + " position";
      return false;
    }
  }

  std::string sHours = value.substr(0, 2);
  int nHours = std::atoi(sHours.c_str());
  if (nHours > 23) {
    error = "Invalid value of hours '" + std::to_string(nHours) + "' expected 00..23";
    return false;
  }
  std::string sMinutes = value.substr(3, 2);
  int nMinutes = std::atoi(sMinutes.c_str());
  if (nMinutes > 59) {
    error = "Invalid value of minutes '" + std::to_string(nMinutes) + "' expected 00..59";
    return false;
  }

  std::string sSeconds = value.substr(6, 2);
  int nSeconds = std::atoi(sSeconds.c_str());
  if (nSeconds > 59) {
    error = "Invalid value of seconds '" + std::to_string(nSeconds) + "' expected 00..59";
    return false;
  }
  return true;
}

bool is_valid_domain_name(const std::string &value, std::string &error) {
  std::vector<std::string> vSubDomains;
  std::string sTmpDomain = "";
  int nAddressLen = value.size();
  char cPrev = 0;
  for (int i = 0; i < nAddressLen; i++) {
    char c = value[i];
    if (i == 0 && c == '.') {
      error = "Domain Name '" + value + "' could not be start on '.'";
      return false;
    }
    if (c == '.') {
      if (sTmpDomain != "") {
        vSubDomains.push_back(sTmpDomain);
        sTmpDomain = "";
        continue;
      } else {
        error = "Domain Name '" + value + "' could not contains '..'";
        return false;
      }
    }
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-') {
      sTmpDomain += c;
      if (cPrev == '-' && c == cPrev) {
        error = "Domain Name '" + value + "' could not two times in a row '";
        error += c;
        error += c;
        error += "'";
        return false;
      }
      cPrev = c;
    } else {
      error = "Domain Name '" + value + "' contains unexpected '";
      error += c;
      error += "'";
      return false;
    }
  }

  if (sTmpDomain != "") {
    vSubDomains.push_back(sTmpDomain);
    sTmpDomain = "";
  } else {
    error = "Domain Name '" + value + "' could not contains '.' on end";
    return false;
  }

  if (vSubDomains.size() < 2) {
    error = "Domain Name '" + value + "' must contains least one dot";
    return false;
  }
  std::string sRootDomain = vSubDomains[vSubDomains.size() - 1];
  if (sRootDomain.size() < 2) {
    error = "Domain Name '" + value + "' has wrong root domain '" + sRootDomain + "' length must be more then 1";
    return false;
  }
  for (int i = 0; i < sRootDomain.size(); i++) {
    char c = sRootDomain[i];
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')) {
      error = "Domain Name '" + value + "' has wrong root domain '" + sRootDomain + "' must have only chars";
      return false;
    }
  }

  for (int i = 0; i < vSubDomains.size(); i++) {
    std::string sDomain = vSubDomains[i];
    char c = sDomain[0];
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9')) {
      error = "Subdomain '" + sDomain + "' could not start on '";
      error += c;
      error += "'";
      return false;
    }
    c = sDomain[sDomain.size() - 1];
    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9')) {
      error = "Subdomain '" + sDomain + "' could not end on '";
      error += c;
      error += "'";
      return false;
    }
  }
  return true;
}

bool is_valid_port(const std::string &value, std::string &error) {
  int nPort = std::atoi(value.c_str());
  return wsjcpp::is_valid_port(nPort, error);
}

bool is_valid_port(int nValue, std::string &error) {
  if (nValue < 1 || nValue > 65535) {
    error = "Port '" + std::to_string(nValue) + "' must be more then 0 and less then 65536";
    return false;
  }
  return true;
}

bool is_valid_url_protocol(const std::string &value, std::string &error) {
  if (value != "http" && value != "https" && value != "ws" && value != "wss" && value != "ftp" &&
      value != "ssl") {
    error = "Unexpected protocol '" + value + "'";
    return false;
  }
  return true;
}

bool is_valid_base64(const std::string &value, std::string &error) {
  int nSize = value.size();
  if (nSize % 4 != 0) {
    error = "Value size must be a multiple of 4";
    return false;
  }
  bool bLastChar = false;
  for (int i = 0; i < nSize; i++) {
    char c = value[i];
    if (!bLastChar && c == '=') {
      bLastChar = true;
      continue;
    }
    if (bLastChar && c == '=') {
      continue;
    }

    if (bLastChar && c != '=') {
      error = "Unexpected char '";
      error += c;
      error += "' after '=' in " + std::to_string(i) + " position";
      return false;
    }

    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9') && c != '+' && c != '/') {
      error = "Unexpected char '";
      error += c;
      error += "' in " + std::to_string(i) + " position";
      return false;
    }
  }
  return true;
}


} // namespace wsjcpp

// ----------------------------------------------------------------------
// WsjcppValidatorStringBase

WsjcppValidatorStringBase::WsjcppValidatorStringBase(const std::string &sTypeName) {
  TAG = "WsjcppValidatorStringBase";
  m_sTypeName = sTypeName;
}

WsjcppValidatorType WsjcppValidatorStringBase::getBaseType() {
  return WsjcppValidatorType::WSJCPP_VALIDATOR_STRING;
}

std::string WsjcppValidatorStringBase::getTypeName() {
  return m_sTypeName;
}

// ----------------------------------------------------------------------
// WsjcppValidatorStringRegexpBase

WsjcppValidatorStringRegexpBase::WsjcppValidatorStringRegexpBase(const std::string &typeName,
                                                                 const std::string &sValidator)
    : WsjcppValidatorStringBase(typeName) {
  TAG = "ValidatorStringRegexpBase";
  m_sValidator = sValidator;
  m_rxValidator = std::regex(sValidator);
}

bool WsjcppValidatorStringRegexpBase::isValid(const std::string &value, std::string &error) {
  if (!std::regex_match(value, m_rxValidator)) {
    error = getTypeName() + " - Value must match regular expression " + m_sValidator;
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// WsjcppValidatorStringListBase

WsjcppValidatorStringListBase::WsjcppValidatorStringListBase(const std::string &sTypeName,
                                                             const std::vector<std::string> &vListValues)
    : WsjcppValidatorStringBase(sTypeName) {
  m_vListValues = vListValues;
}

bool WsjcppValidatorStringListBase::isValid(const std::string &value, std::string &error) {
  if (std::find(m_vListValues.begin(), m_vListValues.end(), value) != m_vListValues.end()) {
    return true;
  }
  error = getTypeName() + " expected one of [";
  for (int i = 0; i < m_vListValues.size(); i++) {
    error += "'" + m_vListValues[i] + "'";
    if (i < m_vListValues.size() - 1) {
      error += ", ";
    }
  }
  error += "]";
  return false;
}

// ----------------------------------------------------------------------
// WsjcppValidatorEmail

WsjcppValidatorEmail::WsjcppValidatorEmail()
    : WsjcppValidatorStringRegexpBase("email", "^[0-9a-zA-Z]{1}[0-9a-zA-Z-._]*[0-9a-zA-Z]{1}@[0-9a-zA-Z]{1}"
                                               "[-.0-9a-zA-Z]*[0-9a-zA-Z]{1}\\.[a-zA-Z]{2,6}$") {
  TAG = "WsjcppValidatorEmail";
}

// ----------------------------------------------------------------------
// WsjcppValidatorUUID

WsjcppValidatorUUID::WsjcppValidatorUUID()
    : WsjcppValidatorStringRegexpBase("uuid", "^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-"
                                              "f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$") {
  TAG = "WsjcppValidatorUUID";
}

// ----------------------------------------------------------------------
// WsjcppValidatorStringLength

WsjcppValidatorStringLength::WsjcppValidatorStringLength(int nMinLength, int nMaxLength)
    : WsjcppValidatorStringBase("string_length") {
  TAG = "WsjcppValidatorStringLength";
  m_nMinLength = nMinLength;
  m_nMaxLength = nMaxLength;
}

bool WsjcppValidatorStringLength::isValid(const std::string &value, std::string &error) {
  if (value.length() < m_nMinLength) {
    error = "Value must have more than " + std::to_string(m_nMinLength) + " symbols";
    return false;
  }

  if (value.length() > m_nMaxLength) {
    error = "Value must have less than " + std::to_string(m_nMaxLength) + " symbols";
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// WsjcppValidatorJWT

WsjcppValidatorJWT::WsjcppValidatorJWT()
    : WsjcppValidatorStringRegexpBase("jwt", "^[A-Za-z0-9-_=]+\\.[A-Za-z0-9-_=]+\\.?[A-Za-z0-9-_.+/=]*$") {
  TAG = "WsjcppValidatorJWT";
}

// ----------------------------------------------------------------------
// WsjcppValidatorDate

WsjcppValidatorDate::WsjcppValidatorDate() : WsjcppValidatorStringBase("date") {
  TAG = "WsjcppValidatorDate";
}

// ----------------------------------------------------------------------

bool WsjcppValidatorDate::isValid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_date(value, error);
}

// ----------------------------------------------------------------------
// WsjcppValidatorTimeH24

WsjcppValidatorTimeH24::WsjcppValidatorTimeH24() : WsjcppValidatorStringBase("time_h24") {
  TAG = "WsjcppValidatorTime";
}

bool WsjcppValidatorTimeH24::isValid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_time_h24(value, error);
}

// ----------------------------------------------------------------------
// WsjcppValidatorDateTime

WsjcppValidatorDateTime::WsjcppValidatorDateTime() : WsjcppValidatorStringBase("datetime") {
  TAG = "WsjcppValidatorDateTime";
}

bool WsjcppValidatorDateTime::isValid(const std::string &value, std::string &error) {
  int nSize = value.size();
  // '2020-01-01T00:00:00'
  if (nSize != 19) {
    error = "Invalid size format expected length 19";
    return false;
  }
  std::string sDate = value.substr(0, 10);
  if (!wsjcpp::is_valid_date(sDate, error)) {
    return false;
  }
  if (value[10] != 'T') {
    error = "Expected 'T' in 10 position, but got '";
    error += value[10];
    error += "'";
    return false;
  }
  std::string sTime = value.substr(11, 8);
  if (!wsjcpp::is_valid_time_h24(sTime, error)) {
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// WsjcppValidatorURL

WsjcppValidatorURL::WsjcppValidatorURL() : WsjcppValidatorStringBase("url") {
  TAG = "WsjcppValidatorURL";
  m_rxLikeIPv4Format = std::regex("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
}

bool WsjcppValidatorURL::isValid(const std::string &value, std::string &error) {
  if (value.size() == 0) {
    error = "Value is empty";
    return false;
  }
  if (value.find(".") == std::string::npos) {
    error = "Must contain at least one dot";
    return false;
  }
  std::string sProtocol = wsjcpp::extract_url_protocol(value);
  if (!wsjcpp::is_valid_url_protocol(sProtocol, error)) {
    return false;
  }

  int nStartPos = sProtocol.length() + 3;
  std::string sAuthorityAddressPath = "";
  for (int i = nStartPos; i < value.size(); i++) {
    char c = value[i];
    if (c == '?') {
      break;
    }
    sAuthorityAddressPath += c;
  }
  std::string sQuery = value.substr(sProtocol.length() + 3 + sAuthorityAddressPath.size());
  std::string sAddressAndPath = sAuthorityAddressPath;

  int nPosAuthority = sAuthorityAddressPath.find("@");
  std::string sAuthority = "";
  if (nPosAuthority != std::string::npos) {
    sAuthority = sAuthorityAddressPath.substr(0, nPosAuthority);
    sAddressAndPath = sAuthorityAddressPath.substr(nPosAuthority + 1);
  }
  if (sAuthority != "") {
    // error = "TODO check username and password sAuthority= [" + sAuthority +
    // "]";
    // -.~_!$&'()*+,;=:%40:80%2f::::::
    // WsjcppLog::warn(TAG, error);
    // return false;
  }
  std::string sAddress = sAddressAndPath;
  std::string sPath = "";
  int nPosAddress = sAddressAndPath.find("/");
  if (nPosAddress != std::string::npos) {
    sAddress = sAddressAndPath.substr(0, nPosAddress);
    sPath = sAddressAndPath.substr(nPosAddress);
  }

  if (sAddress.size() == 0) {
    error = "Address could not be empty";
    return false;
  }

  int nPosPort = sAddress.find(":");
  std::string sPort = "";
  if (sAddress.find(":") != std::string::npos) {
    sPort = sAddress.substr(nPosPort + 1);
    sAddress = sAddress.substr(0, nPosPort);
  }

  if (sPort != "") {
    if (!wsjcpp::is_valid_port(sPort, error)) {
      return false;
    }
  }

  if (std::regex_match(sAddress, m_rxLikeIPv4Format)) {
    if (!wsjcpp::is_valid_ip4(sAddress, error)) {
      return false;
    }
    if (sPort != "") {
      int nPort = std::atoi(sPort.c_str());
      if (nPort < 1 || nPort > 65535) {
        error = "Port '" + std::to_string(nPort) + "' must be more then 0 and less then 65536";
        return false;
      }
    }
  } else {
    if (!wsjcpp::is_valid_domain_name(sAddress, error)) {
      return false;
    }
  }

  if ((sPath == "" || sPath == "/") && sQuery == "") {
    return true;
  }

  if (sPath != "") {
    for (int i = 0; i < sPath.length(); i++) {
      char c = sPath[i];
      if (c == ' ') {
        error = "Path could not contains whitespace ' '";
        return false;
      }
    }
  }

  if (sQuery != "") {
    for (int i = 0; i < sQuery.length(); i++) {
      char c = sQuery[i];
      if (c == ' ') {
        error = "Query could not contains whitespace ' ' (must be encoded)";
        return false;
      }
    }
  }

  // error = "sAddressAndPath=[" + sAddressAndPath + "], , sAddress=[" +
  // sAddress + "]";
  return true;
}

// ----------------------------------------------------------------------
// WsjcppValidatorDomainName

WsjcppValidatorDomainName::WsjcppValidatorDomainName() : WsjcppValidatorStringBase("domain_name") {
  TAG = "WsjcppValidatorDomainName";
}

bool WsjcppValidatorDomainName::isValid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_domain_name(value, error);
}

// ----------------------------------------------------------------------
// WsjcppValidatorBase64

WsjcppValidatorBase64::WsjcppValidatorBase64() : WsjcppValidatorStringBase("base64") {
  TAG = "WsjcppValidatorBase64";
}

// ----------------------------------------------------------------------

bool WsjcppValidatorBase64::isValid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_base64(value, error);
}

// ----------------------------------------------------------------------
// WsjcppValidatorNumber

WsjcppValidatorNumber::WsjcppValidatorNumber() : WsjcppValidatorStringBase("number") {
  TAG = "WsjcppValidatorNumber";
}

// ----------------------------------------------------------------------

bool WsjcppValidatorNumber::isValid(const std::string &value, std::string &error) {
  int nSize = value.size();
  bool bHasOneAndMoreNumbers = false;
  for (int i = 0; i < nSize; i++) {
    char c = value[i];
    if (c == '-' && i == 0) {
      continue;
    }
    if (c < '0' || c > '9') {
      error = "Unexpected char '";
      error += c;
      error += "' in " + std::to_string(i) + " position";
      return false;
    }
    bHasOneAndMoreNumbers = true;
  }
  return bHasOneAndMoreNumbers;
}

// ----------------------------------------------------------------------
// WsjcppValidatorHex

WsjcppValidatorHex::WsjcppValidatorHex() : WsjcppValidatorStringBase("hex") {
  TAG = "WsjcppValidatorHex";
}

// ----------------------------------------------------------------------

bool WsjcppValidatorHex::isValid(const std::string &value, std::string &error) {
  int nSize = value.size();
  if (nSize == 0) {
    error = "Empty string";
    return false;
  }
  for (int i = 0; i < nSize; i++) {
    char c = value[i];
    if (c == '-' && i == 0) {
      continue;
    }
    if ((c < '0' || c > '9') && (c < 'a' || c > 'f') && (c < 'A' || c > 'F')) {
      error = "Unexpected char '";
      error += c;
      error += "' in " + std::to_string(i) + " position";
      return false;
    }
  }
  return true;
}

// ----------------------------------------------------------------------
// WsjcppValidatorIntegerBase

WsjcppValidatorIntegerBase::WsjcppValidatorIntegerBase(const std::string &sTypeName) {
  TAG = "WsjcppValidatorIntegerBase";
  m_sTypeName = sTypeName;
}

// ----------------------------------------------------------------------

WsjcppValidatorType WsjcppValidatorIntegerBase::getBaseType() {
  return WsjcppValidatorType::WSJCPP_VALIDATOR_INTEGER;
}

// ----------------------------------------------------------------------

std::string WsjcppValidatorIntegerBase::getTypeName() {
  return m_sTypeName;
}

// ----------------------------------------------------------------------
// WsjcppValidatorIntegerMinValue

WsjcppValidatorIntegerMinValue::WsjcppValidatorIntegerMinValue(int nMinValue)
    : WsjcppValidatorIntegerBase("integer_min_value") {
  TAG = "WsjcppValidatorIntegerMinValue";
  m_nMinValue = nMinValue;
}

// ----------------------------------------------------------------------

bool WsjcppValidatorIntegerMinValue::isValid(int nValue, std::string &error) {
  if (nValue < m_nMinValue) {
    error = "Value must be more or equal then " + std::to_string(m_nMinValue);
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// WsjcppValidatorIntegerMaxValue

WsjcppValidatorIntegerMaxValue::WsjcppValidatorIntegerMaxValue(int nMaxValue)
    : WsjcppValidatorIntegerBase("integer_max_value") {
  TAG = "WsjcppValidatorIntegerMaxValue";
  m_nMaxValue = nMaxValue;
}

// ----------------------------------------------------------------------

bool WsjcppValidatorIntegerMaxValue::isValid(int nValue, std::string &error) {
  if (nValue > m_nMaxValue) {
    error = "Value must be less or equal then " + std::to_string(m_nMaxValue);
    return false;
  }
  return true;
}
