@echo off
cd ..
del  *.exe,*.in,*.,*.a,*.out /S >nul
cd src
rd ..\tests
