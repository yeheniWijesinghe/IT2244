@echo off 
:: hides the command execution

:: displays the title 'Age calculator'
echo Age calculator 

::/p - obtain user inputs
set /p birth_year=Enter your birth year :

:: display current date
echo %date%

:: extracts only the year
set current_year=%date:~10,4%

::/a - for variables with numeric values
:: get the difference between current year and the birth year
set /a age=%current_year%-%birth_year%

:: display the Age
echo You are %age% years old!

:: display only the date
set /a date=%date:~7,2%
echo Date : %date%

:: diplay only the month
set month=%date:~4,2%
echo Month: %month%

:: display only the year
echo Year : %current_year%

pause 


