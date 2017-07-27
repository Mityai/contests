#ifndef __grader_h__
#define __grader_h__

#define maxN 100000

typedef int mas[maxN];

void Start( int n, mas a );

void Add( int i, int x );
void Del( int i );

int Get( int L, int R, int x );

#endif /* __grader_h__ */
