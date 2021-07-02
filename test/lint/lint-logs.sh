#!/usr/bin/env bash
#
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# Check that all logs are terminated with '\n'
#
# Some logs are continued over multiple lines. They should be explicitly
# commented with /* Continued */
#
# There are some instances of LogPrintf() in comments. Those can be
# ignored

export LC_ALL=C

UNTERMINATED_LOGS=$(git grep --extended-regexp "LogPrintf?\(" -- "*.cpp" | \
    grep -v '\\n"' | \
    grep -v "/\* Continued \*/" | \
    grep -v "LogPrint()" | \
    grep -v "LogPrintf()")
if [[ ${UNTERMINATED_LOGS} != "" ]]; then
    echo "All calls to LogPrintf() and LogPrint() should be terminated with \\n"
    echo
    echo "${UNTERMINATED_LOGS}"
    exit 1
fi
