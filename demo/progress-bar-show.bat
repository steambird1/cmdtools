@echo off
cmdt -p 00 %%
set p=20
:a
timeout /t 2 >nul
cmdt -e progress %p% %%
if "%p%"=="100" goto fin
set /a p=%p% + 20
goto a
:fin
echo.
pause