 @echo off
setlocal

set version=0.0.1
set modbase=P:\inkihh\
set modpath=
set modname=AutolockVehicles
set serverip=192.168.178.96
set serverport=2302
set password=inkihh
set playername=inkihh
::set modlist=@DayZ-Expansion-Bundle;@DayZ-Expansion-Core;@DayZ-Expansion-Licensed;@VPPAdminTools;@Dabs Framework;@CF
::set modlist=@MuchCarKey;@VPPAdminTools;@Dabs Framework;@CF
::set modlist=@Trader;@VPPAdminTools;@Dabs Framework;@CF
set modlist=@TraderPlus;@VPPAdminTools;@Dabs Framework;@CF
set srcpath=%modbase%%modpath%%modname%
set dayzclientpath=C:\Program Files (x86)\Steam\steamapps\common\DayZ
set dayzserverpath=C:\Program Files (x86)\Steam\steamapps\common\DayZServer
set buildpath=P:\mods\local
set mission=dayzOffline.chernarusplus
set keypath=C:\Users\ingma\OneDrive\Documents\Github\dayztools\keys\inkihh\inkihh
set clientprofile=P:\mods\profiles\_dev\%mission%\client
set serverprofile=P:\mods\profiles\_dev\%mission%\server
set serverconfig=P:\mods\config\%mission%.dev.cfg
set pboprojectpath=C:\Program Files (x86)\Mikero\DePboTools\bin\PboProject.exe
set makepbopath=C:\Program Files (x86)\Mikero\DePboTools\bin\MakePbo.exe
set signtoolpath=C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\DsUtils\DSsignfile.exe

for /f "tokens=*" %%i in ('node .\modpath.js "%modlist%"') do set fullmodlist=%%i

::goto :end

set fullmodlist=%fullmodlist%;P:\mods\local\@LBmaster;P:\mods\local\@AutolockVehicles

::goto :nokill

:: STOP THE SERVER AND CLIENT
echo STOPPING THE SERVER AND CLIENT
echo .
TASKKILL /IM DayZ_x64.exe /F /T
TASKKILL /IM DayZServer_x64.exe /F /T
TASKKILL /IM DayZDiag_x64.exe /F /T
TIMEOUT 3

:nokill

goto :nowipe
rmdir /s /q "%dayzserverpath%\mpmissions\dayzOffline.chernarusplus\storage_1"
rmdir /s /q "%dayzserverpath%\mpmissions\dayzOffline.chernarusplus\expansion"
:nowipe

call :GetUnixTime unixtime

:: move server logs to logs folder
echo -------------------------------------------------------
echo .
echo MOVING LOGS TO %dayzserverpath%\logs\%unixtime%
echo .
mkdir "%dayzserverpath%\logs\%unixtime%"
move /Y "%serverprofile%\*.log" "%dayzserverpath%\logs\%unixtime%\"
move /Y "%serverprofile%\*.rpt" "%dayzserverpath%\logs\%unixtime%\"
move /Y "%serverprofile%\*.mdmp" "%dayzserverpath%\logs\%unixtime%\
move /Y "%serverprofile%\*.adm" "%dayzserverpath%\logs\%unixtime%\

:: delete client logs
echo -------------------------------------------------------
echo .
echo DELETING CLIENT LOGS
echo .
del /f /s %clientprofile%\*.log
del /f /s %clientprofile%\*.rpt
del /f /s %clientprofile%\*.mdmp
del /f /s %clientprofile%\*.adm

::goto :juststart

:: delete old build
echo -------------------------------------------------------
echo .
echo Deleting old build
echo .
rmdir /s /q "%buildpath%\%modpath%\@%modname%"

echo -------------------------------------------------------
echo .
echo Creating build folders
echo .
:: create build folders
mkdir "%buildpath%\%modpath%@%modname%"
mkdir "%buildpath%\%modpath%@%modname%\Addons"
mkdir "%buildpath%\%modpath%@%modname%\Info"
mkdir "%buildpath%\%modpath%@%modname%\Keys"

:: Copy key
echo -------------------------------------------------------
echo .
echo Copying pubkey to Keys/
echo .
copy "%keypath%.bikey" "%buildpath%\%modpath%@%modname%\Keys\"

:: PACK THE PBO
echo -------------------------------------------------------
echo .
echo PACKING
echo .
cls

start /B "MakePbo" "%makepbopath%" "%srcpath%" "%buildpath%\%modpath%@%modname%\Addons\%modname%.pbo"
::start /B "MakePbo" "%makepbopath%" "-X=*-U*.git,*.vscode,*.delete" "%srcpath%" "P:\mods\local\@FINKSmartphone\Addons\%modname%_%version%.pbo"
::start /B "PboProject" "%pboprojectpath%" "-S" "+$" "+J" "-W" "+N" "-C" "-K" "%srcpath%" "-M=P:\mods\local\@FINKSmartphone"
::start /B "MakePbo" "%makepbopath%" "-W" "-X=*-U*.git,*.vscode,*.delete" "%srcpath%" "P:\mods\local\@FINKSmartphone\Addons\%modname%_%version%.pbo"
cls

:: -O -Z=default
TIMEOUT 5
::goto :eof

:: KILL MAKEPBO
TASKKILL /IM MakePbo.exe /F /T
TASKKILL /IM PboProject.exe /F /T

:: @CHANGEME
:: only needed if packing is done via PboProject
:: rename "P:\mods\local\@FINKSmartphone\Addons\%modname%.pbo" "%modname%_%version%.pbo"

::goto :eof

::goto :skipsign
:: CREATE SIGNED FILE
echo -------------------------------------------------------
echo .
echo SIGNING
:: @CHANGEME
start /B  "" "%signtoolpath%" "%keypath%.biprivatekey" "%buildpath%\%modpath%@%modname%\Addons\%modname%.pbo"
TIMEOUT 1
:skipsign

goto :eof

:juststart

:: START THE SERVER
echo -------------------------------------------------------
echo .
echo STARTING THE SERVER
echo .
cd /d "%dayzserverpath%"
start "DayZServer" ".\DayZServer_x64.exe" /high "-port=%serverport%" "-dologs" "-netLog" "-adminlog" "-config=%serverconfig%" "-profiles=%serverprofile%"  "-scriptDebug=true" "-scrAllowFileWrite" "-equalmodrequired" "-mod=%fullmodlist%" "-servermod=P:\mods\serverside"
::goto :end
::%buildpath%\@%modpath%%modname%
::"-servermod=P:\mods\serverside"
::"-servermod=%buildpath%\@%modpath%%modname%"
::"-mod=%fullmodlist%" 

goto :afterdzsalauncher

echo -------------------------------------------------------
echo .
echo STARTING DZSALModServer
echo .
cd /d "%dayzserverpath%"
start "DZSALModServer" ".\DZSALModServer.exe" "-port=%serverport%" "-mod=%fullmodlist%" "-skipserver" "-password=%password%"

:afterdzsalauncher
::goto :eof

TIMEOUT 20

:startclient
:: START THE CLIENT
echo -------------------------------------------------------
echo .
echo STARTING THE CLIENT
echo .
cd /d "%dayzclientpath%"
start "DayZClient" ".\DayZ_BE.exe" "-dologs" "-nosplash" "-nopause" "-name=%playername%" "-nobenchmark" "-skipIntro" "-password=%password%" "-profiles=%clientprofile%" "-connect=%serverip%" "-port=%serverport%" "-mod=%fullmodlist%"
::"-name=inkihh"

:end
:: @CHANGEME so that cmd goes back
cd /d C:\Users\ingma\OneDrive\Documents\Github\dayztools\build

GOTO :EOF

:GetUnixTime
setlocal enableextensions
for /f %%x in ('wmic path win32_utctime get /format:list ^| findstr "="') do (
    set %%x)
set /a z=(14-100%Month%%%100)/12, y=10000%Year%%%10000-z
set /a ut=y*365+y/4-y/100+y/400+(153*(100%Month%%%100+12*z-3)+2)/5+Day-719469
set /a ut=ut*86400+100%Hour%%%100*3600+100%Minute%%%100*60+100%Second%%%100
endlocal & set "%1=%ut%" & goto :EOF



