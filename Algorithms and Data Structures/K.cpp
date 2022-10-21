#include <iostream>
#include <vector>

using namespace std;

struct Block {
    int index, start, end;
    Block *previous;
    Block *next;
    bool is_free;

    Block(int index, int start, int end, bool is_free, Block* previous, Block* next) {
        this->index = index;
        this->start = start;
        this->end = end;
        this->is_free = is_free;
        this->previous = previous;
        this->next = next;
        if (previous != nullptr) previous->next = this;
        if (next != nullptr) next->previous = this;
    }

    void remove() {
        if (previous != nullptr) previous->next = next;
        if (next != nullptr) next->previous = previous;
    }
};

Block* freeBlocks[100000];

void swap(int a, int b) {
    Block* t = freeBlocks[a];
    freeBlocks[a] = freeBlocks[b];
    freeBlocks[b] = t;
    freeBlocks[b]->index = b;
    freeBlocks[a]->index = a;
}

void siftDown(Block** heap, int n, int i) {
    int j = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && (heap[j]->end - heap[j]->start + 1) < (heap[l]->end - heap[l]->start + 1)) {
        j = l;
    }
    if (r < n && (heap[j]->end - heap[j]->start + 1) < (heap[r]->end - heap[r]->start + 1)) {
        j = r;
    }
    if (i != j) {
        swap(i, j);
        siftDown(heap, n, j);
    }
}

void siftUp(Block** heap, int i) {
    while (i > 0 && (heap[(i - 1) / 2]->end - heap[(i - 1) / 2]->start + 1) < (heap[i]->end - heap[i]->start + 1)) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void heap_remove(Block** heap, int& n, int i) {
    swap(i, n - 1);
    n--;
    if (i < n) {
        siftUp(heap, i);
        siftDown(heap, n, i);
    }
}

int main() {
    int n, m, read;
    cin >> n >> m;
    Block* req[100000];
    freeBlocks[0] = new Block(0, 1, n, true, nullptr, nullptr);
    int indexOfFreeBlock = 1;
    for (int i = 0; i < m; i++) {
        cin >> read;
        if (read > 0) {
            Block* free = freeBlocks[0];
            if (indexOfFreeBlock == 0) {
                cout << -1 << endl;
                continue;
            }
            int len = free->end - free->start + 1;
            if (read <= len) {
                cout << free->start << endl;
                req[i] = new Block(-1, free->start, free->start + read - 1, false, free->previous, free);
                free->start += read;
                if (free->end - free->start + 1 <= 0) {
                    free->remove();
                    heap_remove(freeBlocks, indexOfFreeBlock, 0);
                } else {
                    siftDown(freeBlocks, indexOfFreeBlock, free->index);
                }
            } else {
                cout << -1 << endl;
            }
        } else {
            Block* del = req[(-read) - 1];
            if (del != nullptr) {
                Block* previous = del->previous;
                Block* next = del->next;
                if (!(previous && previous->is_free) && !(next && next->is_free)) {
                    del->is_free = true;
                    del->index = indexOfFreeBlock;
                    freeBlocks[indexOfFreeBlock] = del;
                    siftUp(freeBlocks, indexOfFreeBlock++);
                } else if (!(next && next->is_free)) {
                    del->previous->end = del->end;
                    int index = del->previous->index;
                    siftUp(freeBlocks, index);
                    del->remove();
                } else if (!(previous && previous->is_free)) {
                    del->next->start = del->start;
                    int index = del->next->index;
                    siftUp(freeBlocks, index);
                    del->remove();
                } else {
                    del->previous->end = del->next->end;
                    int index = del->previous->index;
                    siftUp(freeBlocks, index);
                    del->remove();
                    index = del->next->index;
                    heap_remove(freeBlocks, indexOfFreeBlock, index);
                    del->next->remove();
                }
            }
        }
    }
}