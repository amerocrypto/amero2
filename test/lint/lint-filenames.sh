#!/usr/bin/env bash
#
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# Make sure only lowercase alphanumerics (a-z0-9), underscores (_),
# hyphens (-) and dots (.) are used in source code filenames.

export LC_ALL=C

EXIT_CODE=0
OUTPUT=$(git ls-files --full-name -- "*.[cC][pP][pP]" "*.[hH]" "*.[pP][yY]" "*.[sS][hH]" | \
    grep -vE '^[a-z0-9_./-]+$' | \
    grep -vE '^src/(secp256k1|univalue)/')

if [[ ${OUTPUT} != "" ]]; then
    echo "Use only lowercase alphanumerics (a-z0-9), underscores (_), hyphens (-) and dots (.)"
    echo "in source code filenames:"
    echo
    echo "${OUTPUT}"
    EXIT_CODE=1
fi
exit ${EXIT_CODE}
