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
// #include <arpa/inet.h>
#include <wsjcpp_core.h>

namespace wsjcpp {

validator_date::validator_date() : validator<std::string>("date") {
}

bool validator_date::is_valid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_date(value, error);
}

validator_regexp::validator_regexp(const std::string &name, const std::string &_regexp)
    : validator<std::string>(name) {
  m_sValidator = _regexp;
  m_rxValidator = std::regex(_regexp);
}

bool validator_regexp::is_valid(const std::string &value, std::string &error) {
  if (!std::regex_match(value, m_rxValidator)) {
    error = name() + " - Value must match regular expression " + m_sValidator;
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// validator_str_list

validator_str_list::validator_str_list(const std::string &sTypeName, const std::vector<std::string> &vListValues)
    : validator<std::string>(sTypeName) {
  m_vListValues = vListValues;
}

bool validator_str_list::is_valid(const std::string &value, std::string &error) {
  if (std::find(m_vListValues.begin(), m_vListValues.end(), value) != m_vListValues.end()) {
    return true;
  }
  error = name() + " expected one of [";
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
// validator_email

validator_email::validator_email()
    : validator_regexp("email", "^[0-9a-zA-Z]{1}[0-9a-zA-Z-._]*[0-9a-zA-Z]{1}@[0-9a-zA-Z]{1}"
                                            "[-.0-9a-zA-Z]*[0-9a-zA-Z]{1}\\.[a-zA-Z]{2,6}$") {
}

// ----------------------------------------------------------------------
// validator_uuid

validator_uuid::validator_uuid()
    : validator_regexp("uuid", "^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-"
                                           "f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$") {
}

// ----------------------------------------------------------------------
// validator_strlen

validator_strlen::validator_strlen(int min_length, int max_length)
    : validator<std::string>("string_length") {
  m_min_length = min_length;
  m_max_length = max_length;
}

bool validator_strlen::is_valid(const std::string &value, std::string &error) {
  if (value.length() < m_min_length) {
    error = "Value must have more than " + std::to_string(m_min_length) + " symbols";
    return false;
  }

  if (value.length() > m_max_length) {
    error = "Value must have less than " + std::to_string(m_max_length) + " symbols";
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// validator_jwt

validator_jwt::validator_jwt()
    : validator_regexp("jwt", "^[A-Za-z0-9-_=]+\\.[A-Za-z0-9-_=]+\\.?[A-Za-z0-9-_.+/=]*$") {
}

// ----------------------------------------------------------------------
// validator_time24

validator_time24::validator_time24() : validator<std::string>("time_h24") {
}

bool validator_time24::is_valid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_time24(value, error);
}

// ----------------------------------------------------------------------
// validator_datetime

validator_datetime::validator_datetime() : validator<std::string>("datetime") {
}

bool validator_datetime::is_valid(const std::string &value, std::string &error) {
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
  if (!wsjcpp::is_valid_time24(sTime, error)) {
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// validator_url

validator_url::validator_url() : validator<std::string>("url") {
  m_rx_ip4_format = std::regex("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
}

bool validator_url::is_valid(const std::string &value, std::string &error) {
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

  if (std::regex_match(sAddress, m_rx_ip4_format)) {
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
// validator_domain_name

validator_domain_name::validator_domain_name() : validator<std::string>("domain_name") {
}

bool validator_domain_name::is_valid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_domain_name(value, error);
}

// ----------------------------------------------------------------------
// validator_base64

validator_base64::validator_base64() : validator<std::string>("base64") {
}

// ----------------------------------------------------------------------

bool validator_base64::is_valid(const std::string &value, std::string &error) {
  return wsjcpp::is_valid_base64(value, error);
}

// ----------------------------------------------------------------------
// validator_int

validator_int::validator_int() : validator<std::string>("int") {
}

// ----------------------------------------------------------------------

bool validator_int::is_valid(const std::string &value, std::string &error) {
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
// validator_hex

validator_hex::validator_hex() : validator<std::string>("hex") {
}

// ----------------------------------------------------------------------

bool validator_hex::is_valid(const std::string &value, std::string &error) {
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
// validator_int_min

validator_int_min::validator_int_min(int min_value) : validator<int>("int_min") {
  m_min_value = min_value;
}

// ----------------------------------------------------------------------

bool validator_int_min::is_valid(const int &value, std::string &error) {
  if (value < m_min_value) {
    error = "Value must be more or equal then " + std::to_string(m_min_value);
    return false;
  }
  return true;
}

// ----------------------------------------------------------------------
// validator_int_max

validator_int_max::validator_int_max(int max_value) : validator<int>("int_max") {
  m_max_value = max_value;
}

// ----------------------------------------------------------------------

bool validator_int_max::is_valid(const int &value, std::string &error) {
  if (value > m_max_value) {
    error = "Value must be less or equal then " + std::to_string(m_max_value);
    return false;
  }
  return true;
}

} // namespace wsjcpp
