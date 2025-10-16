#include <iostream>

struct Bitree {
    char data;
    Bitree * lchild;
    Bitree * rchild;
};

int t3_Btdepth(Bitree * T);
bool t4_IsComplete(Bitree * T);
int t5_DsonNodes(Bitree * T);
void t6_ExchangeLR(Bitree * T);
char t7_PreOrderK(Bitree * T, int & k);
Bitree * t8_DeleteXSubtree(Bitree * T, char data);
void t8_DeleteSubTree(Bitree * T);
void t9_PrintXParents(Bitree * T, int x);
bool t9_FindX(Bitree * T, int x, Bitree ** stack, int & top);
bool t9_FindX_nonrec(Bitree *T, int x, Bitree **stack, int &top);
int t11_Btwidth(Bitree * T);

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

    int depth = t3_Btdepth(&A);
    std::cout << "Tree depth: " << depth << std::endl;
    std::cout << "Tree is completed: " << t4_IsComplete(&A) << std::endl;

    return 0;
}

int t3_Btdepth(Bitree * T)
{
    if (!T) return 0;
    Bitree *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = T;
    int depth = 0;
    while (front < rear) {
        int level_size = rear - front;
        ++depth;
        for (int i = 0; i < level_size; ++i) {
            Bitree *p = queue[front++];
            if (p->lchild) queue[rear++] = p->lchild;
            if (p->rchild) queue[rear++] = p->rchild;
        }
    }
    return depth;

    // 递归实现
    // int Btdepth(Bitree *T) {
    //     if (!T) return 0;
    //     int l = Btdepth(T->lchild);
    //     int r = Btdepth(T->rchild);
    //     return std::max(l, r) + 1;
    // }
}

bool t4_IsComplete(Bitree * T) 
{
    if (!T)
        return true;

    Bitree * queue[100] = {nullptr};
    int front, rear;

    front = rear = 0;
    queue[rear++] = T;
    while (front < rear) {
        Bitree * p = queue[front++];
        if (p) {
            queue[rear++] = p->lchild;
            queue[rear++] = p->rchild;
        } else {
            while (front < rear) {
                if (!queue[front++])
                    return false;
            }
            return true;
        }
    }
}

int t5_DsonNodes(Bitree * T)
{
    if (!T) return 0;
    int cnt = t5_DsonNodes(T->lchild) + t5_DsonNodes(T->rchild);
    if (T->lchild && T->rchild) return cnt + 1;
    return cnt;
}

void t6_ExchangeLR(Bitree * T) 
{
    if (!T)
        return;

    t6_ExchangeLR(T->lchild);
    t6_ExchangeLR(T->rchild);

    Bitree * temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
}

char t7_PreOrderK(Bitree * T, int & k)
{
    if (!T) return '#';
    if (--k == 0) return T->data;
    
    char res = t7_PreOrderK(T->lchild, k);
    if (res != '#') return res;
    return t7_PreOrderK(T->rchild, k);
}


Bitree * t8_DeleteXSubtree(Bitree *T, char data) {
    if (!T) return nullptr;
    if (T->data == data) {
        t8_DeleteSubTree(T);
        return nullptr;
    }
    T->lchild = t8_DeleteXSubtree(T->lchild, data);
    T->rchild = t8_DeleteXSubtree(T->rchild, data);
    return T;
}

void t8_DeleteSubTree(Bitree * T) {
    if (!T)
        return;
    t8_DeleteSubTree(T->lchild);
    t8_DeleteSubTree(T->rchild);
    delete T;
}

void t9_PrintXParents(Bitree * T, int x)
{
    Bitree * stack[100];
    int top = 0;

    if (t9_FindX(T, x, stack, top))
        while (top > 0)
            std::cout << stack[--top]->data << std::endl;
}

bool t9_FindX(Bitree * T, int x, Bitree ** stack, int & top)
{
    if (!T) return false;
    if (T->data == x) return true;
    stack[top++] = T;
    if (t9_FindX(T->lchild, x, stack, top)) return true;
    if (t9_FindX(T->rchild, x, stack, top)) return true;
    --top;
    return false;
}

bool t9_FindX_nonrec(Bitree *T, int x, Bitree **stack, int &top) {
    top = 0;
    Bitree *cur = T, *last = nullptr;
    while (cur || top > 0) {
        while (cur) {
            stack[top++] = cur;
            cur = cur->lchild;
        }
        Bitree *peek = stack[top-1];
        // 如果右子树未访问，则访问右子树
        if (peek->rchild && last != peek->rchild) {
            cur = peek->rchild;
        } else {
            // 后序访问当前节点
            if (peek->data == x) {
                --top; // 不包含自身
                return true;
            }
            last = peek;
            --top;
        }
    }
    return false;
}

int t11_Btwidth(Bitree * T)
{
    if (!T) return 0;
    Bitree *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = T;
    int max_width = 0;
    while (front < rear) {
        int level_size = rear - front;
        if (level_size > max_width)
            max_width = level_size;
        for (int i = 0; i < level_size; ++i) {
            Bitree *p = queue[front++];
            if (p->lchild) queue[rear++] = p->lchild;
            if (p->rchild) queue[rear++] = p->rchild;
        }
    }
    return max_width;
}
