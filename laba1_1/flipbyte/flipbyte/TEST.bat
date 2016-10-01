set PROGRAM="%~1" 

rem проверка числа, после изменения байтов которого ничего не изменится
%PROGRAM% 0 > output
fc output example1
if ERRORLEVEL 1 goto err 

rem проверка выхода за пределы
%PROGRAM% -1 
if ERRORLEVEL 1 goto err 

rem проверка колличества аргументов
%PROGRAM%
if NOT ERRORLEVEL 1 goto err 

rem проверка оптимального варианта, должно вернуть 96
%PROGRAM% 6 > output
fc output example
if ERRORLEVEL 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1