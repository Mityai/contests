{$apptype console}

uses sysutils;

var num,last,c,i,j,n,m:longint;
    a,b:array[1..100000]of longint;
    p:array[1..10000]of longint;

begin
  n:=strtoint(paramstr(1));
  m:=strtoint(paramstr(2));
  randseed:=strtoint(paramstr(3));

  c:=0;
  last:=(n*(n-1)) div 2;
  num:=last div m;
  for i:=1 to n-1 do
    for j:=i+1 to n do begin
      if c<m then
        if (random(num)=0)or(last=m-c) then begin
          inc(c);
          a[c]:=i;
          b[c]:=j;
        end;
      dec(last);
    end;

  p[1]:=1;
  for i:=2 to n do
    begin
      j:=random(i)+1;
      p[i]:=p[j];
      p[j]:=i;
    end;

  writeln(n,' ',c, ' ', random(n) + 1);
  for i:=1 to c do
    writeln(p[a[i]],' ',p[b[i]]);
end.