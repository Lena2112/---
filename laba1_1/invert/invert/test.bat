set PROGRAM="%~1" 

rem инвертирование обычной матрицы
%PROGRAM% matrix.txt > output
fc output example
if ERRORLEVEL 1 goto err 

rem матрица с нулевым определителем
%PROGRAM% matrix1.txt > output
fc output example1 
if ERRORLEVEL 1 goto err 

rem несуществующий файл
%PROGRAM% deleted.txt > output
fc output example2
if ERRORLEVEL 1 goto err 

rem файл с недостаточным количеством элементов
%PROGRAM% matrix2.txt > output
fc output example3
if ERRORLEVEL 1 goto err 

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1