#!/usr/bin/bash

rm *.{toc,out,aux,log}

for f in `ls *.tex` ; do
  name=${f/.*}
  texify --pdf --engine=tex --quiet $f
done

rm *.{toc,out,aux,log,dvi}
