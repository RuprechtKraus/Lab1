@ECHO off

SET PROGRAM="%~1"

REM Запуск без аргументов командной строки
ECHO Test 1
%PROGRAM% > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Запуск с несуществующим исходным файлом
ECHO Test 2
%PROGRAM% "MissingMatrixFile.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Исходный файл пустой - выходной файл ожидается пустым
ECHO Test 3
%PROGRAM% "Test files\EmptyCanvas.txt" "%TEMP%\fill_test_result.txt" > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\fill_test_result.txt" "Test files\EmptyCanvas-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Исходный файл имеет 3 стартовые точки внутри фигур
ECHO Test 4
%PROGRAM% "Test files\ThreePointsInsideShapes.txt" "%TEMP%\fill_test_result.txt" > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\fill_test_result.txt" "Test files\ThreePointsInsideShapes-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Исходный файл имеет 3 стартовые точки внутри фигур
ECHO Test 5
%PROGRAM% "Test files\OneShapeHasBreach.txt" "%TEMP%\fill_test_result.txt" > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\fill_test_result.txt" "Test files\OneShapeHasBreach-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Исходный файл имеет 1 стартовую точку вне фигур
ECHO Test 6
%PROGRAM% "Test files\OnePointOutsideOfShape.txt" "%TEMP%\fill_test_result.txt" > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\fill_test_result.txt" "Test files\OnePointOutsideOfShape-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Исходный файл имеет 2 фигуры пересекающие границы 100x100
ECHO Test 7
%PROGRAM% "Test files\TwoShapesCrosseBorder.txt" "%TEMP%\fill_test_result.txt" > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\fill_test_result.txt" "Test files\TwoShapesCrosseBorder-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

ECHO All tests passed successfully
EXIT /B 0

:error
ECHO Testing failed
EXIT /B 1