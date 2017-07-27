// 20 points (TL) by Sergey Kopeliovich

unit kthstat;

interface

uses graderlib;

procedure Start( nn : longint; var aa : mas );

procedure Add( i, x : longint );
procedure Del( i : longint );

function Get( L, R, x : longint ) : longint;

implementation

var
  i, j, n : longint;
  a : mas;

procedure Start( nn : longint; var aa : mas );
begin
  n := nn;
  for i := 0 to n - 1 do
    a[i] := aa[i];
end;


procedure Add( i, x : longint );
begin
  for j := n downto i + 1 do
    a[j] := a[j - 1];
  a[i] := x;
  inc(n);
end;

procedure Del( i : longint );
begin
  for j := i + 1 to n - 1 do
    a[j - 1] := a[j];
  dec(n);
end;

function Get( L, R, x : longint ) : longint;
var
  cnt : longint;
begin
  cnt := 0;
  for i := L to R do
    if (a[i] <= x) then
      inc(cnt);
  Get := cnt;
end;

begin
end.
