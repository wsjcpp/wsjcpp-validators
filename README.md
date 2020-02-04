# wsjcpp-validators

[![Build Status](https://api.travis-ci.org/wsjcpp/wsjcpp-validators.svg?branch=master)](https://travis-ci.org/wsjcpp/wsjcpp-validators) [![Github Stars](https://img.shields.io/github/stars/wsjcpp/wsjcpp-validators.svg?label=github%20%E2%98%85)](https://github.com/wsjcpp/wsjcpp-validators/stargazers) [![Github Stars](https://img.shields.io/github/contributors/wsjcpp/wsjcpp-validators.svg)](https://github.com/wsjcpp/wsjcpp-validators/) [![Github Forks](https://img.shields.io/github/forks/wsjcpp/wsjcpp-validators.svg?label=github%20forks)](https://github.com/wsjcpp/wsjcpp-validators/network/members)

Classes for data validation

## Completed classes

- `new WJSCppValidatorStringRegexpBase("testre", "^[a-zA-Z]+$")` - validate value by regular expression
- `new WJSCppValidatorStringListBase("lang", {"en", "de", "ru"})` - validate value from a list
- `new WJSCppValidatorEmail()` - validate format email
- `new WJSCppValidatorUUID()` - validate format uuid
- `new WJSCppValidatorStringLength(1,100)` - validate min length and max length

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

WJSCppValidatorUUID *pValidatorUUID = new WJSCppValidatorUUID();
std::string sError = "";
if (!pValidatorUUID->isValid("abcdef01-ABCD-EF23-1000-000000000001", sError)) {
    std::cout << sError << std::endl;
}
```

## Example for yuor implementations

``` cpp
class WJSCppValidatorUUID : public WJSCppValidatorStringRegexpBase {
    public:
        WJSCppValidatorUUID() 
            : WJSCppValidatorStringRegexpBase(
                "uuid", // name
                "^[0-9A-Fa-f]{8}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{4}-[0-9A-Fa-f]{12}$"
            ) {
            TAG = "WJSCppValidatorUUID";
        }
};
```