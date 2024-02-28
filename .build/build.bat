 @echo off
setlocal

if not exist .\environment.bat (
	echo No environment.bat found! Forgot to copy environment.bat.orig to environment.bat?
	exit
)

call .\environment.bat

set version=%env_version%
set modbase=%env_modbase%
set modpath=%env_modpath%
set modname=%env_modname%
set serverip=%env_serverip%
set serverport=%env_serverport%
set password=%env_password%
set playername=%env_playername%
set modlist=%env_modlist%
set servermod=%env_servermod%
set srcpath=%modbase%%modpath%%modname%
set dayzclientpath=%env_dayzclientpath%
set dayzserverpath=%env_dayzserverpath%
set serverparams=%env_serverparams%
set buildpath=%env_buildpath%
set mission=%env_mission%
set keypath=%env_keypath%
set clientprofile=%env_clientprofile%
set serverprofile=%env_serverprofile%
set serverconfig=%env_serverconfig%
set pboprojectpath=%env_pboprojectpath%
set makepbopath=%env_makepbopath%
set signtoolpath=%env_signtoolpath%

set dowipe=0

for /f "tokens=*" %%i in ('node .\modpath.js "%modlist%"') do set fullmodlist=%%i

::goto :end

set fullmodlist=%fullmodlist%%env_modlistlocal%

::goto :nokill

:: STOP THE SERVER AND CLIENT
echo STOPPING THE SERVER AND CLIENT
echo .
TASKKILL /IM DayZ_x64.exe /F /T
TASKKILL /IM DayZServer_x64.exe /F /T
TASKKILL /IM DayZDiag_x64.exe /F /T
TIMEOUT 3

:nokill

if %dowipe%==1 (
	echo DO WIPE?
	pause
	rmdir /s /q "%dayzserverpath%\mpmissions\dayzOffline.chernarusplus\storage_1"
	rmdir /s /q "%dayzserverpath%\mpmissions\dayzOffline.chernarusplus\expansion"
)

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

::goto :eof

:juststart

:: START THE SERVER
echo -------------------------------------------------------
echo .
echo STARTING THE SERVER
echo .
cd /d "%dayzserverpath%"
start "DayZServer" ".\DayZServer_x64.exe" %serverparams% "-port=%serverport%" "-config=%serverconfig%" "-profiles=%serverprofile%"  "-mod=%fullmodlist%" "-servermod=%servermod%"
::goto :end

::goto :eof

TIMEOUT 20

:startclient
:: START THE CLIENT
echo -------------------------------------------------------
echo .
echo STARTING THE CLIENT
echo .
cd /d "%dayzclientpath%"
start "DayZClient" ".\DayZ_BE.exe" %clientparams% "-name=%playername%" "-password=%password%" "-profiles=%clientprofile%" "-connect=%serverip%" "-port=%serverport%" "-mod=%fullmodlist%"

:end
GOTO :EOF

:GetUnixTime
setlocal enableextensions
for /f %%x in ('wmic path win32_utctime get /format:list ^| findstr "="') do (
    set %%x)
set /a z=(14-100%Month%%%100)/12, y=10000%Year%%%10000-z
set /a ut=y*365+y/4-y/100+y/400+(153*(100%Month%%%100+12*z-3)+2)/5+Day-719469
set /a ut=ut*86400+100%Hour%%%100*3600+100%Minute%%%100*60+100%Second%%%100
endlocal & set "%1=%ut%" & goto :EOF



