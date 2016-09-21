set PROGRAM="%~1" 

%PROGRAM% empty.txt "в вашей воле" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "вы" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt ""
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "привет" 
if ERRORLEVEL 1 goto err 

%PROGRAM% input.txt "в вашей воле"
if ERRORLEVEL 1 goto err

%PROGRAM% non-existing.txt "найди строку" 
IF ERRORLEVEL 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1