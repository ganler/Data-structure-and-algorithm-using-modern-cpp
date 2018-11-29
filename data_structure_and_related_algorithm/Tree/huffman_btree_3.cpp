#include <iostream>
#include <vector>

using namespace std;

struct node{
    node* left, *right;
    char value;
    node(){
        value = 0;
        right = nullptr;
        left = nullptr;
    }

    node(const node& n){
        value = n.value;
        left = n.left;
        right = n.right;
    }
    node& operator=(const node& n){
        value = n.value;
        left = n.left;
        right = n.right;
        return *this;
    }
    void print(){ cout << value; }
};

int main(){
    int n;
    cin >> n;

    node* root = new node;

    int val;
    string input;

    for (int i = 0; i < n; ++i) {
        cin >> val >> input;
        node* p = root;
        for(auto x : input){
            bool right = (x == '1') ? (1):(0);
            if(right){
                if(p->right == nullptr)
                    p->right = new node;
                p = p->right;
            } else {
                if (p->left == nullptr)
                    p->left = new node;
                p = p->left;
            }
            p->value = static_cast<char>(val);
        }

    }


    char x;
    node* tmp = root;

    while(cin >> x){
        tmp = (x == '1') ? (tmp->right):(tmp->left);
        if(tmp->right == nullptr && tmp->left == nullptr) {
            tmp->print();
            tmp = root;
        }
    }
}

/*
23
32 111
46 010011
73 0111110
83 011110
97 1000
98 11010
99 10011
100 10110
101 0010
102 01000
104 01110
105 11011
108 1010
109 0111111
110 10010
111 000
114 0110
115 0101
116 11001
117 11000
118 010010
119 0011
121 10111
01111001110000001111110111000110000110111010001010000001110011011101000011011001010111110001001010110111100110001001010011001010001010111101110001100001101111100110001101010100010010111110001001010110111011111011100111101110101010111110100010111011111110111010111001110110100011011001010110010011111011110011100000011111101110001100001101111100110001101010100010010111110001001010110111101110001100001101110100010100000011100110111010000110110010101111001111011101010101111101000101110001101001001011011000110000101010011
 */