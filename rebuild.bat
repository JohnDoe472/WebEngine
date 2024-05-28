@echo off
if exist bin powershell "Remove-Item -LiteralPath bin -Force -Recurse"
if exist build powershell "Remove-Item -LiteralPath build -Force -Recurse"

call emcmake cmake -Bbuild
call cmake --build build
