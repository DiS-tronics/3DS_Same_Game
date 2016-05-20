REM === delete build files ===
make clean

REM === delete icon and banner files ===
rm -f app/icon.icn
rm -f app/banner.bnr

REM === pause if there were errors ===
if %errorlevel% neq 0 pause
