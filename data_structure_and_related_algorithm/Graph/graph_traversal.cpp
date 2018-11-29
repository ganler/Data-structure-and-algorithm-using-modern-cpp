// ====
/*

 [描述]
图的遍历算法是图的连通性问题、拓扑排序和求关键路径等算法的基础。遍历图的路径有深度优先搜索dfs和广度优先搜索bfs。
本题给定一个无向图，用dfs和bfs找出图的所有连通子集。所有顶点用0到n-1表示，存储结构采用邻接矩阵表示。
假设搜索时总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。


 [输入]
第1行输入2个整数n m，分别表示顶点数和边数，空格分割
后面m行，每行输入边的两个顶点编号，空格分割

 [输出]
第1行输出dfs的结果
第2行输出bfs的结果
连通子集输出格式为{v11 v12 ...}{v21 v22 ..}... 连通子集内元素之间用空格分割，子集之间无空格,'{'和子集内第一个数字之间、'}'和子集内最后一个元素之间、子集之间均无空格

注： n<20，保证输入数据无错

 [样例输入1]
13 13
0 1
0 2
0 5
0 11
1 12
3 4
6 7
6 8
6 10
7 10
9 11
9 12
11 12

 [样例输出1]
{0 1 12 9 11 2 5}{3 4}{6 7 10 8}
{0 1 2 5 11 12 9}{3 4}{6 7 8 10}
 */
// ====

#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

template <typename T>
class Graph;

template <typename T>
struct g_node;

template <typename T=bool>
struct g_node{
    T data;
    bool visit_bool;
    g_node(){}
    g_node(T d){
        data = d;
    }
    g_node(T d, bool b):data(d), visit_bool(b){};
    g_node(Graph<T> n){
        visit_bool = n.get_graph_visit_bool();
    }
    g_node(const g_node& n){
        data = n.data;
        visit_bool = n.visit_bool;
    }
    g_node(g_node&& n){
        swap(data, n.data);
        swap(visit_bool, n.visit_bool);
    }
    g_node& operator = (const g_node& n){
        g_node copy(n);
        swap(copy, *this);
        return *this;
    }
    g_node& operator = (g_node&& n){
        swap(data, n.data);
        swap(visit_bool, n.visit_bool);
        return *this;
    }
};

template <typename T>
class Graph{
public:
    Graph();
    Graph(uint8_t){}

    void print_ad_mat();
    void print_ad_list();
    void print_vetices();
    bool get_graph_visit_bool(){return graph_visit_bool;};
    void add_node(g_node<T>);
    void dfs(uint32_t, char = ' ');
    void dfs();
    void bfs(uint32_t = 0);

private:
    vector<vector<uint16_t>> ad_mat;
    vector<g_node<T>> vertex;
    bool directed;
    bool graph_visit_bool;// for node.visit_bool == visit_bool, the node has been visited;
    bool net;

    bool has_found(uint32_t i){ return vertex[i].visit_bool != graph_visit_bool; }
};

template <typename T>
Graph<T>::Graph() {
    graph_visit_bool = 0;
    uint16_t direct = 3; // set
    directed = direct < 3;
    uint32_t m, n;
    cin >> n >> m;
    vertex = vector<g_node<T>>(n);
    ad_mat = vector<vector<uint16_t>>(n, vector<uint16_t>(n, 0));
    // auto input = new T[n];
    // string input;
    // cin >> input;
    for (int k = 0; k < n; ++k) {
        vertex[k].data = k;
        vertex[k].visit_bool = graph_visit_bool;
    }
    for (int j = 0; j < m; ++j) {
        T t1, t2;
        cin >> t1 >> t2;
        uint32_t val = 1;
        if(direct%2==0) {
            cin >> val;
            net = 1;
        } else
            net = 0;
        size_t loc[2];
        for (size_t i = 0; i < n; ++i) {
            if(t1 == i)
                loc[0] = i;
            if(t2 == i)
                loc[1] = i;
        }
        ad_mat[loc[0]][loc[1]] =val;
        if(!directed)
            ad_mat[loc[1]][loc[0]] = val;
    }
    // delete[] input;
}

template <typename T>
void Graph<T>::print_ad_mat() {
    for (int i = 0; i < vertex.size(); ++i) {
        for (int j = 0; j < vertex.size(); ++j)
            cout << setw(4) << ad_mat[i][j] << ' ';
        cout << endl;
    }
}

template <typename T>
void Graph<T>::print_vetices(){
    for (int i = 0; i < vertex.size(); ++i)
        cout << vertex[i].data << ' ';
    cout << endl;
}

template <typename T>
void Graph<T>::print_ad_list(){
    for (int i = 0; i < vertex.size(); ++i) {
        cout << vertex[i].data << "-->";
        for (int j = vertex.size()-1; j >= 0; --j) {
            if(ad_mat[i][j]) {
                cout << j;
                if(net)
                    cout << ',' << ad_mat[i][j];
                cout << ' ';
            }
        }
        cout<< endl;
    }
}

template <typename T>
void Graph<T>::dfs(uint32_t ind, char pc){
    vertex[ind].visit_bool = !graph_visit_bool; // found
    cout << pc << vertex[ind].data;
    for (int i = 0; i < ad_mat[ind].size(); ++i) { // its ADJs
        if(ad_mat[ind][i] && vertex[i].visit_bool == graph_visit_bool)// got its not_found adj
            dfs(i);
    }
    if(pc == '{') {
        cout << '}';
        for (int i = 0; i < vertex.size(); ++i) {
            if(vertex[i].visit_bool == graph_visit_bool) {
                dfs(i, '{');
                return;
            }
        }
    }
}

template <typename T>
void Graph<T>::dfs() {
    if(vertex.size() > 0) {
        vertex[0].visit_bool = !graph_visit_bool; // found
        cout << '{' << vertex[0].data;
        for (int i = 0; i < ad_mat[0].size(); ++i) { // its ADJs
            if (ad_mat[0][i] && vertex[i].visit_bool == graph_visit_bool)// got its not_found adj
                dfs(i);
        }
        cout << '}';
        for (int i = 0; i < vertex.size(); ++i) {
            if (vertex[i].visit_bool == graph_visit_bool) {
                dfs(i, '{');
                graph_visit_bool = !graph_visit_bool;
                cout << endl;
                return;
            }
        }
        graph_visit_bool = !graph_visit_bool;
        cout << endl;
    }
}

template <typename T>
void Graph<T>::bfs(uint32_t ind) {
    queue<uint32_t> queue_;
    queue_.push(ind);
    vertex[ind].visit_bool = !graph_visit_bool; // pushed
    cout << '{';
    uint32_t i;
    while(!queue_.empty()){
        i = queue_.front();
        queue_.pop();

        if(ind != i)
            cout << ' ';
        cout << vertex[i].data;

        for (int j = 0; j < vertex.size(); ++j) {
            if(ad_mat[i][j] && !has_found(j)) {
                queue_.push(j);
                vertex[j].visit_bool = !graph_visit_bool;
            }
        }
    }
    cout << '}';
    for (int k = 0; k < vertex.size(); ++k) {
        if (!has_found(k)) {
            bfs(k);
            if(ind == 0) {
                graph_visit_bool = !graph_visit_bool;
                cout << endl;
            }
            return;
        }
    }
    if(ind == 0) {
        graph_visit_bool = !graph_visit_bool;
        cout << endl;
    }
}
int main(){
    Graph<uint32_t> g;
//    g.print_vetices();
//    g.print_ad_mat();
//    g.print_ad_list();
    g.dfs();
    g.bfs();
}