# wsjcpp-validators

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-validators.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-validators) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-validators.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-validators/stargazers) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-validators.svg)](https://github.com/wsjcpp/wsjcpp-validators/) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-validators.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-validators/network/members)

## Integrate to your project

Just include this files:

- src.wsjcpp/wsjcpp_core/wsjcpp_core.cpp
- src.wsjcpp/wsjcpp_core/wsjcpp_core.h
- src/wsjcpp_validators.h
- src/wsjcpp_validators.cpp

## Integrate via wsjcpp

```
$ wsjcpp install "https://github.com/wsjcpp/wsjcpp-core:v0.2.3"
$ wsjcpp install "https://github.com/wsjcpp/wsjcpp-validators:master"
```

## Example usage

``` cpp

validator_uuid *pValidatorUUID = new validator_uuid();
std::string sError = "";
if (!pValidatorUUID->is_valid("abcdef01-ABCD-EF23-1000-000000000001", sError)) {
    std::cout << sError << std::endl;
}
```

Classes for data validation

## Completed classes

- `new WsjcppValidatorStringRegexpBase("testre", "^[a-zA-Z]+$")` - validate value by regular expression
- `new WsjcppValidatorStringListBase("lang", {"en", "de", "ru"})` - validate value from a list
- `new WsjcppValidatorEmail()` - validate format email
- `new validator_uuid()` - validate format uuid
- `new validator_strlen(1,100)` - validate min length and max length
- `new validator_jwt()` - validate format of JWT
- `new WsjcppValidatorDate()` - validate format date like 'YYYY-MM-DD'
- `new validator_time24()` - validate format date like 'HH:mm:ss' (24 hours)
- `new WsjcppValidatorDateTime()` - validate format date like 'YYYY-MM-DD\THH:mm:ss'
- `new WsjcppValidatorURL()` - validate format of url
- `new validator_base64()` - validate format of base64
- `new WsjcppValidatorNumber()` - validate format of number
- `new WsjcppValidatorHex()` - validate hex value
- `new WsjcppValidatorIntegerMinValue(1)` - validate integer min value
- `new WsjcppValidatorIntegerMaxValue(100)` - validate integer max value

## Completed static functions

- `WsjcppValidators::is_validDate(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::is_validTimeH24(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::is_validDomainName(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::is_validBase64(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::is_validIPv4(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::is_validIPv6(const std::string &sValue, std::string &sError)`

## Example for your implementations

``` cpp
class validator_uuid : public WsjcppValidatorStringRegexpBase {
    public:
        validator_uuid() 
            : WsjcppValidatorStringRegexpBase(
                "uuid", // name
                "^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$"
            ) {
            TAG = "validator_uuid";
        }
};
```
