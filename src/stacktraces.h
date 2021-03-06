// Public Resource β 2021 ΔπΊππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

#ifndef BITCOIN_STACKTRACES_H
#define BITCOIN_STACKTRACES_H

#include <string>
#include <sstream>
#include <exception>

#include <cxxabi.h>

#include <tinyformat.h>

std::string DemangleSymbol(const std::string& name);

std::string GetPrettyExceptionStr(const std::exception_ptr& e);
std::string GetCrashInfoStrFromSerializedStr(const std::string& ciStr);

template<typename T>
std::string GetExceptionWhat(const T& e);

template<>
inline std::string GetExceptionWhat(const std::exception& e)
{
    return e.what();
}

// Default implementation
template<typename T>
inline std::string GetExceptionWhat(const T& e)
{
    std::ostringstream s;
    s << e;
    return s.str();
}

void RegisterPrettyTerminateHander();
void RegisterPrettySignalHandlers();

#endif//BITCOIN_STACKTRACES_H
