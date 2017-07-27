@echo off

set prob=kthstat
set sol1=kthstat_sk
set sol2=kthstat_ra

echo Stress solutions %sol1% and %sol2%
set no=0

:a 
  set /a no=%no%+1
  echo Test #%no%
  %* > %prob%.in 2> log.log || exit

  echo %sol1%
  %sol1% || exit
  move %prob%.out %prob%.ans >nul 2>nul

  echo %sol2%
  %sol2% || exit

  echo check.exe
  check.exe %prob%.in %prob%.out %prob%.ans || exit
goto a
