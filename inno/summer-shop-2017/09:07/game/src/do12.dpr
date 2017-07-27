{$apptype console}

uses sysutils;

const n=7812;
      x=6123;

var i:longint;

begin
  writeln(n,' ',n-1, ' ', random(n) + 1);
  for i:=1 to n do
    if i<>x then
      writeln(x,' ',i);
end.