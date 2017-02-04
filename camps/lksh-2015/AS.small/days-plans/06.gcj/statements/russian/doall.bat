pushd ..\..\problems\qualification\statements\russian
for %%i in (*.mp) do (
	mpost %%i || goto error
)
del /F /Q *.log
popd

pushd ..\..\problems\chessboards\statements\russian
for %%i in (*.mp) do (
	mpost %%i || goto error
)
del /F /Q *.log
popd

pushd ..\..\problems\fence\statements\russian
for %%i in (*.mp) do (
	mpost %%i || goto error
)
del /F /Q *.log
popd

pushd ..\..\problems\football\statements\russian
for %%i in (*.mp) do (
	mpost %%i || goto error
)
del /F /Q *.log
popd

pushd ..\..\problems\gl\statements\russian
for %%i in (*.mp) do (
	mpost %%i || goto error
)
del /F /Q *.log
popd

latex statements.tex
latex statements.tex || goto error
dvips statements.dvi || goto error
dvipdfmx -p a4 statements.dvi || goto error

del /F /Q *.log
del /F /Q *.aux
del /F /Q *.dvi
del /F /Q *.ps

goto ok

:error
echo [ERROR]: Can't compile/build statements.
exit 1

:ok
echo [INFO]: Statements have been compiled/build.
