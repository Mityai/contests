{Checker: standard}
{Checker details: compare one 64-bit integer}
{Origin: testlib-kitten, chkcomp.pas}
{$I trans.inc}
program macro;
uses testlib_english;
var jury, cont:extended;
begin
  jury:=ans.readreal;
  cont:=ouf.readreal;
  if int (jury)<>jury then quit (_fail, 'Not an integer: '+r2s (jury));
  if int (cont)<>cont then quit (_pe, 'Not an integer: '+r2s (cont));
  if not ouf.seekeof then quit (_pe, 'EOF expected');
  if jury<>cont then quit (_wa, 'Required: '+cp2s (jury)+', got: '+cp2s (cont));
  quit (_ok, 'Answer: ' + cp2s (cont));
end.
