// Author: Ivan Kazmenko (gassa@mail.ru)
import std.algorithm;
import std.conv;
import std.format;
import std.math;
import std.random;
import std.range;
import std.stdio;
import std.typecons;

struct LCG // for portability: 48-bit random numbers engine used in Java
{
	static immutable long LCG_MULT = 0x5_DEEC_E66DL;
	static immutable long LCG_ADD  =           0xBL;
	static immutable long LCG_MASK = (1L << 48) - 1;

	long state;
	
	void init (long seed)
	{
		state = (seed ^ LCG_MULT) & LCG_MASK;
	}

	int next ()
	{
		state = ((state * LCG_MULT) + LCG_ADD) & LCG_MASK;
		return cast (int) (state >> 17);
	}

	int uniform (int range) // [0..range)
	{
		if (range <= 0)
		{
			assert (false);
		}
		if ((range & -range) == range)
		{
			return cast (int) ((range * 1L * next ()) >> 31);
		}
		int res, temp;
		do
		{
			temp = next ();
			res = temp % range;
		}
		while (temp - res + (range - 1) < 0);
		return res;
	}

	int uniform (int lo, int hi) // [lo..hi]
	{
		return lo + uniform (hi - lo + 1);
	}
}

struct Time
{
	int value;

	Time opBinary (string op) (const Time other) const
	    if (op == "+" || op == "-")
	{
		return mixin ("Time (value " ~ op ~ " other.value)");
	}

	string toString ()
	{
		return value.text;
	}

	string toPrettyString ()
	{
		return format ("%02d:%02d:%02d", value / 3600,
		    (value / 60) % 60, value % 60);
	}
}

Time seconds (int value)
{
	return Time (value);
}

Time minutes (int value)
{
	return Time (value * 60);
}

Time hours (int value)
{
	return Time (value * 60 * 60);
}

struct Point
{
	int x;
	int y;

	string toString ()
	{
		return format ("%s %s", x, y);
	}
}

long distSquared () (const auto ref Point p, const auto ref Point q)
{
	return (((q.x - p.x) * 1L) ^^ 2) + (((q.y - p.y) * 1L) ^^ 2);
}

struct Query
{
	int from;
	int to;
	Time moment;

	string toString ()
	{
		return format ("%s %s %s", from, to, moment);
	}
}

struct Driver
{
	int garage;
	Time momentStart;
	Time momentFinish;

	string toString ()
	{
		return format ("%s %s %s", garage, momentStart, momentFinish);
	}
}

struct Test
{
	static immutable Point origin = Point (0, 0);

	LCG rnd;
	uint seed;
	int r, a, g, q, n, dm, d;

	Point [] point;
	Query [] query;
	Driver [] driver;
	int [] [] gdist;
	Time [] [] gtime;

	@disable this (this);

	void generate (uint newSeed)
	{
		seed = newSeed;
		rnd.init (seed);

		r = rnd.uniform (10_000, 50_000);

		do
		{
			a = rnd.uniform (1, 5);
			g = rnd.uniform (1, 10);
			q = rnd.uniform (500, 2000);
			n = a + g + q;
		}
		while (n > 2000);

		dm = cast (int) ((r * 1.0 * q / 100_000).ceil);
		d = rnd.uniform (dm, 2 * dm);

		generatePoints ();
		generateQueries ();
		generateDrivers ();
		generateMatrices ();
	}

	void generatePoints ()
	{
		point.length = 0;
		point.reserve (n);
		bool [Point] visited;

		Point uniformFreePoint (int r)
		{
			Point res;
			do
			{
				res.x = rnd.uniform (-r, +r);
				res.y = rnd.uniform (-r, +r);
			}
			while (distSquared (origin, res) > r * 1L * r ||
			    res in visited);
			return res;
		}

		void addFarPoints (int num)
		{
			int startPos = cast (int) point.length;
			foreach (i; 0..num)
			{
				Point [] temp;
				long [] minDistSquared;
				auto maxDistSquared = long.min;
				foreach (j; 0..i + 1)
				{
					auto curPoint = uniformFreePoint (r);
					auto curDistSquared = long.max;
					foreach (k; 0..i)
					{
						curDistSquared = min
						    (curDistSquared,
						    distSquared
						    (point[startPos + k],
						    curPoint));
					}
					maxDistSquared = max (maxDistSquared,
					    curDistSquared);
					temp ~= curPoint;
					minDistSquared ~= curDistSquared;
				}

				int j = 0;
				while (maxDistSquared != minDistSquared[j])
				{
					j++;
					if (j > i)
					{
						assert (false);
					}
				}
				point ~= temp[j];
				visited[temp[j]] = true;
			}
		}

		addFarPoints (a);
 
		addFarPoints (g);

		Point skewFreePoint (int r)
		{
			Point res;
			do
			{
				Point pre;
				do
				{
					pre.x = rnd.uniform (-r, +r);
					pre.y = rnd.uniform (-r, +r);
				}
				while (distSquared (origin, pre) > r * 1L * r);

				static immutable int p = 1_000_003;
				int s = rnd.uniform (1, p);
				res = Point (cast (int)
				    (round (pre.x * 1.0L * s / p)), cast (int)
				    (round (pre.y * 1.0L * s / p)));
			}
			while (res in visited);
			return res;
		}

		foreach (i; 0..q)
		{
			auto curPoint = skewFreePoint (r);
			point ~= curPoint;
			visited[curPoint] = true;
		}
	}

	void generateQueries ()
	{
		query.length = 0;
		query.reserve (q);
		auto times = new bool [Time] [a];
		int curNumber = a + g;
		while (query.length < q)
		{
			int t = rnd.uniform (0, 1);
			int atemp = rnd.uniform (1, a);
			int b = rnd.uniform (0, atemp - 1);
			Time m;
			do
			{
				m = rnd.uniform (3 * 60, 21 * 60).minutes;
			}
			while (m in times[b]);
			times[b][m] = true;
			int w = rnd.uniform (1, 20);
			int c;
			do
			{
				c = rnd.uniform (1, w);
			}
			while (query.length + c > q);
			foreach (i; 0..c)
			{
				query ~= Query
				    ((t == 0) ? curNumber : b,
				    (t == 0) ? b : curNumber, m);
				curNumber++;
			}
		}
	}

	void generateDrivers ()
	{
		driver.length = 0;
		driver.reserve (d);
		foreach (i; 0..d)
		{
			int gtemp = rnd.uniform (1, g);
			int h = rnd.uniform (0, gtemp - 1);
			auto m = rnd.uniform (0, 12).hours;
			driver ~= Driver (h + a, m, m + 12.hours);
		}
	}

	void generateMatrices ()
	{
		gdist = new int [] [] (n, n);
		gtime = new Time [] [] (n, n);
		foreach (u; 0..n)
		{
			foreach (v; 0..n)
			{
				int e = cast (int) ((distSquared
				    (point[u], point[v]) * 1.0L).sqrt.ceil);
				int t = cast (int) ((e * 60.0L / 1000).ceil);
				gdist[u][v] = rnd.uniform (e, 2 * e);
				gtime[u][v] = rnd.uniform (t, 2 * t).seconds;
			}
		}
	}

	void write (File fout = stdout)
	{
		debug {stderr.writefln ("seed = %s, r = %s, dm = %s, " ~
		    "a = %s, g = %s, q = %s, d = %s",
		    seed, r, dm, a, g, q, d);}

		fout.writeln (seed);
		fout.writeln (a, " ", g, " ", q, " ", d);
		fout.writefln ("%(%s\n%)", point);
		fout.writefln ("%(%s\n%)", query);
		fout.writefln ("%(%s\n%)", driver);
//		fout.writefln ("%(%(%s %)\n%)", gdist);
//		fout.writefln ("%(%(%s %)\n%)", gtime);
		fout.writeln
		    (gdist.map !(x => x.map !(text).join (" ")).join ("\n"));
		fout.writeln
		    (gtime.map !(x => x.map !(text).join (" ")).join ("\n"));
	}
}

void main (string [] args)
{
	uint seed = unpredictableSeed;
	if (args.length > 1)
	{
		seed = args[1].to !(uint);
	}

	Test test;
	test.generate (seed);
	test.write ();
}
