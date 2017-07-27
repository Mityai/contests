#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
const int SIZE = 35;
const int MOD = (int)1e9 + 7;
 
template<class Type>
class Matrix
{
 
	Type  arr[SIZE][SIZE];
 
public:
 
	Matrix()
	{
		for(int r = 0; r < SIZE; r++)
			for(int l = 0;l < SIZE; l++)
				this->arr[r][l] = 0;
	}
 
	Matrix(int N)
	{
		for(int r = 0; r < SIZE; r++)
			for(int l = 0;l < SIZE; l++)
				this->arr[r][l] = 0;
 
		for(int r = 0, l = 0; r < SIZE; r++, l++)	this->arr[r][l] = N;
	}
 
	~Matrix(){	}
 
 
//member functions...
 
	Type get(int r,int l) { return ( this->arr[r][l] ); }
 
	Type set(Type mat[SIZE][SIZE]) {
 
		for(int r = 0; r < SIZE; r++)
			for(int l = 0;l < SIZE; l++)
				this->arr[r][l] = mat[r][l];
 
		return 0;
	}
 
 
 
 
//matrix operators...		
	Matrix < Type > operator * (Matrix <Type> & M)
	{
		Matrix<Type> T; 
 
		for(int r = 0; r < SIZE; r++)
		{
			for(int l = 0;l < SIZE; l++)
			{
				T.arr[r][l] = 0;
				
				for(int k = 0; k < SIZE; k++)
				{
					T.arr[r][l] += (arr[r][k] * M.arr[k][l]);
					T.arr[r][l] %= MOD;
				}
			}
		}
 
		return T;
	}
 
	//template <typename IntType>
	Matrix <Type> operator ^ (long long N)
	{
		Matrix <Type> X = *this;
		Matrix <Type> Ans(1);
 
		
		while(N)
		{
			if(N&1) Ans = Ans * X;
 
			X = X * X;
			
			N = N >> 1;
		}
 
		return Ans;
	}
 
};
 
 
int main()
{
	ios::sync_with_stdio(false);
 
	int TC;
	cin >> TC;
 
	long long mat[SIZE][SIZE];
 
	Matrix<long long> A, B(1);
	
	for(int test = 1; test <= TC; test++)
	{		
		int N, M;
		cin >> N >> M;
 
		for(int i = 0; i < SIZE; i++)
			for(int j = 0; j < SIZE; j++)
					mat[i][j] = 0;
 
		for(int i = 1; i <= M; i++)
		{
			for(int j = i-2; j <= i+2 && j <= M; j++)
				if(j >=0)
					mat[i][j] = 1;
			mat[i][i]++;
		}
 
		A.set(mat);
 
		
		if(N == 1) cout << M << "\n";
		else if (N == 2) cout  << 2*M - 2 << "\n";
		else
		{
			int p;
			if((N & 1) == 0) p = (N >> 1) - 1;
			else p = N >> 1;
 
			A = A ^ (int)p;
			
			long long val = 0;
			if((N & 1))
			{
				for(int i = 1; i <= M; i++)
				{
					for(int j = 1; j <= M; j++)
					{	
						val += A.get(i,j);
						val %= MOD;
					}
				}
			}
			else
			{
				for(int i = 1; i <= M; i++)
				{
					for(int j = 1; j <= M; j++)
					{	
					
						if(j == 1 || j == M) val += A.get(i,j);
						else val += 2LL * A.get(i,j);
 
						val %= MOD;
					}
				}
			}
 
			cout << val << "\n";
		}
 
	}
 
	return 0;
} 
