particle compile xenon --saveTo xenon.bin

start /min cmd.exe /c particle flash Xenon_Walrus xenon.bin
start /min cmd.exe /c particle flash Xenon_Dolphin xenon.bin
start /min cmd.exe /c particle flash Xenon_Pidgeon xenon.bin
start /min cmd.exe /c particle flash Xenon_Gerbil xenon.bin

particle compile argon --saveTo argon.bin

timeout 30 /nobreak

particle flash Argon_Deer argon.bin