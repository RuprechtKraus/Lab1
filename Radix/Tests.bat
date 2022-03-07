@ECHO off

SET PROGRAM="%~1"

ECHO Test 1
%PROGRAM% > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Исходная система счисления меньше 2
ECHO Test 2
%PROGRAM% -5 10 20 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Исходная система счисления больше 36
ECHO Test 3
%PROGRAM% 38 10 20 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Целевая система счисления меньше 2
ECHO Test 4
%PROGRAM% 15 0 20 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Целевая система счисления больше 36
ECHO Test 5
%PROGRAM% 15 42 20 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Число приводящее к переполнению
ECHO Test 6
%PROGRAM% 25 10 L785MO4398J723985 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Пустое число
ECHO Test 7
%PROGRAM% 18 27 "  " > "%TEMP%\radix_test_result.txt"
IF NOT ERRORLEVEL 1 GOTO error

REM Некорректное число
ECHO Test 8
%PROGRAM% 18 27 50*60 > "%TEMP%\radix_test_result.txt"
IF NOT ERRORLEVEL 1 GOTO error

REM Некорректное число
ECHO Test 9
%PROGRAM% 18 27 "82K OL" > "%TEMP%\radix_test_result.txt"
IF NOT ERRORLEVEL 1 GOTO error

REM Некорректное число
ECHO Test 10
%PROGRAM% 18 27 ":)" > "%TEMP%\radix_test_result.txt"
IF NOT ERRORLEVEL 1 GOTO error

REM Корректные данные. Число положительное
ECHO Test 11
%PROGRAM% 32 12 75KOL > "%TEMP%\radix_test_result.txt"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\radix_test_result.txt" "Test files\PositiveNumber-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Корректные данные. Число отрицательное
ECHO Test 13
%PROGRAM% 18 27 -DEFG > "%TEMP%\radix_test_result.txt"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\radix_test_result.txt" "Test files\NegativeNumber-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Оба основания меньше 2
ECHO Test 15
%PROGRAM% 1 -2 1000 > "%TEMP%\radix_test_result.txt"
IF NOT ERRORLEVEL 1 GOTO error

REM Оба основания больше 36
ECHO Test 16
%PROGRAM% 45 39 1000 > "%TEMP%\radix_test_result.txt"
IF NOT ERRORLEVEL 1 GOTO error

ECHO All tests passed successfully
EXIT /B 0

:error
ECHO Testing failed
EXIT /B 1