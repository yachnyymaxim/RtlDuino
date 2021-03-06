#!/bin/bash

if [ ! -d "${1}" ]; then
 # goto no_dir
  JLinkGDBServer -device Cortex-M3 -if SWD -ir -endian little -speed 3500 &
  arm-none-eabi-gdb -x gdb_img.jlink
  killall JLinkGDBServer
  exit 0
fi

if [ ! -f "${1}/ota.bin" ]; then
  # if not exist %1\ota.bin goto error_x
  echo "Error: Not found ${1}/ota.bin!"
  exit 1
fi

#if exist %2\ota.bin del %2\ota.bin
#copy /b %1\ota.bin %2\ota.bin
cp -f "$1/ota.bin" "$2/ota.bin"
cd "$2"
JLinkGDBServer -device Cortex-M3 -if SWD -ir -endian little -speed 3500 &
#%3arm-none-eabi-gdb.exe -x gdb_img.jlink
${3}arm-none-eabi-gdb -x gdb_img.jlink
killall JLinkGDBServer


exit 0
