#include <vector>
#include <deque>
#include <queue>
#include <iostream>

// =============================================

/*

 [描述]
本题给定一个无向图，用邻接表作存储结构，用dfs和bfs找出图的所有连通子集。 所有顶点用0到n-1表示，假设邻接表采用头插法建立边表，非连通子集的搜索顺序为按照编号从小到大排列。


 [输入]
第1行输入2个整数n m，分别表示顶点数和边数，空格分割
后面m行，每行输入边的两个顶点编号，空格分割
输出
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
{0 11 12 9 1 5 2}{3 4}{6 10 7 8}
{0 11 5 2 1 12 9}{3 4}{6 10 8 7}
 */

// =============================================


using namespace std;

bool graph_visit_bool = 0;

void dfs(vector<pair<deque<int>, bool>>& mat, uint32_t ind, char pc = ' '){
    mat[ind].second = !graph_visit_bool;
    cout << pc << ind;
    for (int i = 0; i < mat[ind].first.size(); ++i) { // its ADJs
        if(mat[mat[ind].first[i]].second == graph_visit_bool)// got its not_found adj
            dfs(mat, mat[ind].first[i]);
    }
    if(pc == '{') {
        cout << '}';
        for (int i = 0; i < mat.size(); ++i) {
            if(mat[i].second == graph_visit_bool) {
                dfs(mat, i, '{');
                return;
            }
        }
    }
}


void dfs(vector<pair<deque<int>, bool>>& mat) {
    if(mat.size() > 0) {
        mat[0].second = !graph_visit_bool; // found
        cout << '{' << 0;
        for (int i = 0; i < mat[0].first.size(); ++i) { // its ADJs
            if (mat[mat[0].first[i]].second == graph_visit_bool)// got its not_found adj
            {
                dfs(mat, mat[0].first[i]);
            }
        }
        cout << '}';
        for (int i = 0; i < mat.size(); ++i) {
            if (mat[i].second == graph_visit_bool) {
                dfs(mat, i, '{');
                graph_visit_bool = !graph_visit_bool;
                cout << endl;
                return;
            }
        }
        graph_visit_bool = !graph_visit_bool;
        cout << endl;
    }
}

void bfs(vector<pair<deque<int>, bool>>& ad_mat, uint32_t ind = 0) {
    queue<uint32_t> queue_;
    queue_.push(ind);
    ad_mat[ind].second = !graph_visit_bool; // pushed
    cout << '{';
    uint32_t i;
    while(!queue_.empty()){
        i = queue_.front();
        queue_.pop();

        if(ind != i)
            cout << ' ';
        cout << i;

        for (int j = 0; j < ad_mat[i].first.size(); ++j) {
            if(ad_mat[ad_mat[i].first[j]].second == graph_visit_bool) {
                queue_.push(ad_mat[i].first[j]);
                ad_mat[ad_mat[i].first[j]].second = !graph_visit_bool;
            }
        }
    }
    cout << '}';
    for (int k = 0; k < ad_mat.size(); ++k) {
        if (ad_mat[k].second == graph_visit_bool) {
            bfs(ad_mat, k);
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
    int m, n;
    cin >> n >> m;
    auto mat = vector<pair<deque<int>, bool>>(n);
    for (int i = 0; i < m; ++i) {
        int t1, t2;
        cin >> t1 >> t2;
        mat[i].second = graph_visit_bool;
        mat[t1].first.push_front(t2);
        mat[t2].first.push_front(t1);
    }
    dfs(mat);
    bfs(mat);
}