#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

const int MOD=1000000007;

typedef vector < vector < long long > > Matrix;

Matrix & Resize (Matrix &M, int Row, int Col)
{
	M.resize(Row);
	for(int i=0;i<Row;++i)
		M[i].resize(Col,0);
	return M;
}

Matrix & Resize(Matrix & M, int n)
{
	return Resize(M,n,n);
}

Matrix &  Mul(const Matrix & A, const Matrix & B, Matrix & R)
{
	for(int i=0;i<R.size();++i)
	for(int j=0;j<R[0].size();++j)
	{
		R[i][j]=0;
		for(int s=0;s<B.size();++s)
		{
			R[i][j]+=A[i][s]*B[s][j];
			R[i][j]%=MOD;
		}
	}
	return R;
}

Matrix & Unary(Matrix & A)
{
	for(int i=0;i<A.size();++i)
	{
		for(int j=0;j<A.size();++j)
		{
			A[i][j]=0;
		}
		A[i][i]=1;
	}
}

Matrix & Copy(const Matrix & A, Matrix & B)
{
	for(int i=0;i<A.size();++i)
	for(int j=0;j<A[0].size();++j)
	B[i][j]=A[i][j];
}

Matrix & Power(Matrix &A, int n)
{
	Matrix B, T;
	Resize(B,A.size());
	Resize(T,A.size());
	Unary(B);
	while(n)
	{
		if(n%2)
		{
			Mul(A,B,T);
			Copy(T,B);
			--n;
		}
		else
		{
			Mul(A,A,T);
			Copy(T,A);
			n/=2;
		}
	}
	Copy(B,A);
	return A;
}

int main()
{
	int n, i, j;
	cin>>n;
	Matrix A;
	Resize(A,10,10);
	for(i=0;i<10;++i)
		for(j=0;j<10;++j)
			A[i][j]=0;
	for(i=1;i<9;++i)
	{
		A[i][i]=A[i][i-1]=A[i][i+1]=1;
	}
	A[0][0]=A[0][1]=A[9][8]=A[9][9]=1;

	Power(A,n-1);
	Matrix V1, V2;
	Resize(V1,10,1);
	Resize(V2,10,1);
	for(i=1;i<10;++i)
		V1[i][0]=1;
	V1[0][0]=0;
	Mul(A,V1,V2);
	for(i=1;i<10;++i)
	{
		V2[0][0]+=V2[i][0];
		V2[0][0]%=MOD;
	}
	cout<<V2[0][0]<<endl;
	return 0;
}
