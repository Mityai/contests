function processText {
  echo "------------- processText"
  while read line ; do 
    echo "$line"
    echo "$line"
  done
}

cat $0 | processText 
echo Hello | processText
