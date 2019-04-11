:: A quick way to compile the firmware for all of the devices
@ echo off
echo Compiling for Argon and Xenon
particle compile argon --saveTo argon.bin
particle compile xenon --saveTo xenon.bin
echo.
timeout 10
