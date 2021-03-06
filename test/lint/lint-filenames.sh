#!/usr/bin/env bash
#
# Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
# Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
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
