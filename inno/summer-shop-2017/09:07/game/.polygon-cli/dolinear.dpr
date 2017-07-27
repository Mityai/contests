{$apptype console}

uses sysutils;

var i,j,n:longint;
    p:array[1..10000]of longint;

begin
  n:=strtoint(paramstr(1));
  randseed:=strtoint(paramstr(2));

  p[1]:=1;
  for i:=2 to n do
    begin
      j:=random(i)+1;
      p[i]:=p[j];
      p[j]:=i;
    end;

  writeln(n,' ',n-1, ' ', random(n) + 1);
  for i:=1 to n-1 do
    writeln(p[i],' ',p[i+1]);
end.