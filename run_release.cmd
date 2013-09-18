:: 
:: Author - Gary Ascuy, Sept 2013
:: Tested for Windows 7
:: 

:: Disable echo
@echo off

:: Variables
set WORKING_DIRECTORY=..\builds\sdl_dependency
set OUTPUT_DIRECTORY=%WORKING_DIRECTORY%\output
set APP_PATH=.\bin\Release\weh.exe
set GAME=start /D %WORKING_DIRECTORY% /B %APP_PATH%

:: Create output directory
if not exist %OUTPUT_DIRECTORY% (
	mkdir %OUTPUT_DIRECTORY%
)

:: Excecute program
if exist %APP_PATH% (
	%GAME% -l5 -o
) else (
	echo Application not found !! %APP_PATH%
)

pause > nul
