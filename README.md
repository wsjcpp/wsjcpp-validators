# wsjcpp-validators

[![Build Status](https://api.travis-ci.com/wsjcpp/wsjcpp-validators.svg?branch=master)](https://travis-ci.com/wsjcpp/wsjcpp-validators) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-validators.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-validators/stargazers) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-validators.svg)](https://github.com/wsjcpp/wsjcpp-validators/) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-validators.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-validators/network/members)

Classes for data validation

## Completed classes

- `new WsjcppValidatorStringRegexpBase("testre", "^[a-zA-Z]+$")` - validate value by regular expression
- `new WsjcppValidatorStringListBase("lang", {"en", "de", "ru"})` - validate value from a list
- `new WsjcppValidatorEmail()` - validate format email
- `new WsjcppValidatorUUID()` - validate format uuid
- `new WsjcppValidatorStringLength(1,100)` - validate min length and max length
- `new WsjcppValidatorJWT()` - validate format of JWT
- `new WsjcppValidatorDate()` - validate format date like 'YYYY-MM-DD'
- `new WsjcppValidatorTimeH24()` - validate format date like 'HH:mm:ss' (24 hours)
- `new WsjcppValidatorDateTime()` - validate format date like 'YYYY-MM-DD\THH:mm:ss'
- `new WsjcppValidatorURL()` - validate format of url
- `new WsjcppValidatorBase64()` - validate format of base64
- `new WsjcppValidatorNumber()` - validate format of number
- `new WsjcppValidatorHex()` - validate hex value

## Completed static functions

- `WsjcppValidators::isValidDate(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::isValidTimeH24(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::isValidDomainName(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::isValidBase64(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::isValidIPv4(const std::string &sValue, std::string &sError)`
- `WsjcppValidators::isValidIPv6(const std::string &sValue, std::string &sError)`

## Integrate to your project

Just include this files:

- src/wsjcpp_validators.h
- src/wsjcpp_validators.cpp

## Integrate via wsjcpp

```
$ wsjcpp install https://github.com/wsjcpp/wsjcpp-validators:master
```

## Example usage 

``` cpp

WsjcppValidatorUUID *pValidatorUUID = new WsjcppValidatorUUID();
std::string sError = "";
if (!pValidatorUUID->isValid("abcdef01-ABCD-EF23-1000-000000000001", sError)) {
    std::cout << sError << std::endl;
}
```

## Example for your implementations

``` cpp
class WsjcppValidatorUUID : public WsjcppValidatorStringRegexpBase {
    public:
        WsjcppValidatorUUID() 
            : WsjcppValidatorStringRegexpBase(
                "uuid", // name
                "^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$"
            ) {
            TAG = "WsjcppValidatorUUID";
        }
};
```
