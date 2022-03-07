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

REM Запуск с неверной операцией - требуется encrypt/decrypt
ECHO Test 3
%PROGRAM% "WrongAction" "Test files\FileToEncrypt.txt" "%TEMP%\crypt_test_result.txt" 20 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Запуск с нечисловым ключем - требуется число от 0 до 255
ECHO Test 4
%PROGRAM% "encrypt" "Test files\Test files\FileToEncrypt.txt" "%TEMP%\crypt_test_result.txt" "InvalidKey" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Запуск с пустым ключем
ECHO Test 5
%PROGRAM% "encrypt" "Test files\Test files\FileToEncrypt.txt" "%TEMP%\crypt_test_result.txt" "" > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Запуск с ключем меньше 0
ECHO Test 6
%PROGRAM% "encrypt" "Test files\FileToEncrypt.txt" "%TEMP%\crypt_test_result.txt" -1 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Запуск с ключем больше 255
ECHO Test 7
%PROGRAM% "encrypt" "Test files\FileToEncrypt.txt" "%TEMP%\crypt_test_result.txt" 300 > nul
IF NOT ERRORLEVEL 1 GOTO error

REM Шифрование файла
ECHO Test 8
%PROGRAM% "encrypt" "Test files\FileToEncrypt.txt" "%TEMP%\crypt_test_result.txt" 255 > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\crypt_test_result.txt" "Test files\FileToEncrypt-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

REM Дешифрование файла
ECHO Test 9
%PROGRAM% "decrypt" "Test files\FileToDecrypt.txt" "%TEMP%\crypt_test_result.txt" 30 > nul
IF ERRORLEVEL 1 GOTO error

FC "%TEMP%\crypt_test_result.txt" "Test files\FileToDecrypt-result.txt" > nul
IF ERRORLEVEL 1 GOTO error

ECHO All tests passed successfully
EXIT /B 0

:error
ECHO Testing failed
EXIT /B 1