#ifndef _PB3_H
#define _PB3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEAP 100

typedef enum {false, true} bool;
typedef char Data;


// Heap
typedef struct {
    Data data;
    int priority;
} HNode;

typedef struct{
    HNode items[MAX_HEAP+1];
    int num;
}Heap;

void InitHeap(Heap *pheap){
    pheap->num=0;
}
bool IsEmpty(Heap *pheap){
    return pheap->num == 0;
}
bool IsFull(Heap *pheap){
    return pheap->num ==MAX_HEAP;
}
void Insert(Heap *pheap, Data data, int priority){
    HNode newNode;
    int idx = pheap->num+1;
    if(IsFull(pheap)) exit(1);

    while(idx>1){
        int parent = GetParent(idx);
        if(priority > pheap->items[parent].priority){
            pheap->items[idx] = pheap->items[parent];
            idx=parent;
        }
        else break;
    }
    newNode.data = data;
    newNode.priority = priority;

    pheap->items[idx] = newNode;
    pheap->num++;
}

int GetParent(int idx){
    return idx/2;
}
int GetLeftChild(int idx){
    return idx*2;
}
int GetRightChild(int idx){
    return idx*2+1;
}
int GetHighPriorityChild(Heap* pheap, int idx){
    if(GetLeftChild(idx) > pheap -> num)
        return 0;
    else if(GetLeftChild(idx) == pheap -> num)
        return GetLeftChild(idx);
    else{
        int left =GetLeftChild(idx), right = GetRightChild(idx);
        if(pheap->items[left].priority > pheap->items[right].priority)
            return left;
        else
            return right;
        
    }
}

Data Delete(Heap *pheap){
    Data max = pheap->items[1].data;
    HNode last = pheap->items[pheap->num];
    int parent = 1, child;
    while(child=GetHighPriorityChild(pheap, parent)){
        if(last.priority < pheap -> items[child].priority){
            pheap->items[parent] = pheap -> items[child];
            parent = child;
        }
        else break;
    }

    pheap->items[parent] = last;
    pheap->num--;

    return max;
}

// Priority Queue
typedef Heap PQueue;

void InitPQueue(PQueue* ppqueue) {
    InitHeap(ppqueue);
}
bool IsPQEmpty(PQueue* ppqueue) {
    return IsEmpty(ppqueue);
}
bool IsPQFull(PQueue* ppqueue) {
    return IsFull(ppqueue);
}
void Enqueue(PQueue* ppqueue, Data data, int priority) {
    Insert(ppqueue, data, priority);
}
Data Dequeue(PQueue* ppqueue) {
    return Delete(ppqueue);
}

#endif