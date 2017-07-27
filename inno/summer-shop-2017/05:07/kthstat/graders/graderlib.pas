unit graderlib;

interface

const maxN = 200000;
type mas = array [0..maxN - 1] of longint;

procedure Main;

implementation

uses kthstat, sysutils;

var
  isRun : boolean;
  n, tn : longint;
  a : mas;
  curTime : extended;

procedure Main;
var
  x, y, z, i : longint;
  t : char;
begin
  if isRun then begin
    writeln('SV User tries to hack the system');
    halt(3128);
  end;
  isRun := true;

  curTime := now();

  read(n);
  for i := 0 to n - 1 do
    read(a[i]);

  Start(n, a);
  tn := 0;

  while not seekeof do begin
    repeat
      read(t);
    until ord(t) > 32;
    if t = '+' then begin
      read(x, y);
      Add(x, y);
    end else if t = '-' then begin
      read(x);
      Del(x);
    end else if t = '?' then begin
      read(x, y, z);
      writeln(Get(x, y, z));
    end else begin
      writeln('Unknown option: ' + t);
      halt(3128);
    end;
    inc(tn);
  end;

  isRun := false;
  writeln('OK, ', tn, ' tests, time = ', (now() - curTime):0:2);

end;

begin
  isRun := false;
end.

