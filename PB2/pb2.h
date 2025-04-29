#ifndef _PB2_H
#define _PB2_H

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK       100

typedef enum {false, true} bool;
typedef int BData;

// Binary tree using linked list
typedef struct _bTreeNode{
    BData item;
    struct _bTreeNode * left_child;
    struct _bTreeNode * right_child;
} BTreeNode;

BTreeNode* CreateNode(BData item);
void DestroyNode(BTreeNode *node);
void CreateLeftSubtree(BTreeNode *root, BTreeNode *left);
void CreateRightSubtree(BTreeNode *root, BTreeNode *right);


// Traversal
void Inorder(BTreeNode *root);
void Preorder(BTreeNode *root);
void Postorder(BTreeNode *root);


// Stack for Non-recursive traversal

typedef BTreeNode* Data;

typedef struct {
    Data items[MAX_STACK];
    int top;
} Stack;

void InitStack(Stack *pstack){
    pstack->top = -1;
}
bool IsFull(Stack *pstack){
    return pstack->top == MAX_STACK -1;
}
bool IsEmpty(Stack *pstack){
    return pstack->top == -1;
}
Data Peek(Stack *pstack){
    if (IsEmpty(pstack))
        exit(1);
    return pstack->items[pstack->top];
}
void Push(Stack *pstack, Data item){
    if(IsFull(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;   
} 
void Pop(Stack *pstack){
    if(IsEmpty(pstack))
        exit(1);
    --(pstack->top);
}


#endif