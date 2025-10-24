/*
    输入一个整数data和一棵二元树。从树的根节点开始往下访问一直到叶节点，所经过的所
    有结点形成一条路径。打印出路径及与data相等的所有路径。例如，输入整数22和下图所
    示的二元树，则打印出两条路径10, 12和10, 5, 7.
                        10
                       /  \
                      5   12
                     / \
                    4   7
*/
#include <iostream>

struct Bitree
{
    int data;
    Bitree * lchild, * rchild;
};

struct Stack {
    int top;
    int s[100];
    int sum;
};

void printStack(Stack & s)
{
    for (int i = 0; i < s.top; ++i) {
        std::cout << s.s[i];
        if (i < s.top-1)
            std::cout << ", ";
    }
        
    std::cout << std::endl;
}

void findPath1(Bitree * root, int x, Stack & stack)
{
    if (!root) return;

    stack.s[stack.top++] = root->data;
    stack.sum += stack.s[stack.top-1];
    if (stack.sum == x && !root->lchild && !root->rchild) {
        printStack(stack);
        stack.sum -= stack.s[--stack.top];
        return;
    } else if (stack.sum > x) {
        stack.sum -= stack.s[--stack.top];
        return;
    }

    findPath1(root->lchild, x, stack);
    findPath1(root->rchild, x, stack);

    stack.sum -= stack.s[--stack.top];
}

void findPath(Bitree * root, int x)
{
    Stack stack;
    stack.top = stack.sum = 0;
    findPath1(root, x, stack);
}

int main()
{
    return 0;
}

