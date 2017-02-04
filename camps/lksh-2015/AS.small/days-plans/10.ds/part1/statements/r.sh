#!/usr/bin/bash

rm *.{toc,out,aux,log}

for f in `ls *.tex` ; do
  name=${f/.*}
  pdflatex $f --quiet
  pdflatex $f --quiet
  #dvipdfm $name.dvi
done

rm *.{toc,out,aux,log,dvi}
