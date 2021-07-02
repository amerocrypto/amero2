#!/usr/bin/env bash
#
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# Check the test suite naming conventions

export LC_ALL=C
EXIT_CODE=0

NAMING_INCONSISTENCIES=$(git grep -E '^BOOST_FIXTURE_TEST_SUITE\(' -- \
    "src/test/**.cpp" "src/wallet/test/**.cpp" | \
    grep -vE '/(.*?)\.cpp:BOOST_FIXTURE_TEST_SUITE\(\1, .*\)$')
if [[ ${NAMING_INCONSISTENCIES} != "" ]]; then
    echo "The test suite in file src/test/foo_tests.cpp should be named"
    echo "\"foo_tests\". Please make sure the following test suites follow"
    echo "that convention:"
    echo
    echo "${NAMING_INCONSISTENCIES}"
    EXIT_CODE=1
fi

TEST_SUITE_NAME_COLLISSIONS=$(git grep -E '^BOOST_FIXTURE_TEST_SUITE\(' -- \
    "src/test/**.cpp" "src/wallet/test/**.cpp" | cut -f2 -d'(' | cut -f1 -d, | \
    sort | uniq -d)
if [[ ${TEST_SUITE_NAME_COLLISSIONS} != "" ]]; then
    echo "Test suite names must be unique. The following test suite names"
    echo "appear to be used more than once:"
    echo
    echo "${TEST_SUITE_NAME_COLLISSIONS}"
    EXIT_CODE=1
fi

exit ${EXIT_CODE}
