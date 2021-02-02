/**********************************
* File:     Heap.h
*
* Author:   caipeng
*
* Email:    iiicp@outlook.com
*
* Date:     2021/2/2
***********************************/

#ifndef UCCPP_HEAP_H
#define UCCPP_HEAP_H

#define BLOCK_SIZE (4 * 1024)
#define ALIGN(size, align)  ((align == 0) ? size: ((size + align - 1) & (~(align - 1))))

#include <stdlib.h>
#include <stdio.h>

struct Block
{
    Block *next;
    char *begin;
    char *avail;
    char *end;
};
union align {
    double d;
    int (*f)(void);
};

struct Heap {
private:
    static Heap *_heap;
    static Block *_freeBlocks;
    Block *last;
    Block head;
private:
    Heap() {last = &head;}
    ~Heap() {};
    Heap(const Heap &);
    Heap &operator=(const Heap&);
public:

    static Heap *sharedHeap() {
        if (_heap == nullptr) {
            _heap = new Heap();
        }
        return _heap;
    }

    void init() {
        head.next = nullptr;
        head.begin = head.end = head.avail = nullptr;
        last = &head;
    }

    void *allocate(int size) {

        Block *blk = nullptr;
        size = ALIGN(size, sizeof(union align));

        /// 语义: 保持指向最后一个有效块
        blk = last;

        while (size > blk->end - blk->avail) {
            // get the first block from FreeBlocks, added into the Heap
            if (_freeBlocks != nullptr) {
                blk->next = _freeBlocks;
                blk = blk->next;
                _freeBlocks = _freeBlocks->next;
            }else {
                int m = size + BLOCK_SIZE + sizeof(Block);
                blk->next = (Block *)malloc(m);
                blk = blk->next;
                if (blk == nullptr) {
                    printf("Memory exhausted\n");
                    abort();
                }
                blk->end = (char *)blk + m;
            }
            blk->avail = blk->begin = (char *)(blk + 1);
            blk->next = NULL;
            last = blk;
        }

        // we are sure that there is enough space
        blk->avail += size;

        return blk->avail - size;
    }

    /// recycle a heap's all memory blocks into free block list
    void free() {
        last->next = _freeBlocks;
        _freeBlocks = head.next;
        init();
    }
};
/// static Heap *heap = nullptr;
Heap *Heap::_heap = nullptr;
Block *Heap::_freeBlocks = nullptr;

#endif//UCCPP_HEAP_H
