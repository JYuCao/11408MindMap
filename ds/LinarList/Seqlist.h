#ifndef __SEQLIST_H__
#define __SEQLIST_H__


class Seqlist {
private:


public:
    int maxlen;
    int length = 0;
    int * seqlist = nullptr;

    Seqlist(int maxlen) {
        this->maxlen = maxlen;
        this->seqlist = new int(maxlen);
    }

    ~Seqlist() {
        delete seqlist;
    }

    int len() {
        return length;
    }

    int locateElem(int e) {
        for (int i = 0; i < length; ++i) 
            if (e == seqlist[i])
                return i;
        return -1;
    }

    int getElem(int index) {
        return seqlist[index];
    }

    bool listInsert(int index, int e) {
        if (index > length || index < 0)
            return false;
        if (length >= maxlen)
            return false;
        
        for (int i = length; i > index; --i) {
            seqlist[i] = seqlist[i-1];
        }
        seqlist[index] = e;
        ++length;
        return true;
    }

    bool listDelete(int index, int & e) {
        if (index >= length || index < 0)
            return false;
        if (empty())
            return false;
        
        e = seqlist[index];
        for (int i = index; i < length - 1; ++i) {
            seqlist[i] = seqlist[i+1];
        }
        --length;
        return true;
    }

    void printList() {
        // todo
    }

    bool empty() {
        if (length <= 0)
            return true;
        else    
            return false;
    }
};

#endif
