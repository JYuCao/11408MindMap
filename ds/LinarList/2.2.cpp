#include <iostream>
#include <climits>
#include "Seqlist.h"

int t1_deleteMin(Seqlist & seq);
void t2_inverseList(Seqlist & seq);
void t3_deletex(Seqlist & seq, int x);
void t8_halfsearch(Seqlist & seq, int x);

int main()
{
    Seqlist * seq = new Seqlist(10);
    // 插入测试数据
    seq->listInsert(0, 5);
    seq->listInsert(1, 2);
    seq->listInsert(2, 8);
    seq->listInsert(3, 1);
    seq->listInsert(4, 6);

    // 打印原始数据
    std::cout << "Original Seqlist: ";
    for (int i = 0; i < seq->length; ++i) {
        std::cout << seq->seqlist[i] << " ";
    }
    std::cout << std::endl;

    // 测试t2_inverseList
    t2_inverseList(*seq);
    std::cout << "Seqlist after inverse: ";
    for (int i = 0; i < seq->length; ++i) {
        std::cout << seq->seqlist[i] << " ";
    }
    std::cout << std::endl;

    delete seq;
    return 0;
}

int t1_deleteMin(Seqlist & seq)
{
    if (seq.length <= 0) {
        std::cout << "Seqlist is empty!" << std::endl;
        return -1;
    }
        
    int index_min = 0;
    int min = INT_MAX;
    for (int i = 0; i < seq.length; ++i) {
        if (seq.seqlist[i] < min) {
            index_min = i;
            min = seq.seqlist[i];
        }
    }
    int e = seq.seqlist[index_min];
    seq.seqlist[index_min] = seq.seqlist[seq.length - 1];
    return e;
}

void t2_inverseList(Seqlist & seq)
{
    for (int i = 0; i < seq.length / 2; ++i) {
        int temp = seq.seqlist[i];
        seq.seqlist[i] = seq.seqlist[seq.length - i - 1];
        seq.seqlist[seq.length - i - 1] = temp;
    }
}

void t3_deletex(Seqlist & seq, int x)
{
    int k = 0;
    for (int i = 0; i < seq.length; ++i) {
        if (seq.seqlist[i] != x)
            seq.seqlist[k++] = seq.seqlist[i];
    }
    seq.length = k;
}

void t8_halfsearch(Seqlist & seq, int x) {
    int left = 0;
    int right = seq.length - 1;
    int mid = (left + right) / 2;

    while (left <= right) {
        if (seq.seqlist[mid] < x)
            left = mid + 1;
        else if (seq.seqlist[mid] > x)
            right = mid - 1;
        else
            break;
        mid = (left + right) / 2;
    }

    if (seq.seqlist[mid] != x) {
        for (int i = seq.length; i > left; ++i) 
            seq.seqlist[i] = seq.seqlist[i-1];
        seq.seqlist[left] = x;
        seq.length++;
    } else {
        if (mid != seq.length - 1) {
            seq.seqlist[mid] = seq.seqlist[mid+1];
            seq.seqlist[mid+1] = x;
        }
    }
}

