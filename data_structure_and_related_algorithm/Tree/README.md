# 树形结构摘要

> 参考课外书：
>
> 《c++数据结构与算法》
>
> 《图解数据结构 使用c++》

> Codes List之后有一些知识点的讲解和我个人的感悟。

## Codes List

> **all_stack_binary_tree.cpp**
>
> > 全部使用栈的方法遍历。
>
> ![img](https://s1.ax1x.com/2018/11/08/iHha9A.png)



> **threaded_tree_1.cpp**
>
> ![img](https://s1.ax1x.com/2018/11/08/iHhQ6x.png)

> **threaded_tree_2.cpp**
>
> ![img](https://s1.ax1x.com/2018/11/08/iHhG7D.png)

> **huffman_btree_1.cpp**
>
> ![img](https://s1.ax1x.com/2018/11/29/FZ0dJA.png)

> **huffman_btree_2.cpp**
>
> ![img](https://s1.ax1x.com/2018/11/29/FZ00zt.png)

> **huffman_btree_3.cpp**
>
> ![img](https://s1.ax1x.com/2018/11/29/FZBy11.png)
>
> > 完整输入请看源码。

## 树的概念方面

- 树由节点组成；

- 树可以组成森林（n个互斥树的集合，其中$n\ge 0$）；

- **专有名词**：

  节点的度数：节点的子树（子节点）的个数；

  层数：根为第一层；

  高度：最大层数；

  树叶、终端节点：度数为0的节点；



## 二叉树

> 重点中的重点

### 概念

- **完全二叉树（Full binary tree）：**对于一个有n个节点的二叉树，按每层从左到右编号，如果每个节点都按从左到右的顺序对应一个1~n的序号则为完全二叉树。

  ![img](https://s1.ax1x.com/2018/10/17/idfj8e.png)

> 从第一个开始数1,2,…，要满足：对于已有的节点，都能连续排布。（即在连续存储的时候，可以利用一些性质提高访问效率）

- **满二叉树：**每一层的节点都达到最大值；（第$k$层的节点数为 $2^k-1$）
- **严格二叉树：**对于非叶子节点，都有2个子节点。
- **二叉查找树（有序二叉树）：** 左节点 < 父节点 ≤ 右节点。（"<"和"≤"可以自己定义）。

### 性质

**一般性质：**

- 层数为k的二叉树的总结点数<u>最多</u>为$2^k-1$ 。

**严格二叉树的性质：**

- 叶子数 = 非叶子节点数 + 1；（可用数学归纳法证明）

> **Exercise**
>
> 对于一个非空树，其度数为5，度数为i的节点有i个，$i\in[1, 5]$，问叶子数为多少？
>
>  节点数为：$1+\sum_{i=1}^5i^2$;
>
> 非叶子点数（子节点数大于0的节点数）：$\sum_{i=1}^5i$;
>
> 两式相减即为答案。

### 存储

- 习惯性用链表存储，也可以用数组； 

> **对于数组**
>
> ![img](https://s1.ax1x.com/2018/10/17/id5F1g.png)
>
> **对于root的编号以1开始的数组：**
>
> - 左子树的下标值 = 父子树的下标值 * 2 ；
> - 右子树的下标值 = 父子树的下标值 * 2 + 1；
> - $\log_2下标+1$ 即为层数；
>
> > 而对于以0开始的数组（以1开始计数的情况加）：
> >
> > - <u>左子树下标值 = 父节点下标值 * 2 + 1</u>
> > - <u>右子树的下标值 = 父节点的下标值 * 2 + 2</u>

> 对于链表表示法，最基本的部分应当是节点：

```c++
template<typename T>
class BST_node{
public:
    T data;
    BST_node<T> *left, *right;
    BST_node(){
        left = right = nullptr;
    }
    BST_node(const T& d){
        data = d;
        left = right = nullptr;
    }
    BST_node(const T& d, BST_node<T> *l = nullptr, BST_node<T> *r = nullptr){
        data = d;
        l = left;
        r = right;
    }
}
```

### 遍历

#### 广度优先遍历

从对底层或最高层开始，对于每一层，从左至右。

假设我们从上往下，从左到右的遍历，其中我们可以用到列队FIFO的思想：

```c++
template<typename T>
void BST<T>::bread_first(){
    queue<BST<T>*> queue_;
    auto p = root;
    
    if(p != nullptr){
        queue_.push(p); // 入队
        while(!queue_.empty()){
            p = queue_.front(); // 队头
            queue_.pop_front();
            
            cout << p->data << endl; // 对数据进行操作
            
            if(p->left != nullptr)
                queue_.push(p->left); // 左边有就左边入队
            if(p->right != nullptr)
                queue_.push(p->right); // 左边判断完后在右边
            // (即如果有左右节点，那么右节点会跟在左节点后)
        }
    }
}
```

#### 深度优先遍历

DLR的各种排列（总共6中深度优先遍历方法）。深度遍历和栈有关。

> **中序遍历：**
>
> `left` -> `data` -> `right`
>
> ![img](https://s1.ax1x.com/2018/10/17/idTl38.png)
>
> 按照这样走就不会错。

> **后序遍历**
>
> `left` -> `right`-> `data` 
>
> ![img](https://s1.ax1x.com/2018/10/17/idTyDJ.png)
>
> 这个可能看上去比第一个麻烦点，其实也简单：
>
> 对于最基础的`father & two sons`树结构，一定是`left->right->father`。每每遍历这个最简单的树结构后，我们先停在`father`，而因为是先L在R那么就是在`father`同层的基础上，从左至右的移动到右侧最近树的最底层，然后依次这样操作。

前序遍历即后续遍历左右反过来（把上面的图左右镜像转换即可）。

#### 非递归深度优先遍历

以前序为例:

> 直到站为空，对于每个节点，先visit栈顶元素，如果有右子树放右子树，再看如果有左子树放左子树。

```c++
template<typename T>
void BST<T>::visit_front(){
    BST_node<T>* p;
    if(root == nullptr)
        return;
    
    stack<BST_node<T>> stack_;
    stack_.push(root);
    
    while(!stack_.empty()){
        p = stack_.top();
        cout << p->data << ' '; // visit
        stack_.pop();
        
        if(p->right != nullptr)
            stack_.push(p->right);
        // 这里的用栈意思其实就是，我想先遍历左边的树，左边的树遍历完了，我再遍历右边的树；
        if(p->left != nullptr)
            stack_.push(p->left);
    }
}
```

中序：

```c++
template<typename T>
void BST<T>::visit_mid(){
    BST_node<T>* p;
    if(root == nullptr)
        return;
    else
        p = root;
    
    stack<BST_node<T>> stack_;
    stack_.push(root);
    
    while(p != nullptr || stack_.empty()){
        while(p != nullptr){ // 把左边的节点全部压栈
            stack_.push(p);
            p = p->left;
        }
        p = stack_.top(); // 取出栈顶的元素
        cout << p->data << ' ';
        stack_.pop();
        p = p->right; // 右移
    }
}
```

后序：

> 思路一：**Geeksforgeeks Guide:**
> 1.1 Create an empty stack
> 2.1 Do following while root is not NULL
> ​    a) Push root's right child and then root to stack.
> ​    b) Set root as root's left child.
> 2.2 Pop an item from stack and set it as root.
> ​    a) If the popped item has a right child and the right child 
> ​       is at top of stack, then remove the right child from stack,
> ​       push the root back and set root as root's right child.
> ​    b) Else print root's data and set root as NULL.
> 2.3 Repeat steps 2.1 and 2.2 while stack is not empty.

> 思路二：[y2b](https://www.youtube.com/watch?v=kcTcfOWFizA).

```c++
template<typename T>
void BST<T>::visit_back(){
	BST_node<T>* cur;
    if(root == nullptr)
        return;
	cur = root;
    BST_node<T>* pre = nullptr;
    
    stack<T> stack_;
    stack_.push(root);
    
    while(cur){
        while(cur){
            stack_.push(cur);
            cur = cur->left;
        }
        auto top_ = stack_.top();
        if(top_->right == nullptr || top_->right == pre){// 此时left已经是null了
            // 出栈，visit
            if(stack_.empty)
                return;
            pre = top_;
            stack_.pop();
            cout << top_->data << ' ';
            cur = nullptr;
        }else
            cur = top_->right;
    }
}
```



#### 遍历的应用

**计数**

```c++
template<typename T>
uint16_t BST<T>::size(){
    auto ptr = root;
    while()
}
```

### 搜索

对于搜索算法（时间复杂度为$O(n)$，当树可被退化为链表的时候，搜索算法最糟糕）：

> 由二叉查找树的性质，`*left < *right;`

```c++
template<typename T>
auto BST<T>::search(const T& val, BST_node<T>* ptr = root) noexcept const{
    while(ptr != nullptr){
        if(ptr->data == val)// 到了叶子就返回nullptr
            return ptr;
        else if(ptr->data < val)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return nullptr; // 表示没找到
}
```

其实搜索也可以试用遍历思想：

```c++
template<typename T>
auto BST<T>::search(BST_node<T>* ptr, const T& val) noexcept const{
    if(ptr->data == val)
        return prt;
    else if(ptr == nullptr)
        return nullptr;
    else if(ptr->data < val)
        return search(ptr->left);
    else
        return search(ptr->right);
}
```

易知，二叉树的查找效率和整个树的高度有关，为了保持高效率，我们最好使用平衡二叉树（对于任意子树，左子树的高度和右子树的高度差 ≤ 1）;

**[图片未上传]**

![image-20181022195928937](/Users/ganler-mac/Library/Application%20Support/typora-user-images/image-20181022195928937.png)

而平衡二叉树的高度为$log_2N$，所以其搜索效率为$O(log_2 N)$。 

### 插入

插入的时间复杂度等同于查找的时间复杂度，插入操作无非是直接<u>在树的基础上加入一个新的叶子节点</u>，那么找到对应的位置即可：

```c++
template<typename T>
void BST<T>::insert(const T& val) noexcept{
    auto ptr = root;
    while(ture){
        if(ptr->data < val){
            if(ptr->left == nullptr){
                ptr->left = new BST_node<T>(val);
                return;
            }else
                ptr = ptr->left;
        }else{
            if(ptr->right == nullptr){
                ptr->right = new BST_node<T>(val);
                return;
            }else
                ptr = ptr->right;
		}
    }
}
```

### 其他

> 限于时间和精力，这里再给出一些关于树的其他内容的纲要，可以参考别的资料。

- 树的删除
- 线索树
- Morris algorithm
- Huffman encode and Huffman tree
- 树的平衡
- 自适应树（self-adjusting tree）
- Heap
- treap树
- k-d树