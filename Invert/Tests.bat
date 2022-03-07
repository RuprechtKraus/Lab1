@ECHO off

SET PROGRAM="%~1"

REM Запуск без аргументов командной строки
ECHO Test 1
%PROGRAM% > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Запуск с несуществующим файлом
ECHO Test 2
%PROGRAM% "MissingMatrixFile.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Матрица содержит буквенные символы
ECHO Test 3
%PROGRAM% "Test files\MatrixWithLetters.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Матрица размера 2х2 - требуется 3х3
ECHO Test 4
%PROGRAM% "Test files\Matrix2x2.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Матрица размера 4х4 - требуется 3х3
ECHO Test 5
%PROGRAM% "Test files\Matrix4x4.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Матрица размера 3x3 - ожидается успех
ECHO Test 6
%PROGRAM% "Test files\Matrix3x3.txt" > "%TEMP%\invert_test_result.txt"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\invert_test_result.txt" "Test files\Matrix3x3-result.txt"
IF ERRORLEVEL 1 GOTO error

REM Матрица размера 3х3, но с нулевым определителем - ожидается успешное завершение программы с выводом сообщения
ECHO Test 7
%PROGRAM% "Test files\Matrix3x3DeterminantZero.txt" > "%TEMP%\invert_test_result.txt"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\invert_test_result.txt" "Test files\Matrix3x3DeterminantZero-result.txt"
IF ERRORLEVEL 1 GOTO error

ECHO All tests passed successfully
EXIT /B 0

:error
ECHO Testing failed
EXIT /B 1