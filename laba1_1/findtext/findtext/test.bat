set PROGRAM="%~1" 

%PROGRAM% empty.txt "� ��襩 ����" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "��" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt ""
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "�ਢ��" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "� ��襩 ����"
if ERRORLEVEL 1 goto err

%PROGRAM% non-existing.txt "����� ��ப�" 
IF ERRORLEVEL 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1