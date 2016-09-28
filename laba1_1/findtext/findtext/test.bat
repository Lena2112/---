set PROGRAM="%~1" 

%PROGRAM% empty.txt "see you" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "me" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt ""
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "hello" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "see you"
if ERRORLEVEL 1 goto err

%PROGRAM% non-existing.txt "find the line" 
if ERRORLEVEL 1 goto err

%PROGRAM% non-existing.txt 
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1