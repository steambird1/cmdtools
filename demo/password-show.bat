@echo off
echo Input password:
cmdt -w testpassword
if errorlevel 1 goto inc
echo Welcome!
goto fin
:inc
echo Incorrect password!
:fin
pause
exit