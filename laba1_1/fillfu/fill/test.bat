set PROGRAM="%~1" 

%PROGRAM% input.txt 
if NOT ERRORLEVEL 1 goto err

%PROGRAM% deleted.txt output.txt 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt output.txt
if ERRORLEVEL 1 goto err 

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1