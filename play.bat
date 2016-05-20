REM === Find the .3dsx file ===
FOR %%F IN (*.3dsx) DO (

  REM === Launch the emulator ===
  START ../../../emulators/citra/citra-qt.exe %%F

#  REM === Upload to 3DS with Netcat ===
#  cd netcat
#  cat ../%%F | nc 192.168.137.8 9000
)