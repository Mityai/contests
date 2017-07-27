@echo off
if "%1" == "" (
	echo No parameters found
    exit       
)

for %%i in (..) do (
    set problem_name=%%~ni
)

if EXIST ..\check.cpp g++ ..\check.cpp -o ..\check.exe -O2
if EXIST ..\check.dpr dcc32 -cc ..\check.dpr
if EXIST ..\Check.java (
pushd ..
	mkdir __chktmp
	call javac -classpath testlib4j.jar -d __chktmp Check.java -encoding utf8 
	pushd __chktmp
	call jar cf Check.jar *.class
	xcopy /Y Check.jar ..
	popd
	rmdir /S /Q __chktmp
popd
)

if EXIST ..\%problem_name%_%1.dpr dcc32 -cc ..\%problem_name%_%1.dpr
if EXIST ..\%problem_name%_%1.cpp g++ -O2 ..\%problem_name%_%1.cpp -o ..\%problem_name%_%1.exe
if EXIST ..\%problem_name%_%1.java javac ..\%problem_name%_%1.java -encoding utf8 

:compiled


if "%2" == "" (
	echo %date% %time% > docheck_%problem_name%_%1.log	   
    for %%i in (??) do (        
        call onecheck %1 %%i
    )
) else (
    call onecheck %1 %2
)