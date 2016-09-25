set PROGRAM="%~1" 

%PROGRAM% 0
if ERRORLEVEL 1 goto err 

%PROGRAM% -1 
if ERRORLEVEL 1 goto err 

%PROGRAM% 300
if ERRORLEVEL 1 goto err 

%PROGRAM% 6
if ERRORLEVEL 1 goto err 

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1