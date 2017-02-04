%Author: Ivan Kazmenko
prologues := 0;
u = 1 cm;
w = 0.01 u;

input TEX;

%verbatimtex
%&latex
%\documentclass[a4paper,12pt]{article}
%\documentclass{minimal}
%\usepackage[T2A]{fontenc}
%\usepackage[cp1251]{inputenc}
%\usepackage[english,russian]{babel}
%etex;

string buf;
numeric cur;

def isdigit (expr s) =
	((ASCII (s) >= ASCII ("0")) and (ASCII (s) <= ASCII ("9")))
enddef;

def issignordigit (expr s) =
	(isdigit (s) or ((s) = "-"))
enddef;

def isalpha (expr s) =
	(((ASCII (s) >= ASCII ("a")) and (ASCII (s) <= ASCII ("z"))) or
	 ((ASCII (s) >= ASCII ("A")) and (ASCII (s) <= ASCII ("Z"))))
enddef;

def isalphaordigit (expr s) =
	(isalpha (s) or isdigit (s))
enddef;

def isnonwhitespace (expr s) =
	(isalphaordigit (s) or (s = "-"))
enddef;

def skip = begingroup
	forever:
		exitif isnonwhitespace (substring (cur, cur + 1) of buf);
		cur := cur + 1;
	endfor;
endgroup; enddef;

def getnum = begingroup
	numeric res, sign;
	string temp;
	skip;
	res := 0;
	sign := 1;
	forever:
		temp := substring (cur, cur + 1) of buf;
		exitunless issignordigit (temp);
		if temp = "-":
			if sign = -1:
				sign := 0;
				exit;
			else:
				sign := -sign;
			fi;
		else:
			res := res * 10 + ASCII (temp) - 48;
		fi;
		cur := cur + 1;
	endfor;
	res := res * sign;
%	show res;
	res
endgroup; enddef;

def getword = begingroup
	string res;
	numeric temp;
	skip;
	temp = cur;
	forever:
		exitunless isalphaordigit (substring (cur, cur + 1) of buf);
		cur := cur + 1;
	endfor;
	res := substring (temp, cur) of buf;
%	show res;
	res
endgroup; enddef;

shiftx := 0;
shifty := 0;
curu := u;

def t (expr p) =
	(p) transformed (identity shifted (1 + shiftx, 1 + shifty) scaled curu)
enddef;

def p (expr x, y, z) =
	((y + 0.5 x, z - 0.5 x))
enddef;

def next_pos = begingroup
	curx := nextx;
	if curx + width + 2 > maxwidth:
		curx := 0;
		cury := nexty + 2;
	fi;
	nextx := curx + width + 2;
	nexty := max (nexty, cury + height);
endgroup; enddef;

def draw_step (expr xs, ys, zs, xt, yt, zt, mode) = begingroup
        numeric height, width, xc, yc, zc, xlo, xhi, xa, xb;
        color shade;

	curu := 0.5 u;
	xlo := 0;
	xhi := 0;
	xlo := min (xlo, xs);
	xhi := max (xhi, xs);
	xlo := min (xlo, xt);
	xhi := max (xhi, xt);
	xlo := xlo - 2;
	xhi := xhi + 2;
	shiftx := curx - 0.5 xlo - ys + 1;
	shifty := cury + 0.5 xhi - zs;
	width := (xhi - xlo) * 0.5 + yt - ys + 1;
	height := (xhi - xlo) * 0.5 + zt - zs;
	if mode:
		shade := 0.3 white;
		shiftx := shiftx + 2;
		width := width + 4;
	else:
		shade := 0.0 white;
	fi;
	next_pos;

	pickup pencircle scaled w;
	for xc := xlo upto xhi:
		draw t (p (xc, ys - 0.4, zs) -- p (xc, 0, zs))
		 withcolor shade;
		draw t (p (xc, 0, zs) -- p (xc, 0, zt))
		 withcolor shade;
		draw t (p (xc, 0, zt) -- p (xc, yt + 0.4, zt))
		 withcolor shade;
	endfor;
	for yc := ys upto 0:
		draw t (p (xlo - 0.4, yc, zs) -- p (xhi + 0.4, yc, zs))
		 withcolor shade;
	endfor;
	for zc := zs + 1 upto zt - 1:
		draw t (p (xlo - 0.4, 0, zc) -- p (xhi + 0.4, 0, zc))
		 withcolor shade;
	endfor;
	for yc := 0 upto yt:
		draw t (p (xlo - 0.4, yc, zt) -- p (xhi + 0.4, yc, zt))
		 withcolor shade;
	endfor;

	pickup pencircle scaled 9 w;
	draw t (p (0, 0, 0)) withcolor shade;
	label.llft ("O", t (p (0, 0, 0)));

	pickup pencircle scaled 3 w;
	drawarrow t (p (xlo - 0.4, 0, 0) -- p (xhi + 0.7, 0, 0))
	 withcolor shade;
	label.llft ("x", t (p (xhi + 0.4, 0, 0)));
	drawarrow t (p (0, ys - 0.4, 0) -- p (0, yt + 0.7, 0))
	 withcolor shade;
	label.bot ("y", t (p (0, yt + 0.4, 0)));
	drawarrow t (p (0, 0, zs - 0.4) -- p (0, 0, zt + 0.7))
	 withcolor shade;
	label.ulft ("z", t (p (0, 0, zt + 0.4)));

	pickup pencircle scaled 4 w;
	draw t (p (xlo - 1.0, 0, zs) -- p (xhi + 0.4, 0, zs))
	 withcolor shade;
	draw t (p (xlo - 1.0, 0, zt) -- p (xhi + 0.4, 0, zt))
	 withcolor shade;
	drawdblarrow t (p (xlo - 0.7, 0, zs) -- p (xlo - 0.7, 0, zt))
	 withcolor shade;
	label.lft ("h", t (p (xlo - 0.7, 0, (zs + zt) * 0.5)));

	if mode:
		pickup pencircle scaled 15 w;
		draw t (p (xs, ys, zs));
		draw t (p (xt, yt, zt));

		pickup pencircle scaled 10 w;
		xa = xs + (xt - xs) * (-ys) / (zt + yt - ys);
		xb = xs + (xt - xs) * (-ys + zt) / (zt + yt - ys);
		draw t (p (xs, ys, 0) -- p (xa, 0, 0) --
		        p (xb, 0, zt) -- p (xt, yt, zt));

		label ("Улитка" infont "latt1000" rotated 315,
		 t (p (xs, ys - 0.8, zs)));
		label ("Травинка" infont "latt1000" rotated 315,
		 t (p (xt, yt + 0.8, zt)));
	fi;
endgroup; enddef;

def process (expr f, h) = begingroup
	string inputfile;
	numeric curx, cury, nextx, nexty;

	inputfile = f;
	curx := 0;
	cury := 0;
	nextx := 0;
	nexty := 0;

	buf := readfrom inputfile;
	cur := 0;
	xs := getnum;
	ys := getnum;
	zs := getnum;
	buf := readfrom inputfile;
	cur := 0;
	xt := getnum;
	yt := getnum;
	zt := getnum;
	draw_step (xs, ys, zs, xt, yt, zt, h);

	buf := readfrom inputfile; % EOF
endgroup; enddef;

beginfig (1);
	maxwidth := 50;
	process ("example.txt", false);
endfig;

beginfig (2);
	maxwidth := 50;
	process ("example.txt", true);
endfig;

end.
