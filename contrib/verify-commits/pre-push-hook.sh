#!/usr/bin/env bash
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

export LC_ALL=C
if ! [[ "$2" =~ ^(git@)?(www.)?github.com(:|/)amerocrypto/amero(.git)?$ ]]; then
    exit 0
fi

while read LINE; do
    set -- A $LINE
    if [ "$4" != "refs/heads/master" ]; then
        continue
    fi
    if ! ./contrib/verify-commits/verify-commits.sh $3 > /dev/null 2>&1; then
        echo "ERROR: A commit is not signed, can't push"
        ./contrib/verify-commits/verify-commits.sh
        exit 1
    fi
done < /dev/stdin
