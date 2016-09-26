set PROGRAM="%~1" 

%PROGRAM% matrix.txt
if ERRORLEVEL 1 goto err 

%PROGRAM% matrix1.txt 
if NOT ERRORLEVEL 1 goto err 

%PROGRAM% deleted.txt
if ERRORLEVEL 1 goto err 

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1