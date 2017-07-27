@echo off

rem Стандартный чекер. Входные файлы - *.in, *.out.
rem Example1: check_sol.cmd sum_sk.exe
rem Example2: check_sol.cmd java sum_as

set prob=sqrtrev

if %1. == . (
  echo Usage: check_sol.cmd "your solution (executable file)"
  goto exit
)

echo Test solution %1

for %%i in (*.) do (
  echo Test %%i : 
  copy %%i %prob%.in >nul
  del %prob%.out >nul 2>nul
  call run.cmd %* || goto RE
  check.exe %prob%.in %prob%.out %%i.a || goto exit
)

goto exit

:RE
echo RE: Runtime Error

:exit
echo The End
