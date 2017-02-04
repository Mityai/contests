#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

using namespace std;

#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define epr(...) fprintf(stderr, __VA_ARGS__)
#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";

#define equal equalll
#define less lesss
const int K = 20;

/************************** Treap ********************************/

struct Node {
    enum TYPE {
        VERTEX, EDGE
    };

    Node *l, *r, *p;
    int y;
    int size;
    TYPE type;
    int id; // 0..n-1 -- индекс вершины или ребра
    int level;
    bool hasVertex;
    bool hasEdge;

    Node(TYPE type, int id, int level) : type(type), id(id), level(level), hasVertex(0), hasEdge(0) {
        y = rand();
        p = l = r = NULL;
        size = 1;
    }

    bool isHasVertex();

    bool isHasEdge();

    void upd(); 

    void updStrong();
};

struct Query {
    int type, v, u;
    Query() { }
    Query(int type, int v, int u): type(type), v(v), u(u) { }

    void read() {
        char ch;
        scanf(" %c", &ch);
        assert(ch == '?' || ch == '+' || ch == '-');
        if (ch == '?') {
            v = u = -1;
            type = 1;
        }
        else {
            if (ch == '+')
                type = 2;
            else
                type = 3;
            scanf("%d%d", &v, &u);
            v--;
            u--;
        }
    }
    void Epr() {
        if (type == 1)
            cerr << "?\n";
        else
            cerr << ((type == 2)? "+": "-") << " " << v << " " << u << endl;
    }
};


void print(Node * v, int tab = 0) {
    if (v == NULL) return;
    if (tab == 0) cerr << "=========================\n";
    print(v->r, tab + 1);
    for (int i = 0; i < tab; i++)
        cerr << "\t";
    cerr << v->id << " " << v->type << " " << v->hasEdge << " " << v->hasVertex << endl;
    print(v->l, tab + 1);
    if (tab == 0) cerr << "=========================\n";
}

void split(Node *node, Node *&l, Node *&r, int k); // + получает node, k; возвращает l, r
Node *merge(Node *l, Node *r);                     // +

Node *getRoot(Node *node);                         // + поднимается до корня
int getPos(Node *node);                            // + поднимается до корня, вычисляем позицию

/************************** Forest ********************************/

struct Forest { // Лес, для каждого дерева которого, храним Эйлеров Обход в treap
    int level; // индекс Forest-а: инвариант f[level].level == level
    map<pair < int, int >, Node *> getEdge;
    vector<Node *> vertexNode; // вершине исходного графа соответствует Node
    // У i-го ребра концы: edges[i].a, edges[i].b. Ориентация туда: a -> b. Ориентация обратно: b -> a.

    void init(int n, int level);   // Каждое Euler Tour Tree состоит из одной Node, type=VERTEX
    void makeFirst(Node *v);       // +
    void cut(int v, int u);        // +
    void link(int v, int u);       // +
    bool isConnected(int v, int u);

    int getCompSize(int v);

    void getSpanningEdges(int v, set<int> &);

    int getAllEdges(int v, set <int> &);

    void getSpanningEdges(Node *root, set<int> &spanning_edges);

    int getAllEdges(Node *root, set <int> &inner_edges);

    void updToTop(Node * v);

    void checkHasEdge(); 
};

/************************** Собственно Dynamic Connectivity ********************************/

struct Edge { // неориентированное
    int v, u; // вершины-концы
    int rank;
    Edge() { assert(false); }

    Edge(int a, int b, int rank) : v(a), u(b), rank(rank) { }
};



void addEdge(int v, int u); // edges <- {a, b, 0}, if (!isConnected(a, b)) f[0].link(index of new edge);
void delEdge(int v, int u); // edgeIndex -> i, if (f[0].edgeNode1[i]) { Код удаления... }
void increaseRank(int edge, bool isSpanning); // пересчитать всё, что зависит от ранга


vector<vector<set<int> > > adjacent; // списки смежности рёбер: для каждой вершины, для каждого ранга храним все НЕ ОСТОВНЫЕ рёбра такого ранга
map<int, Edge> edges; // все рёбра графа (неориентированные!)
map<pair<int, int>, int> edgeIndex; // преобразователь пар вершин <a,b> в "индекс ребра"
vector < Forest > forest;
int edgeCur;
int answer;
bool DEBUG_INFO = 0;
int spanCounter;

int n;
vector<Query> queries;



int getSize(Node *v) {
    return (v == NULL) ? 0 : v->size;
}


bool getHasVertex(Node *v) {
    return (v == NULL) ? false : v->hasVertex;
}

bool getHasEdge(Node *v) {
    return (v == NULL) ? false : v->hasEdge;
}

bool Node::isHasVertex() {
    if (type == Node::VERTEX) {
        return !adjacent[id][level].empty();

    }
    return 0;
}

bool Node::isHasEdge() {
    //db(id);
    if (type == Node::EDGE)
        return edges[id].rank == level;
    return 0;
}

void Node::upd() {
    size = getSize(l) + getSize(r) + 1;
    hasVertex = getHasVertex(l) || getHasVertex(r) || isHasVertex();
    hasEdge = getHasEdge(l) || getHasEdge(r) || isHasEdge();
    if (l != NULL) l->p = this;
    if (r != NULL) r->p = this;
}

void Node::updStrong() {
    assert(size == getSize(l) + getSize(r) + 1);
    assert(hasVertex == getHasVertex(l) || getHasVertex(r) || isHasVertex());
    //db2(hasEdge, (getHasEdge(l) || getHasEdge(r) || isHasEdge()));
    assert(hasEdge == getHasEdge(l) || getHasEdge(r) || isHasEdge());
}


Node *merge(Node *l, Node *r) {
    if (l == NULL) return r;
    if (r == NULL) return l;
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->upd();
        return l;
    }
    else {
        r->l = merge(l, r->l);
        r->upd();
        return r;
    }

}

void split(Node *v, Node *&l, Node *&r, int size) {
    //db(v);
    if (v == NULL) {
        l = r = NULL;
        return;
    }
    if (getSize(v->l) >= size) {
        split(v->l, l, v->l, size);
        v->upd();
        r = v;
        r->p = NULL;
    }
    else {
        split(v->r, v->r, r, size - getSize(v->l) - 1);
        v->upd();
        l = v;
        l->p = NULL;
    }
}


Node *getRoot(Node *v) {
    for (; v->p != NULL; v = v->p);
    return v;
}

int getPos(Node *v) {
    int sum = getSize(v->l);
    for (; v->p != NULL; v = v->p)
        if (v->p->r == v) {
            sum += getSize(v->p->l) + 1;
        }
    return sum;
}


/************************** Forest ********************************/

void Forest::updToTop(Node * v) {
    for (;v != NULL; v = v->p)
        v->upd();
}


void Forest::makeFirst(Node *v) {
    Node *head = getRoot(v);
    int pos = getPos(v);
    Node *ll, *rr;
    split(head, ll, rr, pos);
    //db(getCompSize(rr));
    merge(rr, ll);
}


void Forest::link(int v, int u) {
    if (v > u) swap(v, u);
    //cerr << "\t\tlink v u level : " << v << " " << u << "            " << level << endl;
    //db2(v, u);
    Node *h1 = getRoot(vertexNode[v]);
    Node *h2 = getRoot(vertexNode[u]);
    //db2(h1, h2);
    assert(h1 != h2);
    //db(vertexNode.size());
    makeFirst(vertexNode[v]);
    makeFirst(vertexNode[u]);
    //db("here8");

    assert(getEdge.count(mp(v, u)) == 0);
    assert(getEdge.count(mp(u, v)) == 0);
    assert(edgeIndex.count(mp(v, u)) == 1);
    int edgeId = edgeIndex[mp(v, u)];
    Node *e1 = new Node(Node::EDGE, edgeId, level);
    Node *e2 = new Node(Node::EDGE, edgeId, level);
    getEdge[mp(v, u)] = e1;
    getEdge[mp(u, v)] = e2;

    //db("here99");
    merge(merge(merge(h1, e1), h2), e2);
    //db("here");
}


void Forest::cut(int v, int u) {
    //cerr << "\t\tcut v u : " << v << " " << u << "\t\tlevel: " << level << endl;
    //cerr << edgeIndex[mp(v, u)] << endl;
    makeFirst(vertexNode[v]);

    assert(getEdge.count(mp(v, u)) == 1);
    assert(getEdge.count(mp(u, v)) == 1);

    Node *e1 = getEdge[mp(v, u)];
    Node *e2 = getEdge[mp(u, v)];

    getEdge.erase(mp(v, u));
    getEdge.erase(mp(u, v));

    int pos1 = getPos(e1);
    int pos2 = getPos(e2);
    if (pos1 > pos2) swap(pos1, pos2);

    Node *t1, *t2, *t3, *t4, *t5;
    Node *head = getRoot(vertexNode[v]);
    split(head, t4, t5, pos2 + 1);
    split(t4, t3, t4, pos2); // t4 == e2
    split(t3, t2, t3, pos1 + 1); // t3 = new tree
    split(t2, t1, t2, pos1); // t2 == e1
    merge(t1, t5);
}

int Forest::getCompSize(int v) {
    return getRoot(vertexNode[v])->size;
}

void Forest::init(int n, int _level) {
    vertexNode.clear();
    getEdge.clear();
    level = _level;
    for (int i = 0; i < n; i++)
        vertexNode.pb(new Node(Node::VERTEX, i, level));
}

bool Forest::isConnected(int v, int u) {
    Node *h1 = getRoot(vertexNode[v]);
    Node *h2 = getRoot(vertexNode[u]);
    return h1 == h2;
}


void Forest::getSpanningEdges(int v, set<int> &ans) {
    assert(ans.empty());
    getSpanningEdges(getRoot(vertexNode[v]), ans);
}

int Forest::getAllEdges(int v, set <int> &ans) {
    assert(ans.empty());
    return getAllEdges(getRoot(vertexNode[v]), ans);
}


void Forest::getSpanningEdges(Node *root, set <int> &spanning_edges) {
    spanCounter++;
    if (root == NULL) return;
    if (!root->hasEdge) return;
    if (root->isHasEdge()) {
        spanning_edges.insert(root->id);
    }
    getSpanningEdges(root->l, spanning_edges);
    getSpanningEdges(root->r, spanning_edges);
}


int Forest::getAllEdges(Node *root, set <int> &inner_edges) {
    if (root == NULL) return -1;
    if (!root->hasVertex) return -1;
    if (root->isHasVertex()) {
        for (auto x: adjacent[root->id][root->level]) {
            if (forest[level].isConnected(edges[x].v, edges[x].u))
                inner_edges.insert(x);
            else
                return x;
        }
    }
    int tmp = getAllEdges(root->l, inner_edges);
    if (tmp != -1) return tmp;
    return getAllEdges(root->r, inner_edges);
}

void checkAll(Node * v) {
    if (v == NULL) return;
    v->updStrong();
    checkAll(v->l);
    checkAll(v->r);
}


void Forest::checkHasEdge() {
    assert(false);
    set < Node * > q;
    for (int i = 0; i < n; i++) {
        //db(i);
        //checkAll(getRoot(vertexNode[i]));
        q.insert(getRoot(vertexNode[i]));
    }
    
    //db(q.size());

    for (auto v: q)
        checkAll(v);
}




/************************** Собственно Dynamic Connectivity ********************************/


void addEdge(int v, int u) {
    //if (DEBUG_INFO)
        //cerr << "addEdge v u: " << v << " " << u << endl;
    if (v > u) swap(v, u);

    if (edgeIndex.count(mp(v, u)) == 0) {
        edges.insert(mp(edgeCur, Edge(v, u, 0)));
        edgeIndex[mp(v, u)] = edgeCur;
        edgeCur++;
    }
    int id = edgeIndex[mp(v, u)];
    if (!forest[0].isConnected(v, u)) {
        forest[0].link(v, u);
        answer--;
    }
    else {
        assert(adjacent[v][edges[id].rank].count(id) == 0);
            //db2(v, u);
        adjacent[v][edges[id].rank].insert(id);
        adjacent[u][edges[id].rank].insert(id);

        int level = edges[id].rank;
        forest[level].updToTop(forest[level].vertexNode[v]);
        forest[level].updToTop(forest[level].vertexNode[u]);
    }
    //db("here");
}

void increaseRank(int id, bool isSpanning) {
    //db(id);
    edges[id].rank++;
    if (isSpanning) {
        assert(edges.count(id) == 1);
        int level = edges[id].rank;
        int v = edges[id].v;
        int u = edges[id].u;
        forest[level - 1].updToTop(forest[level - 1].getEdge[mp(v, u)]);
        forest[level - 1].updToTop(forest[level - 1].getEdge[mp(u, v)]);
        forest[level].link(v, u);
    }
    else {
        int level = edges[id].rank;
        int v = edges[id].v;
        int u = edges[id].u;
        adjacent[v][level - 1].erase(id);
        adjacent[u][level - 1].erase(id);
        adjacent[v][level].insert(id);
        adjacent[u][level].insert(id);

        //db2(v, u);
        //print(getRoot(forest[level].vertexNode[v]));

        forest[level - 1].updToTop(forest[level - 1].vertexNode[v]);
        forest[level - 1].updToTop(forest[level - 1].vertexNode[u]);
        forest[level].updToTop(forest[level].vertexNode[v]);
        forest[level].updToTop(forest[level].vertexNode[u]);

        //print(getRoot(forest[level].vertexNode[v]));

    }
    //db2("increase rank", edges[id].rank);
}



void remEdge(int id) {
    int v = edges[id].v;
    int u = edges[id].u;
    assert(edges.count(id) == 1);
    edges.erase(id);
    if (v > u) swap(v, u);
    assert(edgeIndex.count(mp(v, u)) == 1);
    edgeIndex.erase(mp(v, u));
}

void delEdge(int v, int u) {
    //if (DEBUG_INFO)
    //cerr << "===============delEdge v u: " << v << " " << u << endl;

    if (v > u) swap(v, u);

    assert(edgeIndex.count(mp(v, u)) == 1);
    int id = edgeIndex[mp(v, u)];
    
    if (forest[0].getEdge.count(mp(v, u)) == 0) {
        int level = edges[id].rank;
        assert(adjacent[v][level].count(id) == 1);
        assert(adjacent[u][level].count(id) == 1);
        adjacent[v][level].erase(id);
        adjacent[u][level].erase(id);
    
        forest[level].updToTop(forest[level].vertexNode[v]);
        forest[level].updToTop(forest[level].vertexNode[u]);
 
        remEdge(id);
        return;
    }
    
    for (int level = edges[id].rank; level >= 0; level--)
        forest[level].cut(edges[id].v, edges[id].u);

    bool flag = 0;
    for (int level = edges[id].rank; level >= 0; level--) {
        //db(level);
        int v = (forest[level].getCompSize(edges[id].v) < forest[level].getCompSize(edges[id].u)) ? edges[id].v : edges[id].u;

        //db2(edges[id].v, edges[id].u);
        //print(getRoot(forest[level].vertexNode[edges[id].v]));
        //print(getRoot(forest[level].vertexNode[edges[id].u]));

        //db(forest[level].getCompSize(edges[id].v));
        //db(forest[level].getCompSize(edges[id].u));
        //db(v);

        set <int> goUp1;
        spanCounter = 0;
        forest[level].getSpanningEdges(v, goUp1);
        //db(spanCounter);

        //forest[level].checkHasEdge();

        for (auto x: goUp1) {
            increaseRank(x, true);
        }
        set < int > goUp2;
        int res = forest[level].getAllEdges(v, goUp2);
        
        for (auto x: goUp2) {
            increaseRank(x, false);
        }
        //db2(goUp1.size(), goUp2.size());
        if (res != -1) {
            flag = 1;

            int vv = edges[res].v;
            int uu = edges[res].u;
            int ll = edges[res].rank;
            assert(adjacent[vv][ll].count(res) == 1);
            assert(adjacent[uu][ll].count(res) == 1);
            adjacent[vv][ll].erase(res);
            adjacent[uu][ll].erase(res);

            //db("\tbefore for");
            for (int level2 = 0; level2 <= level; level2++) {
                //db(res);
                //db2(edges[res].v, edges[res].u);
                //db("call Link");
                forest[level2].link(edges[res].v, edges[res].u);
            }
            //db("\tafter for");
            break;
        }
    }
    remEdge(id);
    if (!flag)
        answer++;
}



void read() {
    int m;
    scanf("%d%d", &n, &m);
    //db2(n, m);
    queries.resize(m);
    for (int i = 0; i < m; i++)
        queries[i].read();

    //db2(n, m);
    //for (auto x: queries)
        //cerr << x.type << " " << x.v << " " << x.u << endl;

}

vector < int > p;
vector < vector < int > > e;
vector < int > use;
int cnt;


void dfs(int v) {
    use[v] = 1; 
    cnt++;
    for (auto u: e[v])
        if (!use[u])
            dfs(u);
}


void checkLevel() {
    for (int level = 0; level < K; level++) {
        int maxComp = max(1, n >> level);
        e.clear(); 
        e.resize(n);
        //db2(level, forest[level].getEdge.size());
        for (auto x: forest[level].getEdge) {
            int v = x.fr.fr;
            int u = x.fr.sc;
            e[v].pb(u);
            e[u].pb(v);
        }
        use.clear(); 
        use.assign(n, 0);
        int mx = 0;
        for (int i = 0; i < n; i++)
            if (!use[i]) {
                cnt = 0; 
                dfs(i);
                mx = max(mx, cnt);
            }
        db2(mx, maxComp);
        if (mx == 1)
            break;
        assert(mx <= maxComp);
    }

}

vector < int > solve() {
    //db2(Node::VERTEX, Node::EDGE);

    edges.clear();
    edgeIndex.clear();
    adjacent.clear();
    edgeCur = 0;
    answer = n;
    forest.clear();
    forest.resize(K);
    for (int i = 0; i < K; i++)
        forest[i].init(n, i);

    adjacent.assign(n, vector<set<int> >(K));

    vector < int > ans;
    //int it = 0;
    for (auto query: queries) {
        //if (it == 140000) {
            //DEBUG_INFO = 1;
        //}

        ////checkLevel();
        //if (it % 1000 == 0)
            //cerr << it << endl;
        //if (it > 140000)
            //checkLevel();
        //it++;
        
        //if (edges.count(0) >= 1)
            //db(edges[0].rank);
        //db(query.type);
        //query.Epr();

        //for (int i = 0; i < K; i++)
            //forest[i].checkHasEdge();
        if (query.type == 1) {
            ans.pb(answer);
            //cerr << "printAns\n";
        }
        else if (query.type == 2)
            addEdge(query.v, query.u);
        else if (query.type == 3) 
            delEdge(query.v, query.u);
        else
            assert(false);
    }
    return ans;
}

void printAns(vector < int > ans) {
    for (auto x: ans)
        printf("%d\n", x);
    //printf("\n");
}


void genTest() {
    n = 10;
    int m = 200;
    queries.clear();
    multiset < pair < int, int > > q;
    queries.clear();
    for (;(int)queries.size() < m;) {
        int key = rand() % 3;
        if (key == 0)
            queries.pb(Query(1, -1, -1));
        if (key == 1) {
            if (q.size() == 0) continue;
            int id = rand() % q.size();
            auto it = q.begin();
            for (int i = 0; i < id; i++)
                it++;
            queries.pb(Query(3, it->fr, it->sc));
            q.erase(it);
        }
        if (key == 2) {
            int v = rand() % n;
            int u = rand() % n;
            if (v == u) v = (v + 1) % n;
            if (v > u) swap(v, u);
            if (q.count(mp(v, u)) == 1)
                continue;
            q.insert(mp(v, u));
            queries.pb(Query(2, v, u));
        }
    }
    //db(q.size());
    assert((int)queries.size() == m);
}




int getId(int v) {
    return (p[v] == v) ? v: p[v] = getId(p[v]);
}

vector < int > stupid() {
    multiset < pair < int, int > > q;
    vector < int > ans;
    //db(q.size());
    for (auto x: queries) {
        if (x.type == 1) {
            p.assign(n, -1);
            for (int i = 0; i < n; i++)
                p[i] = i;
            for (auto x: q) {
                int v = getId(p[x.fr]);
                int u = getId(p[x.sc]);
                p[v] = u;
            }
            int cnt = 0;
            for (int i = 0; i < n; i++)
                cnt += p[i] == i;
            ans.pb(cnt);
        }
        if (x.type == 2) {
            int v = x.v;
            int u = x.u;
            if (v > u) swap(v, u);
            q.insert(mp(v, u));
        }
        if (x.type == 3) {
            int v = x.v;
            int u = x.u;
            if (v > u) swap(v, u);
            //db(q.size());
            //for (auto x: q)
                //cerr << x.fr << " " << x.sc << endl;
            
            assert(q.count(mp(v, u)) >= 1);

            q.erase(q.find(mp(v, u)));
        }
    }
    //db(q.size());
    return ans;
}

void printTest() {
    cerr << n << " " << queries.size() << endl;
    for (auto x: queries) {
        if (x.type == 1)
            cerr << "?\n";
        else {
            if (x.type == 2)
                cerr << "+ ";
            else
                cerr << "- ";
            cerr << x.v + 1 << " " << x.u + 1 << endl;
        }
    }

}

void stress() {
    for (int tt = 0; ; tt++) {
        cerr << "????????????????   test id: " << tt << endl;
        genTest();
        //printTest();
        auto r1 = solve();
        auto r2 = stupid();
        if (r1 != r2) {
            printTest();
            for (auto x: r1)
                cerr << x << " ";
            cerr << endl;
            for (auto x: r2)
                cerr << x << " ";
            cerr << endl;
        }
        assert(r1 == r2);
    }
}

int main() {
#ifdef DEBUG
    freopen("in", "r", stdin);
#endif
    //freopen("16", "r", stdin);
    //srand(100);
    if (1) {
        int k = 1;
        for (int tt = 0; tt < k; tt++) {
            read();
            printAns(solve());
            //cerr << endl;
            //printAns(stupid());
            //solve1();
        }
    }
    else {
        stress();
    }

    return 0;
}

