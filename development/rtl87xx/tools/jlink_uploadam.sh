#!/bin/bash

if [ ! -d "${1}" ]; then
 #no_dir
 #rem PATH=D:\MCU\SEGGER\JLink_V612i;%PATH%;
echo r0>RunRAM.JLinkScript
echo r1>>RunRAM.JLinkScript
echo h>>RunRAM.JLinkScript
echo h>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo loadbin "run_ram.bin" 0x10000bc8>>RunRAM.JLinkScript
echo loadbin "ram_2.bin" 0x10006000>>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo w4 0x40000210,0x20011113>>RunRAM.JLinkScript
echo w4 0x1FFF0000,0x12345678>>RunRAM.JLinkScript
echo g>>RunRAM.JLinkScript
echo sleep 1000>>RunRAM.JLinkScript
echo h>>RunRAM.JLinkScript
echo loadbin "sdram.bin" 0x30000000>>RunRAM.JLinkScript
echo w4 0x1FFF0000,0x1>>RunRAM.JLinkScript
echo g>>RunRAM.JLinkScript>>RunRAM.JLinkScript
echo q>>RunRAM.JLinkScript>>RunRAM.JLinkScript
JLinkExe -Device CORTEX-M3 -If SWD -Speed 1500 RunRAM.JLinkScript
 exit 0
fi

if [ ! -f "${1}/ram_2.bin" ]; then
 #if not exist %1\ram_2.bin goto error_1
 echo "Error: Not found ${1}/ram_2.bin!"
 exit 1
fi

if [ ! -f "${1}/sdram.bin" ]; then
 #if not exist %1\sdram.bin goto error_1
 echo "Error: Not found ${1}/sdram.bin!"
 exit 1
fi

if [ ! -f "${2}/run_ram.bin" ]; then
 #goto error_2
 echo "Error: Not found ${2}/run_ram.bin!"
 exit 1
fi

# -- ELSE DEFAULT ---

#PATH=%1;%2;%PATH%
cd "$2"
#copy /b %1\ram_2.bin ram_2.bin
#copy /b %1\sdram.bin sdram.bin
cp "$1\ram_2.bin" ram_2.bin
cp "$1\sdram.bin" sdram.bin

echo r0>RunRAM.JLinkScript
echo r1>>RunRAM.JLinkScript
echo h>>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo loadbin "run_ram.bin" 0x10000bc8>>RunRAM.JLinkScript
echo loadbin "ram_2.bin" 0x10006000>>RunRAM.JLinkScript
echo r>>RunRAM.JLinkScript
echo w4 0x40000210,0x20011113>>RunRAM.JLinkScript
echo w4 0x1FFF0000,0x12345678>>RunRAM.JLinkScript
echo g>>RunRAM.JLinkScript
echo sleep 1000>>RunRAM.JLinkScript
echo h>>RunRAM.JLinkScript
echo loadbin "sdram.bin" 0x30000000>>RunRAM.JLinkScript
echo w4 0x1FFF0000,0x1>>RunRAM.JLinkScript
echo g>>RunRAM.JLinkScript>>RunRAM.JLinkScript
echo q>>RunRAM.JLinkScript>>RunRAM.JLinkScript
#rem PATH=D:\MCU\SEGGER\JLink_V612i;%PATH%;
#JLink.exe -Device CORTEX-M3 -If SWD -Speed 1500 RunRAM.JLinkScript
JLinkExe -Device CORTEX-M3 -If SWD -Speed 1500 RunRAM.JLinkScript

exit 0

