#include <iostream>
#include <climits>

using namespace std;

struct Node {
    Node * next;
    int item;
};

struct Node_t13 {
    Node_t13 * next;
    Node_t13 * prev;
    int x;
    int freq;
};

void t1_deletex(Node & h, int x);
int t2_deleteMin(Node & h);
void t3_inverse1(Node & h);
void t3_inverse2(Node & h);
Node * t5_findSameNode(Node & h1, Node & h2);
void t6_divideList(Node & c, Node & a, Node & b);
void t9_intersection(Node & a, Node & b);
Node_t13 * t13_locate(Node_t13 & l, int x);
void t20_reSort(Node & l);

int main()
{
    const int LEN = 5;
    Node * head = new Node{nullptr, 0};
    // 构造链表 1->2->3->4->5
    Node * tail = head;
    for (int i = 1; i <= LEN; ++i) {
        tail->next = new Node{nullptr, i};
        tail = tail->next;
    }

    // 打印原链表
    std::cout << "Original list: ";
    Node * p = head->next;
    while (p) {
        std::cout << p->item << " ";
        p = p->next;
    }
    std::cout << std::endl;

    // 逆置
    t3_inverse1(*head);

    // 打印逆置后链表
    std::cout << "Reversed list: ";
    p = head->next;
    while (p) {
        std::cout << p->item << " ";
        p = p->next;
    }
    std::cout << std::endl;

    // 释放链表内存
    p = head;
    while (p) {
        Node * tmp = p;
        p = p->next;
        delete tmp;
    }
    return 0;
}

void t1_deletex(Node & h, int x)
{
    Node * p = &h;
    Node * q = h.next;

    while (q) {
        if (q->item == x) {
            p->next = q->next;
            Node * temp = q;
            q = q->next;
            delete temp;
        } else {
            p = p->next;
            q = q->next;
        }
    }
}

int t2_deleteMin(Node & h) {
    if (h.next == nullptr)
        return INT_MAX;

    int min_value = INT_MAX; 
    Node * min_node = h.next;
    Node * prev = &h;
    Node * p = &h, * q = h.next;
    while (q) {
        if (q->item < min_value) {
            min_value = q->item;
            min_node = q;
            prev = p;
        }
        p = q;
        q = q->next;
    }
    prev->next = min_node->next;
    delete min_node;
    return min_value;
}

void t3_inverse1(Node & h)
{
    Node * prev = nullptr;
    Node * cur = h.next;
    while (cur) {
        Node * next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    h.next = prev;
}

void t3_inverse2(Node & h)
{
    Node * cur = h.next;

    h.next = nullptr;
    while (cur) {
        Node * next = cur->next;
        cur->next = h.next;
        h.next = cur;
        cur = next;
    }
}

Node * t5_findSameNode(Node & h1, Node & h2)
{
    int len1 = 0, len2 = 0;
    Node *cur1 = h1.next, *cur2 = h2.next;
    Node *tail1 = nullptr, *tail2 = nullptr;

    // 计算长度和尾节点
    for (; cur1; cur1 = cur1->next, ++len1) tail1 = cur1;
    for (; cur2; cur2 = cur2->next, ++len2) tail2 = cur2;

    // 没有相交节点
    if (tail1 != tail2) return nullptr;

    // 重新指向表头
    cur1 = h1.next;
    cur2 = h2.next;
    // 长链表先走
    if (len1 > len2) {
        for (int i = 0; i < len1 - len2; ++i) cur1 = cur1->next;
    } else {
        for (int i = 0; i < len2 - len1; ++i) cur2 = cur2->next;
    }
    // 同步走，找到第一个公共节点
    while (cur1 && cur2) {
        if (cur1 == cur2) return cur1;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    return nullptr;
}

void t6_divideList(Node & c, Node & a, Node & b)
{   
    Node *cur = c.next;
    Node *pa = &a, *pb = &b;
    bool flag = true;

    while (cur) {
        Node * next = cur->next;
        if (flag) {
            pa->next = cur;
            pa = pa->next;
        } else {
            pb->next = cur;
            pb = pb->next;
        }
        flag = !flag;
        cur->next = nullptr;
        cur = next;
    }
    pa->next = nullptr;
    pb->next = nullptr;
}

void t9_intersection(Node & a, Node & b)
{   // a and b are sorted
    if (!a.next || !b.next)
        return;

    Node * cur_a = a.next;
    Node * cur_b = b.next;
    Node * prev = &a;

    while (cur_a && cur_b) {
        if (cur_a->item > cur_b->item) {
            cur_b = cur_b->next;
        } else if (cur_a->item < cur_b->item) {
            Node * next = cur_a->next;
            prev->next = next;
            delete cur_a;
            cur_a = next;
        } else {
            prev = cur_a;
            cur_a = cur_a->next;
            cur_b = cur_b->next;
        }
    }

    while (cur_a) {
        Node * next = cur_a->next;
        prev->next = next;
        delete cur_a;
        cur_a = next;
    }
}

Node_t13 * t13_locate(Node_t13 & l, int x)
{
    Node_t13 * cur = l.next;

    while (cur && cur->x != x) 
        cur = cur->next;
    if (!cur)
        return nullptr;
    
    cur->freq++;

    if (!cur->prev || cur->prev == &l)
        return cur;

    if (cur->prev)
        cur->prev->next = cur->next;
    if (cur->next)
        cur->next->prev = cur->prev;

    Node_t13 * pos = cur->prev;
    while (pos != &l && pos->freq <= cur->freq)
        pos = pos->prev;

    cur->next = pos->next;
    if (pos->next)
        pos->next->prev = cur;
    cur->prev = pos;
    pos->next = cur;

    return cur;
}

void t20_reSort(Node & l)
{
    if (!l.next || !l.next->next)
        return;

    // 1. 找到中点
    Node *slow = l.next, *fast = l.next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 2. 断开前后半部分
    Node *second = slow->next;
    slow->next = nullptr;

    // 3. 逆置后半部分
    Node *prev = nullptr, *cur = second;
    while (cur) {
        Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    second = prev;

    // 4. 交错合并
    Node *first = l.next;
    while (first && second) {
        Node *tmp1 = first->next;
        Node *tmp2 = second->next;
        first->next = second;
        if (tmp1 == nullptr) break;
        second->next = tmp1;
        first = tmp1;
        second = tmp2;
    }
}
