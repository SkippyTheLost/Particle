:: A quick way to update the firmware across all of the devices
@ echo off
echo Compiling Project
particle compile argon --saveTo argon.bin
:: particle compile boron --saveTo argon.bin

timeout 5

echo.
echo Flashing gateway Project Device
echo.

:: Replace this with the Argon gateway
particle flash Argon_Deer argon.bin

:: Replace this with the Boron gateway
:: particle flash Boron boron.bin
