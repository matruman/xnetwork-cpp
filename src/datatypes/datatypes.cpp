#include "datatypes.hpp"
#include <iostream>

// Bool impl

Bool::Bool() : isNullFlag{true} {}
Bool::Bool(bool i) : val{i}, isNullFlag{false} {}
Bool::Bool(const Bool &i) : val{i.val}, isNullFlag{i.isNullFlag} {}
Bool::Bool(Bool &&i) : val{i.val}, isNullFlag{i.isNullFlag} {}

bool Bool::get() const {return val; }
Bool::operator bool() const { return val; }
bool Bool::isNull() const { return isNullFlag; }
bool Bool::operator==(bool b) const { return val == b; }
bool Bool::operator!=(bool b) const { return !(val == b); }

// Integer impl

Integer::Integer() : isNullFlag{true} {}
Integer::Integer(int i) : val{i}, isNullFlag{false} {}
Integer::Integer(const Integer &i) : val{i.val}, isNullFlag{i.isNullFlag} {}
Integer::Integer(Integer &&i) : val{i.val}, isNullFlag{i.isNullFlag} {}

int Integer::get() const {return val; }
Integer& Integer::operator=(const Integer &other)
{
    val = other.val;
    isNullFlag = other.isNullFlag;
    return *this;
}
Integer::operator int() const { return val; }


bool Integer::isNull() const { return isNullFlag; }
bool Integer::operator==(const Integer &other) const { return val == other.val; }
bool Integer::operator!=(const Integer &other) const { return !(*this == other); }
bool Integer::operator<(const Integer &other) const { return val < other.val; }
bool Integer::operator>(const Integer &other) const { return other < *this; }
bool Integer::operator<=(const Integer &other) const { return !(other < *this); }
bool Integer::operator>=(const Integer &other) const { return !(*this < other); }

// Long impl

Long::Long() : isNullFlag{true} {}
Long::Long(long long i) : val{i}, isNullFlag{false} {}
Long::Long(const Long &i) : val{i.val}, isNullFlag{i.isNullFlag} {}
Long::Long(Long &&i) : val{i.val}, isNullFlag{i.isNullFlag} {}

long long Long::get() const {return val; }
Long::operator int64_t() const { return val; }
bool Long::isNull() const { return isNullFlag; }
bool Long::operator==(const Long &other) const { return val == other.val; }
bool Long::operator!=(const Long &other) const { return !(*this == other); }
bool Long::operator<(const Long &other) const { return val < other.val; }
bool Long::operator>(const Long &other) const { return other < *this; }
bool Long::operator<=(const Long &other) const { return !(other < *this); }
bool Long::operator>=(const Long &other) const { return !(*this < other); }

// String impl

String::String() : isNullFlag(true) {}
String::String(const std::string &s) : str (s), isNullFlag{false} {}
String::String(std::string &&s) : str(std::move(s)), isNullFlag{false} {}
String::String(std::wstring &&ws) : str(ws.begin(), ws.end()), isNullFlag{false} {}
String::String(const String& s) : str(s.str), isNullFlag{s.isNullFlag} {}
String::String(String&& s) : str(std::move(s.str)), isNullFlag{s.isNullFlag} {}

const std::string& String::get() const { return str; }

// Additional functions

std::string         saStrToStr(SAString &&str)
{
    std::wstring ws(str.GetWideChars());
    return std::string(ws.begin(), ws.end());
}

long long           saDateTimeToLong(SADateTime &&date)
{
    struct timeval tv;
    date.GetTimeValue(tv);
    return tv.tv_sec;
}

Bool getBoolFromSaField(SAField &field)
{
    return field.isNull() ? Bool() : Bool(field.asBool());
}

Integer getIntegerFromSaField(SAField &field)
{
    return field.isNull() ? Integer() : Integer(field.asLong());
}

Long getLongFromSaField(SAField &field)
{
    return field.isNull() ? Long() : Long(field.asInt64());
}

Long getDateFromSaField(SAField &field)
{
    if (field.isNull())
        return Long();
    else
        return Long(saDateTimeToLong(field.asDateTime()));
}

String getStringFromSaField(SAField &field)
{
    return field.isNull() ? String() : String(saStrToStr(field.asString()));
}
