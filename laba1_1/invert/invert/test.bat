set PROGRAM="%~1" 

rem �������������� ������� �������
%PROGRAM% matrix.txt > output
fc output example
if ERRORLEVEL 1 goto err 

rem ������� � ������� �������������
%PROGRAM% matrix1.txt > output
fc output example1 
if ERRORLEVEL 1 goto err 

rem �������������� ����
%PROGRAM% deleted.txt > output
fc output example2
if ERRORLEVEL 1 goto err 

rem ���� � ������������� ����������� ���������
%PROGRAM% matrix2.txt > output
fc output example3
if ERRORLEVEL 1 goto err 

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1