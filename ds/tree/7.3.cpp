#include <iostream>

struct Bitree
{
    char data;
    Bitree *lchild;
    Bitree *rchild;
};

int abs (int x) { return x > 0 ? x : -x; }

bool t5_JudgeBST(Bitree *T);
bool t5_JudgeBST1(Bitree *T, char &pre);
int t6_NodeLevel(Bitree *T, char x);
void Judge_AVL(Bitree * T, bool & balance, int & h);

int main()
{
    //      A
    //     / \
    //    B   C
    //   /   / \
    //  D   E   F
    Bitree D = {'D', nullptr, nullptr};
    Bitree E = {'E', nullptr, nullptr};
    Bitree F = {'F', nullptr, nullptr};
    Bitree B = {'B', &D, nullptr};
    Bitree C = {'C', &E, &F};
    Bitree A = {'A', &B, &C};

    // int depth = t3_Btdepth(&A);
    // std::cout << "Tree depth: " << depth << std::endl;
    // std::cout << "Tree is completed: " << t4_IsComplete(&A) << std::endl;

    return 0;
}

bool t5_JudgeBST(Bitree *T)
{
    char pre = 0;
    if (t5_JudgeBST1(T, pre))
        return true;
    else
        return false;
}

bool t5_JudgeBST1(Bitree *T, char &pre)
{
    if (T == nullptr)
        return true;
    if (!t5_JudgeBST1(T->lchild, pre))
        return false;
    if (pre >= T->data)
        return false;
    pre = T->data;
    return t5_JudgeBST1(T->rchild, pre);
}

int t6_NodeLevel(Bitree *T, char x)
{
    if (!T) return 0;

    int level = 1;
    Bitree * p = T;
    while (!p) {
        if (x < T->data)
            p = p->lchild;
        else if (x > T->data)
            p = p->rchild;
        else
            return level;
        ++level;
    }
    return level;
}

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