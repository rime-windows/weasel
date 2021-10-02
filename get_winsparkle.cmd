@Echo OFF
SetLocal EnableDelayedExpansion

rem website https://github.com/vslavik/winsparkle/releases

Set web_file=https://github.com/vslavik/winsparkle/releases/download/v0.7.0/WinSparkle-0.7.0.zip
rem set local_path=%CD%
set local_path=%~dp0
Set zip_file=w.zip
set check_file=./WinSparkle-0.7.0/include/winsparkle.h

if exist "%local_path%/%check_file%" (
    echo File %local_path%/%check_file% exists, exiting...
    goto END
)

powershell.exe -Command Invoke-WebRequest "%web_file%" -O "%local_path%/%zip_file%"
rem echo Exit Code errorlevel is %errorlevel%
if %errorlevel% NEQ 0 (
    echo Download %web_file% failed, exiting...
    echo If you are always failed to download it, please download it manually
    echo and extract it in folder "%local_path%"
    goto END
)

rem rundll32.exe zipfldr.dll,RouteTheCall "%local_path%/%zip_file%"
powershell.exe -Command Expand-Archive -LiteralPath "%local_path%/%zip_file%" -DestinationPath "%local_path%." -Force

del "%local_path%/%zip_file%"

echo Download %web_file% and extract it successfully.

:END
