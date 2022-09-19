@echo off
color 07

SETLOCAL EnableExtensions DisableDelayedExpansion
for /F %%a in ('echo prompt $E ^| cmd') do (
  set "ESC=%%a"
)
SETLOCAL EnableDelayedExpansion

cls

  echo batchfile=%0
  echo full=%~f0
setlocal
  for %%d in (%~dp0.) do set Directory=%%~fd
  echo Directory=%Directory%
  for %%d in (%~dp0..) do set ParentDirectory=%%~fd
  echo ParentDirectory=%ParentDirectory%
for %%I in (.) do set CurrDirName=%%~nxI
endlocal

timeout 1
cls

echo !ESC![35m[== SETTING UP WSL / BUILD ENV ==]!ESC![0m
echo Checkig if Windows Subsystem for Linux is enabled...
where wsl > NUL
if %ERRORLEVEL% NEQ 0 (color 04 && echo WSL isn't installed! && pause && exit)
echo WSL is enabled.

echo Starting Windows Subsystem for Linux...

set T=
SETLOCAL EnableDelayedExpansion
for /f "Tokens=* Delims=" %%x in (wsl_mntdrv.bat) do set T=!T!%%x
echo.
echo !ESC![35m[== INSTALLING REQUIRED PACKAGES AND MOUNTING CURRENT DRIVE ==]!ESC![0m
bash -c "sudo apt-get -y install git build-essential nasm xorriso; sudo mkdir -p /mnt/%CD:~0,1%; sudo mount -t drvfs %CD:~0,2% /mnt/%CD:~0,1%"
echo.
echo !ESC![35m[== COMPILING OS IN DIR: "%cd%" ==]!ESC![0m
wsl make

if %ERRORLEVEL% NEQ 0 (color 04 && pause && exit)

call run_qemu.bat

color 07
echo !ESC![35m[== TASK COMPLETED ==]!ESC![0m