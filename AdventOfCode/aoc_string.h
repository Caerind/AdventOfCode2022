#pragma once

#include "aoc.h"

void LTrim(std::string& s);
void RTrim(std::string& s);
void Trim(std::string& s);
std::string LTrimCopy(std::string s);
std::string RTrimCopy(std::string s);
std::string TrimCopy(std::string s);

void ToLower(std::string& string);
void ToUpper(std::string& string);
void ToLower(const std::string& string, std::string& result);
void ToUpper(const std::string& string, std::string& result);

bool IsNumber(const std::string& string);

bool Split(std::string& base, std::string& result, char separator);
bool Split(std::string& base, std::string& result, const std::string& separator);

bool Contains(const std::string& string, char c);
bool Contains(const std::string& string, const std::string& c);

bool LimitSize(std::string& string, std::size_t size);
bool LimitSize(const std::string& string, std::string& result, std::size_t size);

std::string ToBoolString(bool value);
bool FromBoolString(const std::string& string);

template <typename ... Args>
std::string StringFormat(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template <typename T>
std::string ToString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <>
inline std::string ToString<std::string>(const std::string& value)
{
    return value;
}

template <>
inline std::string ToString<bool>(const bool& value)
{
    return (value) ? "1" : "0";
}

template <>
inline std::string ToString<char>(const char& value)
{
    return std::string(1, value);
}

template <typename T>
T FromString(const std::string& string)
{
    T value;
    std::istringstream iss(string);
    iss >> value;
    return value;
}

template <>
inline std::string FromString<std::string>(const std::string& string)
{
    return string;
}

template <>
inline bool FromString<bool>(const std::string& string)
{
    return (string == "1" || string == "true");
}

template <>
inline char FromString<char>(const std::string& string)
{
    return (string.size() >= 1) ? string[0] : '\0';
}