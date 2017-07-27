/*
*/

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include "testlib.h"

using namespace std;

const int N = 200000;

int currentTest;

void my_random_shuffle(vector <int> & v)
{
	for (int i = 0; i < int(v.size()); ++i)
		swap(v[i], v[rnd.next(0, i)]);
}

struct Test {
	vector <string> requests;

	static char s[100];
	int lastNode;

	vector <bool> exists;
	vector <int> parent;

	Test()
	{
		lastNode = 0;
		exists.push_back(true);
		parent.push_back(-1);
	}

	int getCountRequests() const
	{
		return int(requests.size());
	}

	int getLastNode() const
	{
		return lastNode;
	}

	void add(int v)
	{
		++lastNode;
		sprintf(s, "+ %d", v + 1);
		requests.push_back(string(s));
		exists.push_back(true);
		parent.push_back(v);
	}

	void remove(int v)
	{
		sprintf(s, "- %d", v + 1);
		requests.push_back(string(s));
		exists[v] = false;
	}

	void lca(int u, int v)
	{
		sprintf(s, "? %d %d", u + 1, v + 1);
		requests.push_back(string(s));
	}

	int getRandomExistingNode()
	{
		int u;
		do
		{
			u = rnd.next(0, lastNode);
		} while (!exists[u]);
		return u;
	}

	void removeNodes(int current, int count)
	{
		if (getCountRequests() + count > N)
			return ;

		vector <int> v;

		while (current != 0 && exists[current] && count != 0)
		{
			v.push_back(current);
			current = parent[current];
			--count;
		}

		if (rnd.next(0, 1) == 0)
			reverse(v.begin(), v.end());
		int step = rnd.next(1, 6);
		for (int i = 0; i < step; ++i)
			for (int j = i; j < int(v.size()); j += step)
				remove(v[j]);
	}

	void doManyLCA(int countRequests)
	{
		while (getCountRequests() < countRequests)
		{
			int u = getRandomExistingNode();
			int v = getRandomExistingNode();
			lca(u, v);
		}
	}

	void doManyRemoveAndLCA(int countRequests)
	{
		while (getCountRequests() < countRequests)
		{
			if (rnd.next(0, 8) != 0)
			{
				int u = getRandomExistingNode();
				int v = getRandomExistingNode();
				lca(u, v);
			}
			else
			{
				int v = getRandomExistingNode();
				int count = rnd.next(1, 1000);
				removeNodes(v, count);
			}
		}
	}

	void print()
	{
	#ifdef DBG1
		sprintf(s, "%02d", currentTest++);
	#else
		sprintf(s, "%d", currentTest++);
	#endif
		freopen(s, "w", stdout);

		ensure(int(requests.size()) <= N);
		printf("%d\n", int(requests.size()));
		for (int i = 0; i < int(requests.size()); ++i)
			printf("%s\n", requests[i].c_str());
	}

	void addHairLine(int first, int len, int power)
	{
		for (int i = 0; i < len; ++i)
		{
			int currentRoot = (i == 0) ? first : lastNode;
			for (int j = 0; j < power; ++j)
				add(currentRoot);
		}
	}

	void addLine(int first, int len)
	{
		addHairLine(first, len, 1);
	}
};

char Test::s[100];

void test0()
{
	Test test;

	for (int i = 1; i < N; ++i)
		test.add(rnd.next(0, test.getLastNode()));

	int u = test.getRandomExistingNode();
	int v = test.getRandomExistingNode();
	test.lca(u, v);

	test.print();
}

void test1(bool flag)
{
	Test test;
	const int k = 180;
	const int n = (N - 2 * k - k * k) / 2;

	test.addLine(0, n);

	int first[2];

	for (int j = 0; j < 2; ++j)
	{
		first[j] = test.getLastNode() + 1;
		test.addLine(n, k);
	}

	for (int i = 0; i < n; ++i)
		test.remove(flag ? i + 1 : n - i);

	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			test.lca(first[0] + i, first[1] + j);

	test.print();
}

void test2(const int count)
{
	Test test;

	const int len = N / 2 / count;
	for (int i = 0; i < count; ++i)
	{
		int root = test.getRandomExistingNode();
		test.addLine(root, len);
	}

	test.doManyLCA(N);

	test.print();
}

void test3(const int count, const int power)
{
	Test test;

	const int len = N / 2 / count / power;
	for (int i = 0; i < count; ++i)
	{
		int root = test.getRandomExistingNode();
		test.addHairLine(root, len, power);
	}

	test.doManyLCA(N);

	test.print();
}

void test4(const int count, const int power)
{
	Test test;

	const int len = N / 2 / count / power;
	for (int i = 0; i < count; ++i)
	{
		int root = test.getRandomExistingNode();
		test.addHairLine(root, len, power);
	}

	test.doManyRemoveAndLCA(N);

	test.print();
}

void test5()
{
	Test test;

	for (int i = 0; i < N / 2; ++i)
		test.add(0);
	test.doManyLCA(N);

	test.print();
}

void test6()
{
	Test test;

	test.addLine(0, 1);
	test.addHairLine(1, 1, N / 3);
	test.doManyLCA(2 * N / 3);
	test.removeNodes(1, 1);
	test.doManyLCA(N);

	test.print();
}

void test7()
{
	Test test;

	test.addLine(0, N - 5);

	test.lca(0, test.getLastNode());
	test.lca(1, test.getLastNode());
	test.lca(test.getLastNode() - 1, test.getLastNode());

	test.remove(test.getLastNode());
	test.lca(test.getLastNode() - 1, test.getLastNode() - 2);

	test.print();
}

void test8()
{
	Test test;

	const int n1 = N / 2;
	const int n2 = N - n1 - 1;

	test.addLine(0, n1);
	int u = test.getLastNode();
	test.addLine(0, n2);
	int v = test.getLastNode();

	test.lca(u, v);

	test.print();
}

void test9()
{
	Test test;

	vector <int> nodes;
	const int n = N / 2 - 10;
	for (int i = 0; i < n; ++i)
	{
		test.add(i);
		nodes.push_back(i + 1);
	}

	my_random_shuffle(nodes);

	for (int i = 0; i < int(nodes.size()); ++i)
		test.remove(nodes[i]);

	test.lca(0, 0);
	test.add(0);
	test.lca(test.getLastNode(), 0);

	test.print();
}

int main(int argc, char** argv)
{
	registerGen(argc, argv);

	currentTest = 5;

	test0(); //5

	test1(true); //6
	test1(false); //7

	test2(2); //8
	test2(10); //9
	test2(100); //10
	test2(1000); //11

	test3(1, 100); //12
	test3(2, 100); //13
	test3(100, 100); //14
	test3(50, 200); //15

	test4(500, 20); //16
	test4(50, 200); //17
	test4(50, 300); //18
	test4(100, 2); //19
	test4(100, 1); //20

	currentTest = 26;

	test5(); //26
	test6(); //27
	test7(); //28
	test8(); //29
	test9(); //30

	return 0;
}
