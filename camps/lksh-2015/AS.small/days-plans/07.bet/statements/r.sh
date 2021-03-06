#!/usr/bin/bash

rm *.{toc,out,aux,log}

python gen.py > autogenerated.sh || exit
bash autogenerated.sh || exit

for f in `ls *.tex` ; do
  echo compile $f
  name=${f/.*}
  pdflatex $f --quiet
  pdflatex $f --quiet
  #dvipdfm $name.dvi
done

rm *.{toc,out,aux,log,dvi}
