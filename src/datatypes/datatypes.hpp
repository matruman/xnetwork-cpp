#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <stdint.h>
#include <string>
#include <SQLAPI.h>

class   Bool
{
    private:
    bool val;
    bool isNullFlag;

    public:
    Bool();
    Bool(bool i);
    Bool(Bool &&i);
    Bool(const Bool &i);
    ~Bool() = default;

    bool get() const;
    operator bool() const;
    bool isNull() const;
    bool operator==(bool b) const;
    bool operator!=(bool b) const;
};

class   Integer
{
    private:
    int val;
    bool isNullFlag;

    public:
    Integer();
    Integer(int i);
    Integer(Integer &&i);
    Integer(const Integer &i);
    ~Integer() = default;

    int get() const;
    operator int() const;
    bool isNull() const;
    bool operator==(const Integer &other) const;
    bool operator!=(const Integer &other) const;
    bool operator<(const Integer &other) const;
    bool operator>(const Integer &other) const;
    bool operator<=(const Integer &other) const;
    bool operator>=(const Integer &other) const;
};

class   Long
{
    private:
    long long val;
    bool isNullFlag;

    public:
    Long();
    Long(long long i);
    Long(Long &&i);
    Long(const Long &i);
    ~Long() = default;
    
    long long get() const;
    operator int64_t() const;
    bool isNull() const;
    bool operator==(const Long &other) const;
    bool operator!=(const Long &other) const;
    bool operator<(const Long &other) const;
    bool operator>(const Long &other) const;
    bool operator<=(const Long &other) const;
    bool operator>=(const Long &other) const;
};

class String
{
private:
    std::string str;
    bool isNullFlag;

public:
    String();
    String(const std::string &s);
    String(std::string &&s);
    String(std::wstring &&ws);
    String(const String& s);
    String(String&& s);
    ~String() = default;

    bool isNull();
    const std::string& get() const;

};

// Convert SAString to std::string
std::string         saStrToStr(SAString &&str);
// Convert SADateTime to long long
long long           saDateTimeToLong(SADateTime &&date);

// Get values from SAField
Integer getIntegerFromSaField(SAField &field);
Long getLongFromSaField(SAField &field);
Long getDateFromSaField(SAField &field);
String getStringFromSaField(SAField &field);

#endif