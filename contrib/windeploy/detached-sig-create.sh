#!/bin/sh
# Public Resource β 2021 π‘πππΌπππ π£πΎππΎππππΎππ
# Public Resource β 2020 π ππΎππ π£πΎππΎππππΎππ
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
