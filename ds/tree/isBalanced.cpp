/*
    检查一棵树是否为平衡二叉树
*/

struct Bitree {
    char data;
    Bitree *lchild, *rchild;
};

#include <iostream>

int abs (int x) { return x > 0 ? x : -x; }

// version 1 : more avaliable
bool isBalanced(Bitree* root, int& height) {
    if (!root) {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;
    bool leftBalanced = isBalanced(root->lchild, leftHeight);
    bool rightBalanced = isBalanced(root->rchild, rightHeight);

    height = std::max(leftHeight, rightHeight) + 1;

    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}

bool checkBalance(Bitree* root) {
    int height = 0;
    return isBalanced(root, height);
}

// version 2
void Judge_AVL(Bitree * T, bool & balance, int & h)
{
    int hl = 0, hr = 0;
    bool bl = false, br = false;
    if (!T) {
        h = 0;
        balance = true;
    } else if (!T->lchild && !T->rchild) {
        h = 1;
        balance = true;
    } else {
        Judge_AVL(T->lchild, bl, hl);
        Judge_AVL(T->rchild, br, hr);
        if (abs(hl - hr) < 2)
            balance = bl && br;
        else
            balance = false;
    }
}
