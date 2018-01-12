#!/bin/bash

if [ ! -d "${1}" ]; then
 # goto no_dir
echo r0>RunRAM.JLinkScript
echo r1>>RunRAM.JLinkScript
echo h>>RunRAM.JLinkScript
echo h>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo loadbin "run_ram.bin" 0x10000bc8>>RunRAM.JLinkScript
echo loadbin "ota.bin" 0x10005FF0>>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo w4 0x40000210,0x20011117>>RunRAM.JLinkScript
echo g>>RunRAM.JLinkScript
echo q>>RunRAM.JLinkScript
JLinkExe  -Device CORTEX-M3 -If SWD -Speed 3500 RunRAM.JLinkScript
 exit 0
fi

if [ ! -f "${1}/ota.bin" ]; then
 #goto error_1
 echo "Error: Not found ${1}/ota.bin!"
 exit 1
fi

if [ ! -f "${2}/run_ram.bin" ]; then
 #goto error_2
 echo "Error: Not found ${2}/run_ram.bin!"
 exit 1
fi


# -- ELSE --
#PATH=$1:$2:${PATH}
#echo "*** cd $2"
cd "$2"
#echo "*** cp $1/ota.bin ota.bin"
cp "$1/ota.bin" ota.bin
echo r0>RunRAM.JLinkScript
echo r1>>RunRAM.JLinkScript
echo h>>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo loadbin "run_ram.bin" 0x10000bc8>>RunRAM.JLinkScript
echo loadbin "ota.bin" 0x10005FF0>>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo w4 0x40000210,0x20111117>>RunRAM.JLinkScript
echo g>>RunRAM.JLinkScript
echo q>>RunRAM.JLinkScript
JLinkExe -Device CORTEX-M3 -If SWD -Speed 3500 RunRAM.JLinkScript

exit 0
