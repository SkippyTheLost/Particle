:: A quick way to update the firmware across all of the devices
@ echo off
echo Flashing gateway Project Device
particle compile argon --saveTo argon.bin
:: particle compile boron --saveTo argon.bin

:: Replace this with the Argon gateway
particle flash Argon_Deer argon.bin

:: Replace this with the Boron gateway
:: particle flash Boron boron.bin
