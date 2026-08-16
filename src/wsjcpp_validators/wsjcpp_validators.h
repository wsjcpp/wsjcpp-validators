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

#pragma once

#include <regex>
#include <string>
#include <vector>

namespace wsjcpp {

template <typename T> class validator {
public:
  validator(const std::string &name) : m_name(name) {
  }
  virtual const std::string &name() const {
    return m_name;
  };
  virtual bool is_valid(const T &value, std::string &error) = 0;

private:
  std::string m_name;
};

class validator_date : public validator<std::string> {
public:
  validator_date();
  virtual bool is_valid(const std::string &value, std::string &error) override;
};

class validator_regexp : public validator<std::string> {
public:
  validator_regexp(const std::string &typeName, const std::string &sValidator);
  virtual bool is_valid(const std::string &value, std::string &error) override;

private:
  std::string m_sValidator;
  std::regex m_rxValidator;
};

class validator_str_list : public validator<std::string> {
public:
  validator_str_list(const std::string &name, const std::vector<std::string> &list_vals);
  virtual bool is_valid(const std::string &value, std::string &error) override;

private:
  std::vector<std::string> m_vListValues;
};

class validator_email : public validator_regexp {
public:
  validator_email();
};

class validator_uuid : public validator_regexp {
public:
  validator_uuid();
};

class validator_strlen : public validator<std::string> {
public:
  validator_strlen(int min_length, int max_length);
  virtual bool is_valid(const std::string &value, std::string &error) override;

private:
  int m_min_length;
  int m_max_length;
};

class validator_jwt : public validator_regexp {
public:
  validator_jwt();
};

class validator_time24 : public validator<std::string> {
public:
  validator_time24();
  virtual bool is_valid(const std::string &value, std::string &error) override;
};

class validator_datetime : public validator<std::string> {
public:
  validator_datetime();
  virtual bool is_valid(const std::string &value, std::string &error) override;
};

class validator_url : public validator<std::string> {
public:
  validator_url();
  virtual bool is_valid(const std::string &value, std::string &error) override;

private:
  std::regex m_rx_ip4_format;
};

class validator_domain_name : public validator<std::string> {
public:
  validator_domain_name();
  virtual bool is_valid(const std::string &value, std::string &error) override;
};

class validator_base64 : public validator<std::string> {
public:
  validator_base64();
  virtual bool is_valid(const std::string &value, std::string &error) override;
};

class validator_int : public validator<std::string> {
public:
  validator_int();
  virtual bool is_valid(const std::string &value, std::string &error) override;
};

class validator_hex : public validator<std::string> {
public:
  validator_hex();
  virtual bool is_valid(const std::string &value, std::string &error) override;
};

class validator_int_min : public validator<int> {
public:
  validator_int_min(int min_value);
  virtual bool is_valid(const int &value, std::string &error) override;

private:
  int m_min_value;
};

class validator_int_max : public validator<int> {
public:
  validator_int_max(int max_value);
  virtual bool is_valid(const int &value, std::string &error) override;

private:
  int m_max_value;
};

} // namespace wsjcpp