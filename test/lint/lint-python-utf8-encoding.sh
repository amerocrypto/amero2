#!/usr/bin/env bash
#
# Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
# Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
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
