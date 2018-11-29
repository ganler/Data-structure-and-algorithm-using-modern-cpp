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
    BST_node(char d) : data(d), left(nullptr), right(nullptr){}
};

struct Trick{
    char data;
    uint16_t layer;
    Trick(char d, uint16_t l):data(d), layer(l){}
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
    void pre_visit(){
        BST_node* p;
        if(root == nullptr)
            return;

        stack<BST_node*> stk_;
        stk_.push(root);

        while(!stk_.empty()){
            p = stk_.top();
            cout << p->data; // visit
            stk_.pop();

            if(p->right)
                stk_.push(p->right);
            if(p->left)
                stk_.push(p->left);
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
                p = p->left;
            }

            p = stk_.top();
            cout << p->data; // visit
            stk_.pop();

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
        vector<Trick> vec;

        inter_mid(vec);
        for(auto it = vec.cend()-1; it >= vec.cbegin(); it--){
            cout << setfill(' ') << setw((*it).layer*5+1) << (*it).data << endl;
        }
    }


    void mid_tra(BST_node* cur, int layer, vector<Trick>& v){ // layer是cur所在的层数
        if(cur != nullptr){
            mid_tra(cur->left, layer+1, v);
            v.push_back(Trick(cur->data, layer));
            mid_tra(cur->right, layer+1, v);
        }
    }

    void inter_mid(vector<Trick>& v){
        auto p = root;
        mid_tra(p, 0, v);
    }

private:
    BST_node* root;
    string input_string;
};

int main(){
    string input;
    cin >> input;
    BST b_tree;
    b_tree.create(input);
    b_tree.pre_visit();
    b_tree.in_visit();
    b_tree.post_visit();
    b_tree.breath_visit();
    b_tree.trick_print();
}