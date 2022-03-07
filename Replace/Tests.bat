@ECHO off

SET PROGRAM="%~1"

REM При запуске без параметров ожидается ненулевой код возврата
ECHO Test 1
%PROGRAM% > nul
IF NOT ERRORLEVEL 1 GOTO error

REM При запуске с отсутствующим входным файлом ожидается ненулевой код возврата
ECHO Test 2
%PROGRAM% "Test files\MissingTestFile.txt" "%TEMP%\replace_test_result.txt" dog cat
IF NOT ERRORLEVEL 1 GOTO error

REM При запуске с правильными параметрами ожидается нулевой код возврата
ECHO Test 3
%PROGRAM% "Test files\CorrectFile.txt" "%TEMP%\replace_test_result.txt" "Top of the world" "Bottom of the sky"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\replace_test_result.txt" "Test files\CorrectFile-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Поиск строки в пустом файле
ECHO Test 4
%PROGRAM% "Test files\EmptyFile.txt" "%TEMP%\replace_test_result.txt" "FindString" "JustString"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\replace_test_result.txt" "Test files\EmptyFile-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Замена ma на mama
ECHO Test 5
%PROGRAM% "Test files\ExtendingPattern.txt" "%TEMP%\replace_test_result.txt" "ma" "mama"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\replace_test_result.txt" "Test files\ExtendingPattern-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Замена пустой строки
ECHO Test 6
%PROGRAM% "Test files\CorrectFile.txt" "%TEMP%\replace_test_result.txt" "" "Bottom of the sky" > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\replace_test_result.txt" "Test files\EmptySearchString-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

ECHO All tests passed successfully
EXIT /B 0

:error
ECHO Testing failed
EXIT /B 1