{$O+,R-,Q-,S+}
uses testlib;
const MaxK=20;
      MaxM=150;
      MaxN=150;
type integer=longint;
var m, n:integer;
    a:array [1..MaxM] of set of 1..MaxN;
    {b:array [1..MaxN] of set of 1..MaxM;}

function answer (var f:instream):integer;
var i, j, v, ms, ns:integer;
    bs:array [1..MaxM] of integer;
    gl:array [1..MaxN] of integer;
begin
  v:=f.readlongint;
  ms:=f.readlongint; ns:=f.readlongint;
  if (ms<0) or (ms>m) or (ns<0) or (ns>n) or (ms+ns<>v) then
    f.quit (_wa, 'Invalid number of boys or girls');
  for i:=1 to ms do begin
    bs[i]:=f.readlongint;
    if (bs[i]<1) or (bs[i]>m) then f.quit (_wa, 'Invalid boy id');
    if (i>1) and (bs[i]<=bs[i-1]) then f.quit (_pe, 'Not ascending');
  end;
  for j:=1 to ns do begin
    gl[j]:=f.readlongint;
    if (gl[j]<1) or (gl[j]>n) then f.quit (_wa, 'Invalid girl id');
    if (j>1) and (gl[j]<=gl[j-1]) then f.quit (_pe, 'Not ascending');
  end;
  for i:=1 to ms do
    for j:=1 to ns do
      if {not (bs[i] in b[gl[j]]) or} not (gl[j] in a[bs[i]]) then
        f.quit (_wa, 'no edge found');
  answer:=v;
end;



var k, ct, i, j, c:integer;
    jury, cont:integer;
begin
  k:=inf.readlongint;
  for ct:=1 to k do begin
    m:=inf.readlongint;
    n:=inf.readlongint;
    
    for i:=1 to m do a[i]:=[];
{    for j:=1 to n do b[j]:=[];}
    for i:=1 to m do begin
      repeat
        c:=inf.readlongint;
        if c=0 then break;
        include (a[i], c); 
        { include (b[c], i); }
      until false;
    end;
    jury:=answer (ans);
    cont:=answer (ouf);
    if jury<cont then quit (_fail, 'Contestant knows a better solution!')
    else
    if jury>cont then quit (_wa, 'Not optimal');
  end;
  quit (_ok, '');
end.