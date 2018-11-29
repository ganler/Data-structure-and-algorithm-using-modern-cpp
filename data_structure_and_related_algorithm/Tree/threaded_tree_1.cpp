#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

struct BST_node{
    char data;
    BST_node *left, *right;
    bool l_, r_;
    BST_node(char d) : data(d), left(nullptr), right(nullptr){
        l_ = 1;
        r_ = 1;
    }
};

struct Trick{
    BST_node* node;
    uint16_t layer;
    Trick(BST_node* d, uint16_t l):node(d), layer(l){}
};

class BST{
public:
    BST_node* pre_add(int& pos){
        ++pos;
        BST_node* tmp;
        if(pos < input_string.size())
            if(input_string[pos] == '#')
                tmp = nullptr;
            else{// 按照先序依次初始化之
                tmp = new BST_node(input_string[pos]);
                tmp->left = pre_add(pos);
                tmp->right = pre_add(pos);
            }
        else
            return nullptr;
        return tmp;
    }
    void create(const string& str){
        int pos = -1;
        input_string = str;
        root = pre_add(pos);
    }

    void pre_visit(bool flag = true){
        BST_node* p;
        if(root == nullptr)
            return;

        stack<BST_node*> stk_;
        stk_.push(root);

        while(!stk_.empty()){
            p = stk_.top();
            if(flag)
                cout << p->data; // visit
            stk_.pop();

            if(p->right) {
                stk_.push(p->right);
                p->r_ = 0;
            }
            if(p->left) {
                stk_.push(p->left);
                p->l_ = 0;
            }
        }
        cout << endl;
    }

    void in_visit(){
        BST_node* p;
        if(root == nullptr)
            return;

        p = root;
        stack<BST_node*> stk_;

        while(!stk_.empty() || p != nullptr){
            while(p){ // 尽可能的左
                stk_.push(p);
                cout << "push " << p->data << endl;
                p = p->left;
            }

            p = stk_.top();
            stk_.pop();
            cout << "pop " << endl;
            cout << p->data << endl; // visit

            p = p->right;
        }
        cout << endl;
    }

    void post_visit(){
        BST_node* cur;
        if(root == nullptr)
            return;
        cur = root;
        BST_node* pre = nullptr;
        stack<BST_node*> stk_;

        while(cur || !stk_.empty()){
            while(cur){
                stk_.push(cur);
                cur = cur->left;
            }
            auto top_ = stk_.top();
            if(top_->right == nullptr || top_->right == pre){
                stk_.pop();
                pre = top_;
                cur = nullptr;
                cout << top_->data;
            } else
                cur = top_->right;
        }
        cout << endl;
    }
    void breath_visit(){
        BST_node* p;
        if(root == nullptr)
            return;
        p = root;

        queue<BST_node*> queue_;
        queue_.push(root);

        while(!queue_.empty()){
            p = queue_.front();
            cout << p->data;
            queue_.pop();
            if(p->left)
                queue_.push(p->left);
            if(p->right)
                queue_.push(p->right);
        }
        cout << endl;
    }
    void trick_print(){
        if(layer_vec.empty()){
            inter_mid(layer_vec);
        }
        for(auto it = layer_vec.cend()-1; it >= layer_vec.cbegin(); it--){
//            char left_flag = ((*it).node->left != nullptr) ? '0' : '1';
//            char right_flag = ((*it).node->left != nullptr) ? '0' : '1';
            cout << setfill(' ') << setw(((*it).layer-1)*5 + 1) << (*it).node->data << (*it).node->l_ << (*it).node->r_ << endl;
        }
    }

    void mid_tra(BST_node* cur, int layer, vector<Trick>& v){ // layer is the layer num of cur
        if(cur != nullptr){
            mid_tra(cur->left, layer+1, v);
            v.push_back(Trick(cur, layer));
            mid_tra(cur->right, layer+1, v);
        }
    }

    void inter_mid(vector<Trick>& v){
        auto p = root;
        mid_tra(p, 1, v);
    }

    void vec_prepare(){
        inter_mid(layer_vec);
    }

    uint16_t get_node_num(){
        uint16_t i = 0;
        for(char x : input_string){
            if(x != '#')
                i++;
        }
        return i;
    }

    uint16_t get_layer_num(){
        uint16_t max_layer = 1;
        for(int i = 0; i < layer_vec.size(); i++){
            if(layer_vec[i].layer > max_layer)
                max_layer = layer_vec[i].layer;
        }
        return max_layer;
    }

    uint16_t get_leaf_num(){
        BST_node* p;
        if(root == nullptr)
            return 0;
        p = root;
        uint16_t leaf_num = 0;
        queue<BST_node*> queue_;
        queue_.push(root);

        while(!queue_.empty()){
            p = queue_.front();
            queue_.pop();
            if(p->right == nullptr && p->left == nullptr)
                leaf_num++;
            if(p->left)
                queue_.push(p->left);
            if(p->right)
                queue_.push(p->right);
        }
        return leaf_num;
    }

private:
    BST_node* root;
    string input_string;
    vector<Trick> layer_vec;
};

int main(){
    string input;
    cin >> input;
    BST b_tree;
    b_tree.create(input);
    b_tree.vec_prepare();
    b_tree.pre_visit(0);
//    cout << b_tree.get_leaf_num() << endl;
//    cout << b_tree.get_node_num() << endl;
//    cout << b_tree.get_layer_num() << endl;
//    b_tree.pre_visit();
//    b_tree.post_visit();
//    b_tree.breath_visit();
    b_tree.trick_print();
    b_tree.pre_visit();
}