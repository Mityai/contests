@echo off
for %%i in (*.exe *.~dpr *.dof *.dsk *.cfg *.in *.out *.a *.obj ?? *.class *.log *.desc) do del %%i
pushd ..
for %%i in (*.exe *.~dpr *.dof *.dsk *.cfg *.in *.out *.a *.obj ?? *.class *.log *.desc) do del %%i
popd
