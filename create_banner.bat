REM === Define path to 3DSBannerMaker ===
SET banmak_dir=C:\devkitpro\3DSBannerMaker

REM === Copy input files to 3DSBannerMaker folders ===
cp app\banner.png %banmak_dir%\cbmd_bannerImage\256x128.png
cp app\icon24x24.png %banmak_dir%\ctpk_24x24icon\icon.png
cp app\icon48x48.png %banmak_dir%\ctpk_48x48icon\icon.png
cp app\BannerAudio.bcwav %banmak_dir%\bcwav_audio\example.bcwav
cp app\IcnSettings.txt %banmak_dir%\AppData.txt

REM === Create Banner and Icon ===
call %banmak_dir%\BUILD.bat

REM === Copy banner and icon into current project ===
cp %banmak_dir%\icon.icn %~dp0\app\icon.icn
cp %banmak_dir%\banner.bnr %~dp0\app\banner.bnr

REM === Remove input files in 3DSBannerMaker folders ===
rm -f %banmak_dir%\cbmd_bannerImage\256x128.png
rm -f %banmak_dir%\ctpk_24x24icon\icon.png
rm -f %banmak_dir%\ctpk_48x48icon\icon.png
rm -f %banmak_dir%\icon.icn	
rm -f %banmak_dir%\banner.bnr
rm -f %banmak_dir%\AppData.txt

REM === pause if there were errors ===
if %errorlevel% neq 0 pause