{$apptype console}

uses sysutils;

const n=4999;

var i:longint;

begin
  writeln(2*n+1,' ',2*n, ' ', random(2 * n + 1) + 1);
  for i:=1 to n do
    writeln(i,' ',n+1);
  for i:=n+2 to 2*n+1 do
    writeln(n+1,' ',i);
end.