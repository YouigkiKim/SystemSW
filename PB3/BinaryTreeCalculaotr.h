#ifndef _BINARY_TREE_CALCULATOR_H
#define _BINARY_TREE_CALCULATOR_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STACK 100

typedef enum {false, true} bool;
typedef int Data;

// Binary tree using linked list
typedef struct _bTreeNode{
    Data item;
    struct _bTreeNode * left_child;
    struct _bTreeNode * right_child;
} BTreeNode;

// Binary Tree
BTreeNode* CreateNode(Data item){
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node -> item = item;
    node -> left_child = NULL;
    node -> right_child = NULL;
    return node;
}
void DestroyNode(BTreeNode* node){
    free(node);
}
void CreateLeftSubtree(BTreeNode* root, BTreeNode* left){
    
    if( root -> left_child != NULL) exit(1);

    root->left_child = left;
}
void CreateRightSubtree(BTreeNode* root, BTreeNode* right){
    
    if(root->right_child != NULL) exit(1);

    root->right_child = right;
}

// Check tree state
int Nodes(BTreeNode* node){
    // Recursive Counting
    int r=0, l=0;
    if(node->right_child != NULL) 
        r = Nodes(node->right_child);
    if(node->left_child != NULL) 
        l = Nodes(node->left_child);

    return r+l+1;
}
int Height(BTreeNode *node){
    int r=0, l = 0;
    if (node->right_child != NULL) 
        r = Height(node->right_child);
    if (node->left_child != NULL) 
        l = Height(node->left_child);

    if (r > l) 
        return r+1;
    else 
        return l+1;
};




// Data type definition

/* #############################################
    스택 구조체 
################################################# */

typedef struct {
    BTreeNode* items[MAX_STACK];
    int top;
} Stack;

void InitStack(Stack *pstack) {
    pstack->top = -1;
}

bool IsFull(Stack *pstack) {
    return pstack->top == MAX_STACK - 1;
}

bool IsEmpty(Stack *pstack) {
    return pstack->top == -1;
}

BTreeNode* Peek(Stack *pstack) {
    if (IsEmpty(pstack)) {
        fprintf(stderr, "Stack empty error\n");
        exit(1); 
    }
    return pstack->items[pstack->top];
}
void Push(Stack *pstack, BTreeNode *node) {
    if (IsFull(pstack)) {
        fprintf(stderr, "Stack full error\n");
        exit(1);
    }
    pstack->items[++(pstack->top)] = node;
}

BTreeNode* Pop(Stack *pstack) {
    if (IsEmpty(pstack)) {
        fprintf(stderr, "Stack empty error\n");
        exit(1);
    }
    return pstack->items[(pstack->top)--];
}

/*
End Stack
*/


/* #############################################
Converting Infix to Prefix From PB1
################################################# */
int GetPriority(char op){
    if (op == '*' || op == '/'){
        return 2;
    }
    // else if ( op == ')'){
    //     return 3;}
    else if (op == '+' || op == '-'){
        return 1;
    }else{
        return 0;
    }
}

bool ComPriority(char op1, char op2){
    int op1_pr = GetPriority(op1);
    int op2_pr = GetPriority(op2);

    if(op1_pr >= op2_pr){
        return true;
    }else{
        return false;
    }
}

void ConvInfixToPostfix(char* exp, char* convExp, int len){
    Stack stack;
    InitStack(&stack);
    int idx = 0;
    
    for (int i=0; i<len; i++){
        if (isdigit(exp[i])){
            convExp[idx++] = exp[i];
        }else if (exp[i] == '('){
            Push(&stack, exp[i]);
        }else if (exp[i] == ')'){
            while (!IsEmpty(&stack) && (char)Peek(&stack) != '('){
                convExp[idx++] = (char)Pop(&stack);
            }
            if (!IsEmpty(&stack) && (char)Peek(&stack) == '('){
                Pop(&stack); // 왼쪽 괄호 제거
            }
        }else{
            // Store operator as integer
            Data item = exp[i];
            
            while (!IsEmpty(&stack) && (char)Peek(&stack) != '(' && ComPriority((char)Peek(&stack), exp[i])){
                convExp[idx++] = (char)Pop(&stack);
            }
            
            Push(&stack, item);
        }
    }
    
    while(!IsEmpty(&stack)){
        convExp[idx++] = (char)Pop(&stack);
    }
    
    convExp[idx] = '\0'; 
}


/*
End Infix 2 Prefix
*/


// Expression Tree
BTreeNode *MakeExpTree(char* exp, int len);



#endif