@ECHO off
CLS
SETLOCAL

SET "c_file=%~dp0build_system\fbs.c"
SET "exe_file=%~dp0fbs.exe"

SET compile=cl -nologo "%c_file%" -Fe: "%exe_file%" -O2 -DFBS_ENABLE_CONSOLE_COLORS

IF NOT EXIST "%exe_file%" %compile% || EXIT /b %errorlevel%
"%exe_file%" %* || EXIT /b %errorlevel%
