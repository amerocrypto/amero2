#!/usr/bin/env bash
#
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# Make sure all shell scripts:
# a.) explicitly opt out of locale dependence using "export LC_ALL=C", or
# b.) explicitly opt in to locale dependence using the annotation below.

export LC_ALL=C

EXIT_CODE=0
for SHELL_SCRIPT in $(git ls-files -- "*.sh" | grep -vE "src/(secp256k1|univalue)/"); do
    if grep -q "# This script is intentionally locale dependent by not setting \"export LC_ALL=C\"" "${SHELL_SCRIPT}"; then
        continue
    fi
    FIRST_NON_COMMENT_LINE=$(grep -vE '^(#.*)?$' "${SHELL_SCRIPT}" | head -1)
    if [[ ${FIRST_NON_COMMENT_LINE} != "export LC_ALL=C" ]]; then
        echo "Missing \"export LC_ALL=C\" (to avoid locale dependence) as first non-comment non-empty line in ${SHELL_SCRIPT}"
        EXIT_CODE=1
    fi
done
exit ${EXIT_CODE}
