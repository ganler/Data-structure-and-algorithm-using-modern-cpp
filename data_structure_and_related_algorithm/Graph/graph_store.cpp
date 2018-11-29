#include <vector>
#include <iostream>
#include <iomanip>

// ======================
/*
[描述]
图是一种描述多对多关系的数据结构, 图中的数据元素称作顶点，具有关系的两个顶点形成的一个二元组称作边或弧，顶点的集合V和关系的集合R构成了图，记作G=（V,R）。
图又分成有向图，无向图，有向网，无向网。图的常用存储结构有邻接矩阵、邻接表、十字链表、邻接多重表。
图的基本操作包括图的创建、销毁、添加顶点、删除顶点、插入边、删除边、图的遍历。
本题练习邻接矩阵和邻接表的创建。

[输入]
第1行输入一个数字1~4，1为有向图,2为有向网,3为无向图,4为无向网;
第2行输入2个整数n m，分别表示顶点数和边数，空格分割
第3行为n个字符的序列，一个字符表示一个顶点
后面m行，若前面选择的是图，则每行输入边的两个顶点字符，空格分割，若是网，则每行输入弧的两个顶点字符和弧的权值，空格分割

 [输出]
第1行输出顶点向量，顶点字符以一个空格分割
接着n行n列，输出邻接矩阵，每个数字占4位
接着n行，输出邻接表

 [样例输入1]
1
4 4
abcd
a b
a c
c d
d a

 [样例输出1]
a b c d
   0   1   1   0
   0   0   0   0
   0   0   0   1
   1   0   0   0
a-->2 1
b-->
c-->3
d-->0

 [样例输入2]
2
6 10
123456
1 2 5
1 4 7
2 3 4
3 1 8
3 6 9
4 3 5
4 6 6
5 4 5
6 1 3
6 5 1

 [样例输出2]
1 2 3 4 5 6
   0   5   0   7   0   0
   0   0   4   0   0   0
   8   0   0   0   0   9
   0   0   5   0   0   6
   0   0   0   5   0   0
   3   0   0   0   1   0
1-->3,7 1,5
2-->2,4
3-->5,9 0,8
4-->5,6 2,5
5-->3,5
6-->4,1 0,3
 */
// ======================




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
        data = n.data;
        visit_bool = n.visit_bool;
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

private:
    vector<vector<uint16_t>> ad_mat;
    vector<g_node<T>> vertex;
    bool directed;
    bool graph_visit_bool;// for node.visit_bool == visit_bool, the node has been visited;
    bool net;
};

template <typename T>
Graph<T>::Graph() {
    uint16_t direct;
    cin >> direct;
    directed = direct < 3;
    uint32_t m, n;
    cin >> n >> m;
    vertex = vector<g_node<T>>(n);
    ad_mat = vector<vector<uint16_t>>(n, vector<uint16_t>(n));
    // auto input = new T[n];
    string input;
    cin >> input;
    for (int j = 0; j < m; ++j) {
        vertex[j].data = input[j];
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
            if(t1 == input[i])
                loc[0] = i;
            if(t2 == input[i])
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

int main(){
    Graph<char> g;
    g.print_vetices();
    g.print_ad_mat();
    g.print_ad_list();
}