#!/usr/bin/env bash
#
# Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
# Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# Check include guards.

export LC_ALL=C
HEADER_ID_PREFIX="BITCOIN_"
HEADER_ID_SUFFIX="_H"

REGEXP_EXCLUDE_FILES_WITH_PREFIX="src/(crypto/ctaes/|leveldb/|secp256k1/|tinyformat.h|univalue/|ctpl.h|bls/|crypto/sph)"

EXIT_CODE=0
for HEADER_FILE in $(git ls-files -- "*.h" | grep -vE "^${REGEXP_EXCLUDE_FILES_WITH_PREFIX}")
do
    HEADER_ID_BASE=$(cut -f2- -d/ <<< "${HEADER_FILE}" | sed "s/\.h$//g" | tr / _ | tr "[:lower:]" "[:upper:]" | tr - _)
    HEADER_ID="${HEADER_ID_PREFIX}${HEADER_ID_BASE}${HEADER_ID_SUFFIX}"
    if [[ $(grep -cE "^#(ifndef|define) ${HEADER_ID}" "${HEADER_FILE}") != 2 ]]; then
        echo "${HEADER_FILE} seems to be missing the expected include guard:"
        echo "  #ifndef ${HEADER_ID}"
        echo "  #define ${HEADER_ID}"
        echo "  ..."
        echo "  #endif // ${HEADER_ID}"
        echo
        EXIT_CODE=1
    fi
done
exit ${EXIT_CODE}
