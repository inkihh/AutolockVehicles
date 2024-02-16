@echo off

set signpath=P:\mods\build\@MAGHeliUH1DMedic\Addons
::set keypath=C:\Users\Admin\Documents\Github\dayztools\keys\MiddleAgedGamers\MiddleAgedGamers
set keypath=C:\Users\Admin\Documents\Github\dayztools\keys\inkihh\inkihh

:: CREATE SIGNED FILES
echo -------------------------------------------------------
echo SIGNING

for /f %%f in ('dir /b %signpath%') do (call :signpbo %signpath%\%%f)

:: Copy key
echo -------------------------------------------------------
echo Copying pubkey to Keys/
copy "%keypath%.bikey" %signpath%

goto :eof

:signpbo
    echo signing %1
    start "" "C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\DsUtils\DSsignfile.exe" "%keypath%.biprivatekey" "%1"
    GOTO :eof
