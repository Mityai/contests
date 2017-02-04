const int N = 1e6;
const int K = 20;

/************************** Treap ********************************/

struct TreapNode {
  static TreapNode* null;
  TreapNode *l, *r, *p;
  int y;
  int size; // размер поддерева
  enum TYPE {VERTEX, EDGE};
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
  }
  TreapNode( TYPE type, int i, int level ) : type(type), i(i), level(level) {
    y = rand();
    p = l = r = null;
    size = 1;
  }
};
TreapNode* TreapNode::null = new TreapNode();

void split( TreapNode* node, TreapNode* &l, TreapNode* &r, int k ); // получает node, k; возвращает l, r
TreapNode* merge( TreapNode* l, TreapNode* r );
TreapNode* getRoot( TreapNode* node ); // поднимается до корня
int positionInTreap( TreapNode* node ); // поднимается до корня, вычисляем позицию

/************************** Forest ********************************/

struct Forest { // Лес, для каждого дерева которого, храним Эйлеров Обход в treap
  int level; // индекс Forest-а: инвариант f[level].level == level
  TreapNode* vertexNode[N]; // вершине исходного графа соответствует TreapNode
  TreapNode* edgeNode1[N]; // по номеру ребра i (ориентация туда) получить вершину в Treap
  TreapNode* edgeNode2[N]; // по номеру ребра i (ориентация обратно) получить вершину в Treap
  // У i-го ребра концы: edges[i].a, edges[i].b. Ориентация туда: a -> b. Ориентация обратно: b -> a.

  void init(); // Каждое Euler Tour Tree состоит из одной TreapNode, type=VERTEX
  void makeRoot( int vertex ); // используется в cut() и link()
  void cut( int edge ); 
  void link( int edge );
  bool isConnected( int a, int b ); // "внутреннее ребро или внешнее", по-другому "в одной компоненте связности a и b, или в разных"
  // getRoot(f[i].vertexNode[vertex]) -- корень treap, в котором лежит вершина исходного графа vertex в лесе уровня i
  // getRoot(f[i].edgeNode1[edge]) -- корень treap, в котором лежит ребро исходного графа edge в лесе уровня i

  void getSpanningEdges( TreapNode* root, vector<int> &spanning_edges ); // все остовные рёбра ранга k в компоненте root (использует hasEdge)
  int getAllEdges( TreapNode* root, vector<int> &inner_edges );
  // Перебирает все НЕ остовные рёбра ранга k в компоненте root (используя hasVertex), внутренние складывает в inner_edges.
  // Выходит, когда натыкается на внешнее, возвращает номер найденного внешнего, если не нашла, то -1
};

/************************** Собственно Dynamic Connectivity ********************************/

struct Edge { // неориентированное
  int a, b; // вершины-концы
  int rank;
  int multi; // кратность ребра
};

set<int> adjacent[N][K]; // списки смежности рёбер: для каждой вершины, для каждого ранга храним все НЕ ОСТОВНЫЕ рёбра такого ранга

vector<Edge> edges; // все рёбра графа (неориентированные!)
Forest f[K]; // f[i] = остовный лес рёбер ранга 0..i
map<pair<int, int>, int> edgeIndex; // преобразователь пар вершин <a,b> в "индекс ребра"

bool isConnected( int a, int b ); // f[0].isConnected(a, b)
void addEdge( int a, int b ); // edges <- {a, b, 0}, if (!isConnected(a, b)) f[0].link(index of new edge);
void delEdge( int a, int b ); // edgeIndex -> i, if (f[0].edgeNode1[i]) { Код удаления... }
/**
Код удаления...
  k = edges[i].rank
  for (j=k..0) 
    f[j].cut(i)
  for (j=k..0) { // цикл по уровням
    root = выбрали из { f[j].root(edges[i].a), f[j].root(edges[i].b) } минимум по size
    list = f[k].getSpanningEdges(root);
    увеличить ранг всем рёбрам из list
    vector<inner_edges> store;
    outer_edge  = f[k].getAllEdges(root, store);
    if (outer_edge != -1) {
      for (z=0..j) 
        f[z].link(outer_edge)
      break;
    }
  }
*/

/************************** Об этом должны думать все, чтобы не забыть ничего пересчитать ********************************/

// Вспомогательные функции
void updateVertex( int vertex, int level ); // пересчитать всё, что зависит от вершины vertex
void increaseRank( int edge, bool isSpaning ); // пересчитать всё, что зависит от ранга
