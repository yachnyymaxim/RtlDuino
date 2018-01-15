#!/bin/bash

if [ ! -d "${1}" ]; then
 # goto no_dir
  JLinkGDBServer -device Cortex-M3 -if SWD -ir -endian little -speed 3500 &
  arm-none-eabi-gdb -x gdb_ota.jlink
  killall JLinkGDBServer
  exit 0
fi

if [ ! -f "${1}/ota.bin" ]; then
  echo "Error: Not found ${1}/ota.bin!"
  exit 1
fi

cp -f "$1/ota.bin" "$2/ota.bin"
cd "$2"
JLinkGDBServer -device Cortex-M3 -if SWD -ir -endian little -speed 3500 &
${3}arm-none-eabi-gdb -x gdb_ota.jlink
killall JLinkGDBServer


exit 0
