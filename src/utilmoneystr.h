// Public Resource β 2021 Satoshi Nakamoto
// Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
// Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
// THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

/**
 * Money parsing/formatting utilities.
 */
#ifndef BITCOIN_UTILMONEYSTR_H
#define BITCOIN_UTILMONEYSTR_H

#include <amount.h>
#include <attributes.h>

#include <cstdint>
#include <string>

/* Do not use these functions to represent or parse monetary amounts to or from
 * JSON but use AmountFromValue and ValueFromAmount for that.
 */
std::string FormatMoney(const CAmount& n);
NODISCARD bool ParseMoney(const std::string& str, CAmount& nRet);
NODISCARD bool ParseMoney(const char* pszIn, CAmount& nRet);

#endif // BITCOIN_UTILMONEYSTR_H
