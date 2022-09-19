@echo off
color 07
SETLOCAL EnableExtensions DisableDelayedExpansion
for /F %%a in ('echo prompt $E ^| cmd') do (
  set "ESC=%%a"
)
SETLOCAL EnableDelayedExpansion

for %%I in (.) do set CurrDirName=%%~nxI
echo !ESC![35m[== RUNNING "%CurrDirName%" IN QEMU ==]!ESC![0m
"%CD:~0,3%Quality Software\OperatingSystemDevTools\vms\qemu-system-x86_64.exe" -serial stdio -cdrom %CurrDirName%.iso -m 256 -M q35