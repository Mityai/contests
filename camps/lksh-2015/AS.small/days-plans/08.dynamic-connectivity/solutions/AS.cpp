#include <map>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <assert.h>
#include <string>

using namespace std;
struct KOROVA{
	KOROVA(){
		srand('M' + 'O' + 'L' + 'O' + 'K' + 'O');
	}
} GbI;

typedef long long ll;

#define forn(i, n) for(int i = 0; i < n; i++)
#define fornn(i, a, n) for(int i = a; i < n; i++)
#define times clock() * 1.0 / CLOCKS_PER_SEC

const int N = 3e5 + 5;
const int K = 20;

/************************** Treap ********************************/

struct TreapNode {
	static TreapNode* null;
	TreapNode *l, *r, *p;
	int y;
	int size; // размер поддерева
	enum TYPE { VERTEX, EDGE };
	TYPE type; // node-у декартова дерева соответствует или вершина, или ребро исходного графа
	int i; // 0..n-1 -- индекс вершины или ребра
	int level; // уровень на котором живёт вершина, инвариант: f[level].vertexNode[vertex]->level == level
	int hasVertex; // есть ли node-VERTEX в поддереве, из которой торчат рёбра ранга level (adjacent[v][k].size() != 0)
	int hasEdge; // есть ли node-EDGE в поддереве ранга ровно level

	void calc(); // пересчитать size, hasVertex, hasEdge
	void calcToTop(); // пересчитать всё на пути до корня

	TreapNode() {
		memset(this, 0, sizeof(TreapNode));
		p = l = r = null;
		level = -1;
		i = -1;
	}
	TreapNode(TYPE type, int i, int level) : type(type), i(i), level(level) {
		y = (rand() << 16ll) ^ rand();
		p = l = r = null;
		size = 1;
	}

	bool operator == (TreapNode b){
		return size == b.size && hasVertex == b.hasVertex && hasEdge == b.hasEdge;
	}
};
TreapNode* TreapNode::null = new TreapNode();

void split(TreapNode* node, TreapNode* &l, TreapNode* &r, int k); // получает node, k; возвращает l, r
TreapNode* merge(TreapNode* l, TreapNode* r);
TreapNode* getRoot(TreapNode* node); // поднимается до корня
int positionInTreap(TreapNode* node); // поднимается до корня, вычисляем позицию


/************************** Forest ********************************/

struct Forest { // Лес, для каждого дерева которого, храним Эйлеров Обход в treap
	int level; // индекс Forest-а: инвариант f[level].level == level
	TreapNode* vertexNode[N]; // вершине исходного графа соответствует TreapNode
	TreapNode* edgeNode1[N]; // по номеру ребра i (ориентация туда) получить вершину в Treap
	TreapNode* edgeNode2[N]; // по номеру ребра i (ориентация обратно) получить вершину в Treap
	// У i-го ребра концы: edges[i].a, edges[i].b. Ориентация туда: a -> b. Ориентация обратно: b -> a.

	void init(int ); // Каждое Euler Tour Tree состоит из одной TreapNode, type=VERTEX
	void makeRoot(int vertex); // используется в cut() и link()
	void cut(int edge);
	void link(int edge);
	bool isConnected(int a, int b); // "внутреннее ребро или внешнее", по-другому "в одной компоненте связности a и b, или в разных"
	// getRoot(f[i].vertexNode[vertex]) -- корень treap, в котором лежит вершина исходного графа vertex в лесе уровня i
	// getRoot(f[i].edgeNode1[edge]) -- корень treap, в котором лежит ребро исходного графа edge в лесе уровня i

	void getSpanningEdges(TreapNode* root, vector<int> &spanning_edges); // все остовные рёбра ранга k в компоненте root (использует hasEdge)
	int getAllEdges(TreapNode* root, vector<int> &inner_edges);
	// Перебирает все НЕ остовные рёбра ранга k в компоненте root (используя hasVertex), внутренние складывает в inner_edges.
	// Выходит, когда натыкается на внешнее, возвращает номер найденного внешнего, если не нашла, то -1
};

struct Edge { // неориентированное
	int a, b; // вершины-концы
	int rank;
	int multi; // кратность ребра
	Edge(int a, int b) : a(a), b(b){
		multi = 1;
		rank = 0;
	}
};


set<int> adjacent[N][K]; // списки смежности рёбер: для каждой вершины, для каждого ранга храним все НЕ ОСТОВНЫЕ рёбра такого ранга

vector<Edge> edges; // все рёбра графа (неориентированные!)
Forest f[K]; // f[i] = остовный лес рёбер ранга 0..i
map<pair<int, int>, int> edgeIndex; // преобразователь пар вершин <a,b> в "индекс ребра"
void updateVertex(int, int);
void updateEdges(int, int);


/******************************************************************* MAX PLUSHKIN CODE *******************************************************************/

void TreapNode::calc()
{
	size = l -> size + r -> size + 1;
	hasVertex = l -> hasVertex || r -> hasVertex;
	hasEdge = l -> hasEdge || r -> hasEdge;
	if (type == VERTEX){
		hasVertex |= adjacent[i][level].size() != 0;
	}
	else{
		hasEdge |= edges[i].rank == level;
	}
}

void TreapNode::calcToTop()
{
	TreapNode *l = this;
	if(l == TreapNode::null)
		return;
	while(l -> p != TreapNode::null){
		TreapNode g = *l;
		l -> calc();
		if(g == *l)
			return;
		assert(l != l -> p);
		l = l -> p;
	}
}

void refresh(TreapNode* v)
{
	v->calc();
}

void split(TreapNode* v, TreapNode* &l, TreapNode* &r, int k) {
	if (v == TreapNode::null)
		return void((l = TreapNode::null, r = TreapNode::null));
	if (v -> l -> size >= k)
	{
		r = v;
		split(r -> l, l, r -> l, k);
		l -> p = TreapNode::null;
		r -> l -> p = r;
	}
	else
	{
		l = v;
		split(l -> r, l -> r, r, k - v -> l -> size - 1);
		r -> p = TreapNode::null;
		l -> r -> p = l;
	}
	refresh(v);
}

TreapNode* merge(TreapNode* l, TreapNode* r)
{
	if (l == TreapNode::null || r == TreapNode::null)
		return l == TreapNode::null ? r : l;
	if (l -> y > r -> y)
	{
		l -> r -> p = TreapNode::null;
		l -> r = merge(l -> r, r);
		l -> r -> p = l;
		refresh(l);
		return l;
	}
	else
	{
		r->l->p = TreapNode::null;
		r->l = merge(l, r->l);
		r->l->p = r;
		refresh(r);
		return r;
	}
}

TreapNode* getRoot(TreapNode* a)
{
	while (a -> p != TreapNode::null){
		assert(a != a -> p);
		a = a -> p;
	}
	return a;
}

int positionInTreap(TreapNode* a)
{
	assert(a != TreapNode::null);
	int pos = a -> l -> size + 1;
	while (a->p != TreapNode::null)
	{
		if (a -> p -> l == a) {
			a = a -> p;
			continue;
		}
		assert(a != a -> p);
		pos += a -> p -> l -> size + 1;
		a = a -> p;
	}
	return pos;
}

/******************************************************** GORBUNOV ROMAN CODE  **********************************************************************************/

ostream& operator << (ostream& cout, TreapNode* a) {
	if (a == TreapNode::null) {
		return cout << "NULL";
	}
	cout << a->l;
	cout << "(" << a->type << "; " << a->i << " " << a->size << ")";
	cout << a->r;
	return cout;
}

void Forest::init(int ops) {
	level = ops;
	for (int i = 0; i < N; i++) {
		vertexNode[i] = new TreapNode(TreapNode::VERTEX, i, level);
		edgeNode1[i] = edgeNode2[i] = TreapNode::null;
	}
}

void Forest::makeRoot(int vertex) {
	assert(vertex >= 0 && vertex < N);
	TreapNode* node = vertexNode[vertex];
	assert(node != TreapNode::null);
	int Index = positionInTreap(node);
	TreapNode *L, *R;
	split(getRoot(node), L, R, Index);
	merge(R, L);
	assert(node != TreapNode::null);
}

void Forest::cut(int edge) {
	assert(0 <= edge && edge < N);

	TreapNode* Left = edgeNode1[edge];
	TreapNode* Right = edgeNode2[edge];

	assert(Left != TreapNode::null);
	assert(Right != TreapNode::null);

	int IndexL = positionInTreap(Left);
	int IndexR = positionInTreap(Right);

	assert(Left != Right);
	assert(IndexL != IndexR);
	if (IndexL > IndexR) {
		swap(IndexL, IndexR);
		swap(Left, Right);
	}
	TreapNode* Root = getRoot(Left);
	TreapNode *l, *edge1, *m, *edge2, *r;

	assert(Root == TreapNode::null || (Root->size + 2) % 3 == 0);
	split(Root, l, r, IndexR);
	split(l, l, edge2, IndexR - 1);
	assert(edge2 == TreapNode::null || edge2->size == 1);
	split(l, l, m, IndexL);
	assert(m == TreapNode::null || (m->size + 2) % 3 == 0);
	split(l, l, edge1, IndexL - 1);
	assert(edge1 != TreapNode::null || (edge1->size + 2) % 3 == 0);
	Root = merge(l, r);
	assert(Root == TreapNode::null || (Root->size + 2) % 3 == 0);
}

void Forest::link(int edge) {
	assert(0 <= edge && edge < N);
	TreapNode *edge1 = new TreapNode(TreapNode::EDGE, edge, level);
	TreapNode *edge2 = new TreapNode(TreapNode::EDGE, edge, level);
	edgeNode1[edge] = edge1;
	edgeNode2[edge] = edge2;
	makeRoot(edges[edge].a);
	makeRoot(edges[edge].b);
	TreapNode *A = vertexNode[edges[edge].a];
	TreapNode *B = vertexNode[edges[edge].b];

	assert(A != TreapNode::null);
	assert(B != TreapNode::null);

	TreapNode *root = merge(getRoot(A), edge1);
	assert(root != TreapNode::null);

	root = merge(root, getRoot(B));
	assert(root != TreapNode::null);

	root = merge(root, edge2);
	assert(root != TreapNode::null);
	assert((root->size + 2) % 3 == 0);
}

bool Forest::isConnected(int a, int b) {
	assert(a >= 0 && a < N);
	assert(b >= 0 && b < N);
	assert(vertexNode[a] != TreapNode::null);
	assert(vertexNode[b] != TreapNode::null);
	return (getRoot(vertexNode[a]) == getRoot(vertexNode[b]));
}

/******************************************************************* ROMA & YAN *******************************************************************/

void Forest::getSpanningEdges(TreapNode *root, vector<int> &ans) {
	if (root == TreapNode::null) {
		return;
	}
	if (root -> hasEdge) {
		assert(root -> type == TreapNode::VERTEX || (root -> type == TreapNode::EDGE && edges[root -> i].rank >= root -> level));
		if (root -> type == TreapNode::EDGE && edges[root -> i].rank == root -> level) {
			ans.push_back(root -> i);
		}
		getSpanningEdges(root -> l, ans);
		getSpanningEdges(root -> r, ans);
	}
}

// перебирает все НЕ остовные рёбра ранга k в компоненте root (используя hasVertex), внутренние складывает в inner_edges,
// выходит, когда натыкается на внешнее, возвращает номер найденного внешнего
int Forest::getAllEdges(TreapNode *root, vector<int> &ans) {
	if (root == TreapNode::null) {
		return -1;
	}
	if (root->type == TreapNode::VERTEX) {
		for (int u : adjacent[root->i][root->level]) {
			Edge v = edges[u];
			assert(v.a >= 0 && v.b >= 0);
			if (isConnected(v.a, v.b)) {
				ans.push_back(edgeIndex[{v.a, v.b}]);
			}
			else {
				return edgeIndex[{v.a, v.b}];
			}
		}
	}
	int res = -1;
	if (root -> l -> hasVertex){
		res = max(res, getAllEdges(root->l, ans));
	}
	if (root -> r -> hasVertex){	
		res = max(res, getAllEdges(root->r, ans));
	}
	return res;
}


/**________________________NAUMOV STAS  AND  YUTMAN MISHKA HAVE WRITTEN THIS CODE__________________________*/
/************************** Собственно Dynamic Connectivity ********************************/


bool isConnected(int a, int b){
	assert(a >= 0 && b >= 0);
	return f[0].isConnected(a, b);
}

void addEdge(int a, int b){
	if (a > b)
		swap(a, b);
	int k;
	if (!edgeIndex.count(make_pair(a, b))){
		k = edges.size();
		edges.push_back(Edge(a, b));
		edgeIndex[make_pair(a, b)] = k;
	}
	else{
		k = edgeIndex[make_pair(a, b)];
		edges[k].multi++;
		return;
	}
	assert(a >= 0 && b >= 0);
	if (isConnected(a, b)){
		adjacent[a][0].insert(k);
		adjacent[b][0].insert(k);
		updateEdges(k, 0);
	}
	else{
		f[0].link(k);
	}
}
#define WHILE while
void delEdge(int a, int b){
	if (a > b)
		swap(a, b);
	int k = edgeIndex[make_pair(a, b)];
	edges[k].multi--;
	if (edges[k].multi > 0){
		return;
	}
	Edge v = edges[k];
	edgeIndex.erase(make_pair(a, b));
	int l = v.rank;
	if (adjacent[a][l].count(k)){
		adjacent[a][l].erase(k);
		adjacent[b][l].erase(k);
		updateEdges(k, l);
		return;
	}
	int z1;
	bool b1 = false;
	WHILE(l >= 0){
		f[l].cut(k);
		updateEdges(k, l);
		if (!b1){
			TreapNode *s1 = getRoot(f[l].vertexNode[a]);
			TreapNode *s2 = getRoot(f[l].vertexNode[b]);

			if (s1 -> size > s2 -> size){
                swap(s1, s2);
                swap(a, b);
			}
			vector<int> v;
			f[l].getSpanningEdges(s1, v);
			sort(v.begin(), v.end());
			v.resize(unique(v.begin(), v.end()) - v.begin());
			for (auto u : v){
				assert(edges[u].rank == l);
				assert(!f[l + 1].isConnected(edges[u].a, edges[u].b));
				assert(edges[u].a >= 0 && edges[u].b >= 0);
				f[l + 1].link(u);
				edges[u].rank++;
				updateEdges(u, l);
				updateEdges(u, l + 1);
			}
			v.clear();
			int z = f[l].getAllEdges(s1, v);
			sort(v.begin(), v.end());
			v.resize(unique(v.begin(), v.end()) - v.begin());
			for (auto u : v){
				assert(edges[u].rank == l);
				edges[u].rank++;
				assert(adjacent[edges[u].a][l].count(u));
				assert(adjacent[edges[u].b][l].count(u));
				adjacent[edges[u].a][l].erase(u);
				adjacent[edges[u].b][l].erase(u);

				assert(!adjacent[edges[u].a][l + 1].count(u));
				assert(!adjacent[edges[u].b][l + 1].count(u));
				adjacent[edges[u].a][l + 1].insert(u);
				adjacent[edges[u].b][l + 1].insert(u);

				updateEdges(u, l);
				updateEdges(u, l + 1);
			}
			if (z != -1){
				z1 = z;
				b1 = true;
			}
		}
		if (b1){
			adjacent[edges[z1].a][l].erase(z1);
			adjacent[edges[z1].b][l].erase(z1);
			if (!f[l].isConnected(edges[z1].a, edges[z1].b)){
				f[l].link(z1);
				updateEdges(z1, l);
			}
		}
		l--;
	}
}

/************************** Об этом должны думать все, чтобы не забыть ничего пересчитать ********************************/

void updateVertex(int vertex, int level) { // пересчитать всё, что зависит от вершины vertex
	assert(f[level].vertexNode[vertex] != TreapNode::null);
	f[level].vertexNode[vertex] -> calcToTop();
}

void updateEdges(int edge, int level) { // пересчитать всё, что зависит от ребра edges
	f[level].vertexNode[edges[edge].a] -> calcToTop();
	f[level].vertexNode[edges[edge].b] -> calcToTop();
	f[level].edgeNode1[edge] -> calcToTop();
	f[level].edgeNode2[edge] -> calcToTop();
}

/**________________________NAUMOV STAS CODE__________________________**/

int getint(){
	char c = 0;
	while((c = getchar()) <= 32);
	int t = 0;
	while(1) {
		t = t * 10 + c - '0';
		c = getchar();
		if(c < '0' || c > '9')
			return t;
	}
}

char getchars(){
	char c = 0;
	while((c = getchar()) <= 32);
	return c;
}


int main(){
	int n, m;
	n = getint();
	m = getint();
	for (int i = 0; i < K; i++)
		f[i].init(i);
	int count = n;
	
	cerr << n << ' ' << m << '\n';
	cerr << times << '\n';
	for (int i = 0; i < m; i++){
		if(i % 1000 == 0){
			cerr << times << ' ' << i << '\n';
		}
		char c;
		c = getchars();
		if (c == '?'){
			printf("%d\n", count);
		}
		else{
			int a, b;
			a = getint();
			b = getint();
			a--, b--;
			if (c == '+'){
				bool pred = isConnected(a, b);
				addEdge(a, b);
				if (!pred){
					count--;
				}
			}

			if (c == '-'){
				delEdge(a, b);
				bool next = isConnected(a, b);
				if (!next){
					count++;
				}
			}
		}
	}
}
