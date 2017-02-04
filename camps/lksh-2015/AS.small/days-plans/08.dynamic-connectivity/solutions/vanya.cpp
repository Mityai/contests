#include <bits/stdc++.h>

using namespace std;

#define fr first
#define sc second
#define mp make_pair
#define pb push_back

const int N = 1e6;
const int K = 20;


template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
  template<typename S, typename T> struct hash<pair<S, T>>
  {
    inline size_t operator()(const pair<S, T> & v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.first);
      ::hash_combine(seed, v.second);
      return seed;
    }
  };
}

struct Node {
    enum TYPE {
        VERTEX, EDGE
    };

    Node *l, *r, *p;
    int y;
    int size;
    TYPE type;
    int id; 
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
};

void split(Node *node, Node *&l, Node *&r, int k);
Node *merge(Node *l, Node *r);  

Node *getRoot(Node *node);    
int getPos(Node *node); 


struct Forest { 
    int level;
    unordered_map<pair < int, int >, Node *> getEdge;
    vector<Node *> vertexNode; 

    void init(int n, int level);  
    void makeFirst(Node *v);       
    void cut(int v, int u);        
    void link(int v, int u);       
    bool isConnected(int v, int u);

    int getCompSize(int v);

    void getSpanningEdges(int v);

    int getAllEdges(int v);

    void getSpanningEdges(Node *root);

    int getAllEdges(Node *root);

    void updToTop(Node * v);

};

struct Edge { 
    int v, u; 
    int rank;
    Edge() { }

    Edge(int a, int b, int rank) : v(a), u(b), rank(rank) { }
};



void addEdge(int v, int u);
void delEdge(int v, int u); 
void increaseRank(int id, bool isSpanning); 

vector<vector<unordered_set<int> > > adjacent;
unordered_map<int, Edge> edges; 
unordered_map<pair<int, int>, int> edgeIndex;
vector < Forest > forest;
int edgeCur;
int answer;
int spanCounter;
int globalUse[N];
int useTmr;

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
    if (type == Node::VERTEX) 
        return !adjacent[id][level].empty();
    return 0;
}

bool Node::isHasEdge() {
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


void Forest::updToTop(Node * v) {
    for (;v != NULL; v = v->p)
        v->upd();
}


void Forest::makeFirst(Node *v) {
    Node *head = getRoot(v);
    int pos = getPos(v);
    Node *ll, *rr;
    split(head, ll, rr, pos);
    merge(rr, ll);
}


void Forest::link(int v, int u) {
    if (v > u) swap(v, u);
    Node *h1 = getRoot(vertexNode[v]);
    Node *h2 = getRoot(vertexNode[u]);
    makeFirst(vertexNode[v]);
    makeFirst(vertexNode[u]);

    int edgeId = edgeIndex[mp(v, u)];
    Node *e1 = new Node(Node::EDGE, edgeId, level);
    Node *e2 = new Node(Node::EDGE, edgeId, level);
    getEdge[mp(v, u)] = e1;
    getEdge[mp(u, v)] = e2;

    merge(merge(merge(h1, e1), h2), e2);
}


void Forest::cut(int v, int u) {
    makeFirst(vertexNode[v]);

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
    split(t4, t3, t4, pos2); 
    split(t3, t2, t3, pos1 + 1); 
    split(t2, t1, t2, pos1); 
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


vector < int > increaseT;
vector < int > increaseF;


void Forest::getSpanningEdges(Node *root) {
    spanCounter++;
    if (root == NULL) return;
    if (!root->hasEdge) return;
    if (root->isHasEdge()) {
        if (globalUse[root->id] != useTmr) {
            globalUse[root->id] = useTmr;
            increaseT.pb(root->id);
        }
    }
    getSpanningEdges(root->l);
    getSpanningEdges(root->r);
}


int Forest::getAllEdges(Node *root) {
    if (root == NULL) return -1;
    if (!root->hasVertex) return -1;
    if (root->isHasVertex()) {
        for (auto x: adjacent[root->id][root->level]) {
            if (forest[level].isConnected(edges[x].v, edges[x].u)) {
                if (globalUse[x] != useTmr) {
                    globalUse[x] = useTmr;
                    increaseF.pb(x);
                }
            }
            else
                return x;
        }
    }
    int tmp = getAllEdges(root->l);
    if (tmp != -1) return tmp;
    return getAllEdges(root->r);
}

void addEdge(int v, int u) {
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
        adjacent[v][edges[id].rank].insert(id);
        adjacent[u][edges[id].rank].insert(id);

        int level = edges[id].rank;
        forest[level].updToTop(forest[level].vertexNode[v]);
        forest[level].updToTop(forest[level].vertexNode[u]);
    }
}

void increaseRank(int id, bool isSpanning) {
    edges[id].rank++;
    if (isSpanning) {
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

        forest[level - 1].updToTop(forest[level - 1].vertexNode[v]);
        forest[level - 1].updToTop(forest[level - 1].vertexNode[u]);
        forest[level].updToTop(forest[level].vertexNode[v]);
        forest[level].updToTop(forest[level].vertexNode[u]);

    }
}

void remEdge(int id) {
    int v = edges[id].v;
    int u = edges[id].u;
    edges.erase(id);
    if (v > u) swap(v, u);
    edgeIndex.erase(mp(v, u));
}

void delEdge(int v, int u) {

    if (v > u) swap(v, u);

    int id = edgeIndex[mp(v, u)];
    
    if (forest[0].getEdge.count(mp(v, u)) == 0) {
        int level = edges[id].rank;
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
        int v = (forest[level].getCompSize(edges[id].v) < forest[level].getCompSize(edges[id].u)) ? edges[id].v : edges[id].u;

        useTmr++;
        increaseF.clear();
        increaseT.clear();
        forest[level].getSpanningEdges(getRoot(forest[level].vertexNode[v]));
        for (auto x: increaseT)
            increaseRank(x, true);


        useTmr++;
        int res = forest[level].getAllEdges(getRoot(forest[level].vertexNode[v])); 
        for (auto x: increaseF)
            increaseRank(x, false);
        if (res != -1) {
            flag = 1;

            int vv = edges[res].v;
            int uu = edges[res].u;
            int ll = edges[res].rank;
            adjacent[vv][ll].erase(res);
            adjacent[uu][ll].erase(res);
            for (int level2 = 0; level2 <= level; level2++) {
                forest[level2].link(edges[res].v, edges[res].u);
            }
            break;
        }
    }
    remEdge(id);
    answer += !flag;
}

void read() {
    int m;
    scanf("%d%d", &n, &m);
    queries.resize(m);
    for (int i = 0; i < m; i++)
        queries[i].read();
}

void  solve() {
    answer = n;
    forest.resize(K);
    for (int i = 0; i < K; i++)
        forest[i].init(n, i);

    adjacent.assign(n, vector<unordered_set <int> >(K));

    vector < int > ans;
    for (auto query: queries) {
        if (query.type == 1) 
            ans.pb(answer);
        else if (query.type == 2)
            addEdge(query.v, query.u);
        else if (query.type == 3) 
            delEdge(query.v, query.u);
    }
    for (auto x: ans)
        printf("%d\n", x);
}


int main() {
    read();
    solve();
}

