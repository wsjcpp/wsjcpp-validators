#ifndef WJSCPP_VALIDATOR_H
#define WJSCPP_VALIDATOR_H

#include <string>
#include <vector>
#include <regex>

enum WJSCppValidatorType {
    WJSCPP_VALIDATOR_STRING,
    WJSCPP_VALIDATOR_NUMBER
};

/*
// ----------------------------------------------------------------------

class WJSCppValidatorBase {
    public:
        WJSCppValidatorBase(const std::string &sTypeName, WJSCppValidatorType nValidatorType);
        virtual WJSCppValidatorType getBaseType();
        virtual std::string getTypeName();
        virtual bool isValid(const std::string &sValue, std::string &sError) = 0;
    protected:
        std::string TAG;
    private:
        std::string m_sTypeName;
};

*/

// ----------------------------------------------------------------------

class WJSCppValidatorStringBase {
    public:
        WJSCppValidatorStringBase(const std::string &typeName);
        virtual WJSCppValidatorType getBaseType();
        virtual std::string getTypeName();
        virtual bool isValid(const std::string &sValue, std::string &sError) = 0;
    protected:
        std::string TAG;
    private:
        std::string m_sTypeName;
};

// ----------------------------------------------------------------------

class WJSCppValidatorStringRegexpBase : public WJSCppValidatorStringBase {
    public:
        WJSCppValidatorStringRegexpBase(const std::string &typeName, const std::string &sValidator);
        virtual bool isValid(const std::string &sValue, std::string &sError) override;
    private:
        std::string m_sValidator;
        std::regex m_rxValidator;
};

// ----------------------------------------------------------------------

class WJSCppValidatorStringListBase : public WJSCppValidatorStringBase {
    public:
        WJSCppValidatorStringListBase(const std::string &typeName, const std::vector<std::string> &vListValues);
        virtual bool isValid(const std::string &sValue, std::string &sError) override;
    private:
        std::vector<std::string> m_vListValues;
};

// ----------------------------------------------------------------------

class WJSCppValidatorEmail : public WJSCppValidatorStringRegexpBase {
    public:
        WJSCppValidatorEmail();
};

// ----------------------------------------------------------------------

class WJSCppValidatorUUID : public WJSCppValidatorStringRegexpBase {
    public:
        WJSCppValidatorUUID();
};

// ----------------------------------------------------------------------

class WJSCppValidatorStringLength : public WJSCppValidatorStringBase {
    public:
        WJSCppValidatorStringLength(int nMinLength, int nMaxLength);
        virtual bool isValid(const std::string &sValue, std::string &sError);

    private:
        std::string TAG;
        int m_nMinLength;
        int m_nMaxLength;
};

// ----------------------------------------------------------------------

#endif // WJSCPP_VALIDATOR_H