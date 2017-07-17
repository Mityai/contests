#include <algorithm>
#include <cstdio>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>
#include <utility>

#ifdef __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

using std::queue;
using std::set;
using std::string;
using std::vector;
using std::pair;

#if __APPLE__
    std::mt19937 rng(228);
#else
    std::mt19937 rng(228);
    // std::mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif

const int MAX_K = 16;
const int MAX_GEN_K = 6;
const int INF = 1234567890;

const char EMPTY_CELL = '.';

const double C_VALUE = 160000;

const double MAX_T = 2.0;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

double t; // time marker

template<typename T>
T sqr(const T& x) {
    return x * x;
}

struct Cell {
    int x, y;

    Cell() {
    }

    Cell(int x_, int y_) : x(x_), y(y_) {
    }

    Cell(size_t x_, size_t y_) : x(static_cast<int>(x_)), y(static_cast<int>(y_)) {
    }

    bool operator < (const Cell& oth) const {
        return x < oth.x || (x == oth.x && y < oth.y);
    }

    bool operator == (const Cell& oth) const {
        return x == oth.x && y == oth.y;
    }

    bool operator != (const Cell& oth) const {
        return !(*this == oth);
    }

    void read() {
        scanf("%d%d", &x, &y);
    }
};

void read(vector<Cell>& sources_live, vector<Cell>& sources_magic) {
    int k;
    scanf("%d", &k);

    sources_live.resize(k);
    sources_magic.resize(k);
    for (size_t i = 0; i != k; ++i) {
        sources_live[i].read();
    }
    for (size_t i = 0; i != k; ++i) {
        sources_magic[i].read();
    }
}

bool in_field(const Cell& cell, const vector<string>& field) {
    return 0 <= cell.x && cell.x < field.size() && 0 <= cell.y && cell.y < field[0].size();
}

void mark_region(const Cell& current, const vector<string>& field, vector<vector<char>>& used) {
    used[current.x][current.y] = true;
    for (size_t k = 0; k < 4; ++k) {
        Cell to = current;
        to.x += dx[k];
        to.y += dy[k];
        if (in_field(to, field)) {
            if (!used[to.x][to.y] && field[to.x][to.y] == field[current.x][current.y]) {
                mark_region(to, field, used);
            }
        }
    }
}

bool is_connected(const vector<string>& field) {
    vector<vector<char>> used(field.size(), vector<char>(field[0].size(), false));
    vector<char> region_marked(MAX_K, false);
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            if (field[i][j] == EMPTY_CELL) {
                // eprintf("Error: empty cell founded\n");
                return false;
            }
            if (!used[i][j]) {
                int region = field[i][j] - 'a';
                if (region_marked[region]) {
                    // eprintf("Error: regions are not connected\n");
                    return false;
                }
                mark_region(Cell(i, j), field, used);
                region_marked[region] = true;
            }
        }
    }
    return true;
}

void get_values_vectors(const vector<string>& field, vector<int>& area, vector<int>& perimeter) {
    area.resize(MAX_K);
    perimeter.resize(MAX_K);
    int amount_of_regions = 0;
    for (int i = 0; i < field.size(); ++i) {
        for (int j = 0; j < field[i].size(); ++j) {
            if (field[i][j] != EMPTY_CELL) {
                int region = field[i][j] - 'a';
                if (region == amount_of_regions) {
                    ++amount_of_regions;
                }
                ++area[region];
                for (size_t k = 0; k < 4; ++k) {
                    Cell current(i + dx[k], j + dy[k]);
                    if (!in_field(current, field) ||
                            field[current.x][current.y] != field[i][j]) {
                        ++perimeter[region];
                    }
                }
            }
        }
    }
    area.resize(amount_of_regions);
    perimeter.resize(amount_of_regions);
}

double get_mark_value(int area, int perimeter) {
    return static_cast<double>(area) / sqr(static_cast<double>(perimeter));
}

double get_mark(const vector<string>& field, bool bad = true) { // Assuming at least one cell belongs to one region
    if (!is_connected(field) && bad) {
        return 0;
    }
    vector<int> area;
    vector<int> perimeter;
    get_values_vectors(field, area, perimeter);
    double mark = 0;
    int regions_amount = 0;
    for (size_t region = 0; region < MAX_K; ++region) {
        if (area[region] != 0) {
            ++regions_amount;
            mark += get_mark_value(area[region], perimeter[region]);
        }
    }
    mark *= C_VALUE / regions_amount;
    return mark;
}

void print_field(const vector<string>& field) {
    eprintf("Grade value: %.2lf\n", get_mark(field));
    for (const string& row : field) {
        puts(row.c_str());
    }
}

int factorial(int n) {
    int value = 1;
    for (int i = 2; i <= n; ++i) {
        value *= i;
    }
    return value;
}

vector<size_t> get_indexes(size_t n) {
    vector<size_t> indexes(n);
    for (size_t i = 0; i < n; ++i) {
        indexes[i] = i;
    }
    return indexes;
}

vector<size_t> get_random_permutation(size_t n) {
    vector<size_t> permutation(get_indexes(n));
    shuffle(permutation.begin(), permutation.end(), rng);
    return permutation;
}

bool paint(const Cell& start, const Cell& end, char color, vector<string>& field) {
    size_t n = field.size();
    size_t m = field[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INF));
    vector<vector<Cell>> parent(n, vector<Cell>(m));
    queue<Cell> q;

    distance[start.x][start.y] = 0;
    q.push(start);

    while (!q.empty()) {
        Cell v = q.front();
        q.pop();

        if (v == end) {
            break;
        }

        for (size_t k = 0; k < 4; ++k) {
            Cell new_v(v.x + dx[k], v.y + dy[k]);
            if (in_field(new_v, field) && (field[new_v.x][new_v.y] == EMPTY_CELL || new_v == end)) {
                if (distance[new_v.x][new_v.y] > distance[v.x][v.y] + 1) {
                    distance[new_v.x][new_v.y] = distance[v.x][v.y] + 1;
                    parent[new_v.x][new_v.y] = v;
                    q.push(new_v);
                }
            }
        }
    }

    if (distance[end.x][end.y] != INF) {
        Cell current = end;
        while (current != start) {
            field[current.x][current.y] = color;
            current = parent[current.x][current.y];
        }
        field[start.x][start.y] = color;
        return true;
    }
    return false;
}

vector<string> build_field(int n,
                           int m,
                           const vector<Cell>& sources_live,
                           const vector<Cell>& sources_magic) {
    int regions_amount = sources_live.size();
    vector<string> field(n, string(m, EMPTY_CELL));
    for (size_t i = 0; i < regions_amount; ++i) {
        const Cell& live = sources_live[i];
        const Cell& magic = sources_magic[i];
        field[live.x][live.y] = char('a' + i);
        field[magic.x][magic.y] = char('a' + i);
    }

    bool ok;
    int cnt = 0;
    auto tmp_field = field;
    do {
        ok = true;
        field = tmp_field;
        vector<size_t> order = get_random_permutation(static_cast<size_t>(regions_amount));
        for (size_t i = 0; i < regions_amount; ++i) {
            const Cell& live = sources_live[order[i]];
            const Cell& magic = sources_magic[order[i]];
            if (!paint(live, magic, field[live.x][live.y], field)) {
                ok = false;
                break;
            }
        }
        if (++cnt == 10 && !ok) {
            return field;
        }
    } while (!ok);

    bool changed;
    do {
        changed = false;
        set<pair<Cell, int>> tosee;
        for (int i = 0; i < field.size(); ++i) {
            for (int j = 0; j < field[i].size(); ++j) {
                if (field[i][j] != EMPTY_CELL) {
                    size_t region = field[i][j] - 'a';
                    for (size_t k = 0; k < 4; ++k) {
                        Cell current(i + dx[k], j + dy[k]);
                        if (in_field(current, field) &&
                                field[current.x][current.y] == EMPTY_CELL) {
                            tosee.insert({current, region});
                        }
                    }
                }
            }
        }
        vector<pair<int, pair<Cell, int>>> cells;
        for (const pair<Cell, int>& pole : tosee) {
            field[pole.first.x][pole.first.y] = char('a' + pole.second);
            cells.push_back({get_mark(field, false), pole});
            field[pole.first.x][pole.first.y] = EMPTY_CELL;
        }
        sort(cells.rbegin(), cells.rend());
        for (const auto& pole : cells) {
            const Cell& cell = pole.second.first;
            char color = char('a' + pole.second.second);
            if (field[cell.x][cell.y] == EMPTY_CELL) {
                field[cell.x][cell.y] = color;
                changed = true;
            }
        }
    } while (changed);

    return field;
}

bool is_time_limit() {
    return (clock() - t) > (MAX_T - 0.1) * CLOCKS_PER_SEC;
}

vector<string> calculate(int n,
                         int m,
                         const vector<Cell>& sources_live,
                         const vector<Cell>& sources_magic) {
    size_t sources_amount = sources_live.size();
    int gens_amount = factorial(MAX_GEN_K);
    vector<size_t> index_map = get_indexes(sources_amount);
    set<vector<size_t>> was_map;
    double best_mark = -1;
    vector<string> best_field;
    for (int iteration = 0; iteration < gens_amount && !is_time_limit(); ++iteration) {
        if (sources_amount <= MAX_GEN_K) {
            next_permutation(index_map.begin(), index_map.end());
        } else {
            do {
                shuffle(index_map.begin(), index_map.end(), rng);
            } while (was_map.find(index_map) != was_map.end());
            was_map.insert(index_map);
        }

        vector<Cell> sources_magic_permutation(sources_amount);
        for (size_t i = 0; i < sources_amount; ++i) {
            sources_magic_permutation[i] = sources_magic[index_map[i]];
        }

        vector<string> field = build_field(n, m, sources_live, sources_magic_permutation);
        double mark = get_mark(field);
        if (best_mark < mark) {
            best_mark = mark;
            best_field = field;
        }
    }
    return best_field;
}

int main() {
#if __APPLE__
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    double max_t = 0;
    double count_test = 0;
    double error = 0;
    int zero = 0;
    while (scanf("%d%d", &n, &m) == 2) {
        t = clock();

        vector<Cell> sources_live;
        vector<Cell> sources_magic;
        read(sources_live, sources_magic);
        vector<string> field_ans = calculate(n, m, sources_live, sources_magic);
        print_field(field_ans);

        max_t = std::max(max_t, (clock() - t) / CLOCKS_PER_SEC);
        ++count_test;
        if (count_test == 20 || count_test == 60) {
            eprintf("-----------\n");
        }
        double mark = get_mark(field_ans);
        if (mark == 0) ++zero;
        error += mark;
    }

    eprintf("average mark: %.4lf\n", error / count_test);
    eprintf("zero marks:   %.2lf%%\n", zero / count_test * 100);
    eprintf("max time:     %.4lf\n", max_t);
}
