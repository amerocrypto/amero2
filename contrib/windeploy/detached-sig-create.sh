#!/bin/sh
# Public Resource ℗ 2021 𝖡𝗂𝗍𝖼𝗈𝗂𝗇 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# Public Resource ℗ 2020 𝖠𝗆𝖾𝗋𝗈 𝖣𝖾𝗏𝖾𝗅𝗈𝗉𝖾𝗋𝗌
# THIS REPOSITORY IS LICENSED UNDER THE AMERO PUBLIC RESOURCE LICENSE.

export LC_ALL=C
if [ -z "$OSSLSIGNCODE" ]; then
  OSSLSIGNCODE=osslsigncode
fi

if [ -z "$1" ]; then
  echo "usage: $0 <osslcodesign args>"
  echo "example: $0 -key codesign.key"
  exit 1
fi

OUT=signature-win.tar.gz
SRCDIR=unsigned
WORKDIR=./.tmp
OUTDIR="${WORKDIR}/out"
OUTSUBDIR="${OUTDIR}/win"
TIMESERVER=http://timestamp.comodoca.com
CERTFILE="win-codesign.cert"

mkdir -p "${OUTSUBDIR}"
basename -a `ls -1 "${SRCDIR}"/*-unsigned.exe` | while read UNSIGNED; do
  echo Signing "${UNSIGNED}"
  "${OSSLSIGNCODE}" sign -certs "${CERTFILE}" -t "${TIMESERVER}" -in "${SRCDIR}/${UNSIGNED}" -out "${WORKDIR}/${UNSIGNED}" "$@"
  "${OSSLSIGNCODE}" extract-signature -pem -in "${WORKDIR}/${UNSIGNED}" -out "${OUTSUBDIR}/${UNSIGNED}.pem" && rm "${WORKDIR}/${UNSIGNED}"
done

rm -f "${OUT}"
tar -C "${OUTDIR}" -czf "${OUT}" .
rm -rf "${WORKDIR}"
echo "Created ${OUT}"
