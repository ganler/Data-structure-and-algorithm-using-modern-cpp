#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T = int>
struct huffman_node{
    huffman_node(T v, uint16_t f, huffman_node<T>* l, huffman_node<T>* r) : val(v), frequency(f), left(l), right(r){};
    huffman_node(huffman_node<T>* l, huffman_node<T>* r) : frequency(l->frequency+r->frequency), left(l), right(r){};
    huffman_node(T v, uint16_t f) : val(v), frequency(f), left(nullptr), right(nullptr){};
    huffman_node(T v) : val(v), left(nullptr), right(nullptr){};
    bool is_leaf(){ return (left == nullptr)&&(right == nullptr); }

    huffman_node& operator=(const huffman_node& node){
        left = node.left;
        right = node.right;
        val = node.val;
        frequency = node.frequency;
    }
    huffman_node(const huffman_node& node){
        *this = node;
    }

    T val;
    uint16_t frequency;
    huffman_node<T> *left, *right;

};

template <typename T = int>
class huffman_tree{
public:
    uint16_t weight_cal();
    void create(const vector<uint16_t >&);

    // ~huffman_tree(){ clear(root); };
private:
    void clear(huffman_node<T>*);

    huffman_node<T>* root;
};

template <typename T>
class freq_cmp{
public:
    bool operator() (const huffman_node<T>* a, const huffman_node<T>* b){
        return a->frequency > b->frequency;
    }
};

template <typename T>
void huffman_tree<T>::create(const vector<uint16_t >& vec) {
    priority_queue<huffman_node<T>*, vector<huffman_node<T>*>, freq_cmp<T>> pri_queue;

    for (int i = 0; i < vec.size(); ++i)
        pri_queue.push(new huffman_node<T>(vec[i], vec[i])); // no value version

    while(pri_queue.size() > 0){
        auto c_r = pri_queue.top();
        pri_queue.pop();

        auto c_l = pri_queue.top();
        pri_queue.pop();

        pri_queue.push(new huffman_node<T>(c_l, c_r));
    }

    root = pri_queue.top();
}

template <typename T>
uint16_t huffman_tree<T>::weight_cal() {
    // 广度优先遍历
    queue<huffman_node<T>*> queue_;
    queue<uint16_t> layer_queue;

    uint16_t weight_sum = 0;

    if(root == nullptr)
        return 0;

    auto p = root;
    uint16_t layer_now = 0;

    queue_.push(root);
    layer_queue.push(layer_now);

    while(!queue_.empty()){
        p = queue_.front(); // queue顶
        layer_now = layer_queue.front(); // 当前层

        queue_.pop();
        layer_queue.pop();

        // what to do
        if(p->is_leaf())
            weight_sum += layer_now * p->frequency;

        if(p->left) {
            queue_.push(p->left);
            layer_queue.push(layer_now+1);
        }
        if(p->right) {
            queue_.push(p->right);
            layer_queue.push(layer_now+1);
        }
    }

    return weight_sum;
}

int main(){
    uint16_t tms, tmp;

    vector<uint16_t> input_vec;

    cin >> tms;

    for (int i = 0; i < tms; ++i) {
        cin >> tmp;
        input_vec.push_back(tmp);
    }

    huffman_tree<int> h_tree;

    h_tree.create(input_vec);
    cout << h_tree.weight_cal();
}