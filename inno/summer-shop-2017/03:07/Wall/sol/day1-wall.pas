{IOI 2014 Problem Wall, solution by Pavel Mavrin}

uses Math;

const
  MAXN = 2000000;
  MAXH = 1000000000;
  MINH = 0;

var
  n, k, i: longint;
  op, left, right, height: array[0..MAXN - 1] of longint;
  lb, rb : array of longint;

procedure setbound(i, h1, h2: longint);
begin
  if lb[i] >= h2 then begin
    lb[i] := h2;
    rb[i] := h2;
  end else if rb[i] <= h1 then begin
    lb[i] := h1;
    rb[i] := h1;
  end else begin
    lb[i] := max(lb[i], h1);
    rb[i] := min(rb[i], h2);
  end;
end;

procedure relax(i: longint);
begin
  setbound(i * 2 + 1, lb[i], rb[i]);
  setbound(i * 2 + 2, lb[i], rb[i]);
  lb[i] := MINH;
  rb[i] := MAXH;
end;

procedure add(i, ll, rr, l, r, h1, h2: longint);
var m: longint;
begin
  if rr > ll + 1 then relax(i);
  if (ll >= l) and (rr <= r) then begin
    setbound(i, h1, h2);
  end else if (ll >= r) or (l >= rr) then begin
    exit;
  end else begin
    m := (ll + rr) div 2;
    add(i * 2 + 1, ll, m, l, r, h1, h2);
    add(i * 2 + 2, m, rr, l, r, h1, h2);
  end;
end;

function get(i, ll, rr, x: longint): longint;
var m: longint;
begin
  if rr > ll + 1 then begin
    relax(i);
    m := (ll + rr) div 2;
    if x < m then
      result := get(i * 2 + 1, ll, m, x)
    else
      result := get(i * 2 + 2, m, rr, x)
  end else begin
    result := lb[i];
  end;
end;

procedure buildWall(column, numPhase: longint);
var
  i, size: integer;
begin
  size := 1;
  while size < column * 2 do 
    size := size * 2;
  setlength(lb, size);
  setlength(rb, size);
  for i := 0 to numPhase - 1 do begin
    if op[i] = 1 then 
      add(0, 0, column, left[i], right[i] + 1, height[i], MAXH)
    else
      add(0, 0, column, left[i], right[i] + 1, MINH, height[i])
  end;
  for i := 0 to column - 1 do begin
    writeln(get(0, 0, column, i));
  end;
end;

begin
  read(n, k);
  for i := 0 to k - 1 do
    read(op[i], left[i], right[i], height[i]);
  buildWall(n, k);
end.
