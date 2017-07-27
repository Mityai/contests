@echo off

for %%i in (*.t) do (
  copy %%i %%~ni > nul
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

call tall aa
call docheck aa

