:: A quick way to update the firmware across all of the devices
@ echo off
echo Flashing all Project Devices
particle compile xenon --saveTo xenon.bin
echo.
:: Follow the following structure, add each Xenon
echo Flashing Xenons in background
start /min cmd.exe /c particle flash Xenon_Walrus xenon.bin
start /min cmd.exe /c particle flash Xenon_Dolphin xenon.bin
start /min cmd.exe /c particle flash Xenon_Pidgeon xenon.bin
start /min cmd.exe /c particle flash Xenon_Gerbil xenon.bin

particle compile argon --saveTo argon.bin
:: particle compile boron --saveTo argon.bin

:: Add delay to allow slave devices to flash or timeout
timeout 30 /nobreak

:: Replace this with the Argon gateway
particle flash Argon_Deer argon.bin

:: Replace this with the Boron gateway
:: particle flash Boron boron.bin
