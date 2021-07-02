#!/usr/bin/env bash
#
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# Make sure we explicitly open all text files using UTF-8 (or ASCII) encoding to
# avoid potential issues on the BSDs where the locale is not always set.

export LC_ALL=C
EXIT_CODE=0
OUTPUT=$(git grep " open(" -- "*.py" | grep -vE "encoding=.(ascii|utf8|utf-8)." | grep -vE "open\([^,]*, ['\"][^'\"]*b[^'\"]*['\"]")
if [[ ${OUTPUT} != "" ]]; then
    echo "Python's open(...) seems to be used to open text files without explicitly"
    echo "specifying encoding=\"utf8\":"
    echo
    echo "${OUTPUT}"
    EXIT_CODE=1
fi
exit ${EXIT_CODE}
