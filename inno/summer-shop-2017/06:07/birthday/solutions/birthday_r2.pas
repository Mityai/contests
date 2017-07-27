{$A+,B-,D+,E-,F-,G+,I+,L+,N-,O-,P-,Q-,R-,S-,T-,V+,X+,Y+}
{$M 16384,0,655360}
program macro;
const MaxK=20; MaxM=150; MaxN=150;
var
  N, M, C, C1  : integer;
  G            : array [1..MaxM, 1..MaxN] of boolean;
  S, D         : array [1..MaxM] of boolean;
  E            : array [1..MaxN] of boolean;
  A            : array [1..MaxM] of integer;
  B            : array [1..MaxN] of integer;

function rec (v : integer) : boolean;
var i : integer;
begin
  rec := false;
  if S[v] then exit;
  S[v] := true;
  for i := 1 to N do
    if not G[v,i] and ((B[i] = 0) or rec(B[i])) then begin
      A[v] := i;  B[i] := v;  rec := true; break
    end;
end;

var
  i, j, K : integer;
  F       : boolean;
begin
  assign (input, 'birthday.in');  reset (input);
  assign (output, 'birthday.out');  rewrite (output);
  read(K);  if (K <= 0) or (K > MaxK) then runerror (239);
  repeat
    read (M, N);
    if (M < 0) or (N < 0) or (M > MaxM) or (N > MaxN) then runerror (239);
    fillchar (G, sizeof(G), 0);
    for i := 1 to M do
      repeat
        read(j);  if j = 0 then break;
        if (j < 0) or (j > N) or G[i,j] then runerror (239);
        G[i,j] := true
      until false;
    C := 0;
    fillchar (D, sizeof(D), 0);
    fillchar (E, sizeof(E), 0);
    fillchar (A, sizeof(A), 0);
    fillchar (B, sizeof(B), 0);
    for i := 1 to M do begin
      fillchar (S, i, 0);
      if rec(i) then begin inc(C); D[i]:=true end else
      for j := 1 to i-1 do
        if S[j] then begin D[j]:=false; E[A[j]]:=true end
    end;
    C1 := 0;
    for i := 1 to M do if not D[i] then inc(C1);
    writeln (N+M-C);
    writeln (C1, ' ', N+M-C-C1);
    F := false;
    for i := 1 to M do if not D[i] then begin
      if F then write (' ');
      F := true;  write(i)
    end;
    writeln;
    F := false;
    for i := 1 to N do if not E[i] then begin
      if F then write (' ');
      F := true;  write(i)
    end;
    writeln;
    dec(K); if K > 0 then writeln
  until K = 0
end.