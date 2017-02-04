cd ../../problems/qualification/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/chessboards/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/fence/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/football/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/gl/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

latex statements.tex
latex statements.tex
dvips statements.dvi
dvipdfmx -p a4 statements.dvi
rm -f *.log
rm -f *.aux
rm -f *.dvi
rm -f *.ps
