@echo off
echo cleaning
call wipeall.cmd
echo compiling...

g++ ..\check.cpp -o check.exe -Wall -O2 -Wl,--stack=64000000||exit
g++ ..\heaps2_mb.cpp  -o heaps2_mb.exe -Wall -O2 -Wl,--stack=64000000||exit

g++ test.cpp -o test.exe -Wall -O0 -Wl,--stack=64000000||exit
g++ test_max.cpp -o test_max.exe -Wall -O0 -Wl,--stack=64000000||exit

echo generating test

copy ..\heaps2_mb.exe  .
for %%i in (*.hand) do (
  copy %%i %%~ni
)
7z -y x 10.hand.7z || exit
test 2 2 2
test 100 100 20
test 239 239 15
test 0 0 0
test 0 0 0
test 566 123 10
test 1000000 10000 1
test 1000000 10000 20
test 1000000 10000 20

test_max 1
test_max 2

mkdir ..\tests
for %%i in (??) do ( 
  copy %%i heaps2.in >nul
  heaps2_mb
  rename heaps2.out %%i.a >nul
  copy %%i ..\tests >nul
  copy %%i.a ..\tests >nul
  del %%i.,%%i.a
)
:exit
