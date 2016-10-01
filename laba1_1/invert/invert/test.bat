set PROGRAM="%~1" 

rem �������������� ������� �������
%PROGRAM% matrix.txt > output
fc output example
if ERRORLEVEL 1 goto err 

rem ������� � ������� �������������
%PROGRAM% matrix1.txt 
if NOT ERRORLEVEL 1 goto err 

rem �������������� ����
%PROGRAM% deleted.txt
if ERRORLEVEL 1 goto err 

rem ���� � ������������� ����������� ���������
%PROGRAM% matrix2.txt
if ERRORLEVEL 1 goto err 

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1