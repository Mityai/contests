@echo off
:x0
gen.exe > sqrtrev.in 
sqrtrev_nm_mb.exe 
copy sqrtrev.out out
"sqrtrev_msqrt(n)log(n)_mb.exe" 
fc sqrtrev.out out
goto x%errorlevel%