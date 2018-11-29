#include <iostream>
#include <vector>

using namespace std;

struct node{
    int weight;
    node* left;
    node* right;
    int father;

    int huff;
    node():weight(0), left(nullptr), right(nullptr), huff(0){}
};

void print(node n, vector<node>& vec){
    if(n.father != 0)
        print(vec[n.father], vec);
    if(n.father != 0)
        cout << n.huff;
    return;
}

int main(){
    int n;
    cin >> n;
    auto huff_tree = vector<node>(n+1);

    int w, p, r;
    int i = 1;
    while(cin >> w >> p >> r && r != 2){
        huff_tree[i].weight = w;
        huff_tree[i].huff = r;
        huff_tree[i].father = p;
        if(r == 0)
            huff_tree[p].left = &(huff_tree[i]);
        else
            huff_tree[p].right = &(huff_tree[i]);
        i++;
    }

    for (int j = 1; j < n+1; ++j) {
        int tmp = j;
        cout << tmp << ' ';
        print(huff_tree[j], huff_tree);
        cout << endl;
    }
}