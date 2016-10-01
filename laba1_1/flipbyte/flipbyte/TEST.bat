set PROGRAM="%~1" 

rem �������� �����, ����� ��������� ������ �������� ������ �� ���������
%PROGRAM% 0 > output
fc output example1
if ERRORLEVEL 1 goto err 

rem �������� ������ �� �������
%PROGRAM% -1 
if ERRORLEVEL 1 goto err 

rem �������� ����������� ����������
%PROGRAM%
if NOT ERRORLEVEL 1 goto err 

rem �������� ������������ ��������, ������ ������� 96
%PROGRAM% 6 > output
fc output example
if ERRORLEVEL 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1