#!/usr/bin/env bash
#
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# Lint format strings: This program checks that the number of arguments passed
# to a variadic format string function matches the number of format specifiers
# in the format string.

export LC_ALL=C

FUNCTION_NAMES_AND_NUMBER_OF_LEADING_ARGUMENTS=(
    "FatalError,0"
    "fprintf,1"
    "LogConnectFailure,1"
    "LogPrint,1"
    "LogPrintf,0"
    "printf,0"
    "snprintf,2"
    "sprintf,1"
    "strprintf,0"
    "vfprintf,1"
    "vprintf,1"
    "vsnprintf,1"
    "vsprintf,1"
    "WalletLogPrintf,0"
)

EXIT_CODE=0
if ! python3 -m doctest test/lint/lint-format-strings.py; then
    EXIT_CODE=1
fi
for S in "${FUNCTION_NAMES_AND_NUMBER_OF_LEADING_ARGUMENTS[@]}"; do
    IFS="," read -r FUNCTION_NAME SKIP_ARGUMENTS <<< "${S}"
    for MATCHING_FILE in $(git grep --full-name -l "${FUNCTION_NAME}" -- "*.c" "*.cpp" "*.h" | sort | grep -vE "^src/(leveldb|secp256k1|tinyformat|univalue)"); do
        MATCHING_FILES+=("${MATCHING_FILE}")
    done
    if ! test/lint/lint-format-strings.py --skip-arguments "${SKIP_ARGUMENTS}" "${FUNCTION_NAME}" "${MATCHING_FILES[@]}"; then
        EXIT_CODE=1
    fi
done
exit ${EXIT_CODE}
