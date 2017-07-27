@echo off
if "%1" == "" (
	echo No parameters found
    exit       
)

for %%i in (..) do (
    set problem_name=%%~ni
)

if "%2" == "" (
    echo No second parameter found
    exit
) else (
    echo Running on test: %2
    copy %2 %problem_name%.in > nul
    if EXIST ..\%problem_name%_%1.exe run -t 2 -m 256M ..\%problem_name%_%1.exe
    if EXIST ..\%problem_name%_%1.class run -1 -t 2 -m 256M java -Xss64M -Xmx256M -cp .. %problem_name%_%1
    if EXIST ..\%problem_name%_%1.py run -t 2 -m 256M python ..\%problem_name%_%1.py
    echo Checking on test: %2
    if EXIST ..\check.exe ..\check %problem_name%.in %problem_name%.out %2.a
    if EXIST ..\Check.jar java -Xmx256M -Xss64M -cp ..\testlib4j.jar;..\Check.jar ru.ifmo.testlib.CheckerFramework Check %problem_name%.in %problem_name%.out %2.a

    if errorlevel 1 (
     	echo %2 failed >> docheck_%problem_name%_%1.log	
   	) else (
   	    echo %2 ok >> docheck_%problem_name%_%1.log	
   	)
)