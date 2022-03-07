@ECHO off

SET PROGRAM="%~1"

REM ������ ��� ���������� ��������� ������
ECHO Test 1
%PROGRAM% > nul
IF NOT ERRORLEVEL 1 GOTO error

REM ������ � �������������� ������
ECHO Test 2
%PROGRAM% "MissingMatrixFile.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM ������� �������� ��������� �������
ECHO Test 3
%PROGRAM% "Test files\MatrixWithLetters.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM ������� ������� 2�2 - ��������� 3�3
ECHO Test 4
%PROGRAM% "Test files\Matrix2x2.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM ������� ������� 4�4 - ��������� 3�3
ECHO Test 5
%PROGRAM% "Test files\Matrix4x4.txt" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM ������� ������� 3x3 - ��������� �����
ECHO Test 6
%PROGRAM% "Test files\Matrix3x3.txt" > "%TEMP%\invert_test_result.txt"
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\invert_test_result.txt" "Test files\Matrix3x3-result.txt"
IF ERRORLEVEL 1 GOTO error

REM ������� ������� 3�3, �� � ������� ������������� - ��������� �������� ���������� ��������� � ������� ���������
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