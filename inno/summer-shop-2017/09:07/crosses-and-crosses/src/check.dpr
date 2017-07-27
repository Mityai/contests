uses	
	SysUtils, testlib;

var
	n, ja, pa: longint;

begin
	n := inf.readlongint;
	ja := ans.readlongint;
	pa := ouf.readlongint;

	if ja <> pa then
		quit(_wa, format('n = %d, expected: %d, found: %d', [n, ja, pa]));

	quit(_ok, format('n = %d, ans = %d', [n, pa]));	
end.