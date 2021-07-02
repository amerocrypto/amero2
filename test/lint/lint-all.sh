#!/usr/bin/env bash
#
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.
#
# This script runs all contrib/devtools/lint-*.sh files, and fails if any exit
# with a non-zero status code.

# This script is intentionally locale dependent by not setting "export LC_ALL=C"
# in order to allow for the executed lint scripts to opt in or opt out of locale
# dependence themselves.

set -u

SCRIPTDIR=$(dirname "${BASH_SOURCE[0]}")
LINTALL=$(basename "${BASH_SOURCE[0]}")

for f in "${SCRIPTDIR}"/lint-*.sh; do
  if [ "$(basename "$f")" != "$LINTALL" ]; then
    if ! "$f"; then
      echo "^---- failure generated from $f"
      exit 1
    fi
  fi
done
