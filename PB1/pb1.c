#include <stdio.h>
#include <stdlib.h>  
#include <string.h> 
#include <ctype.h>

#define MAX_STACK 100

typedef enum {false, true} bool;

// Data type definition
typedef int Data;

/* #############################################
    스택 구조체 
################################################# */
typedef struct {
    Data items[MAX_STACK];
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

Data Peek(Stack *pstack) {
    if (IsEmpty(pstack)) {
        fprintf(stderr, "Stack empty error\n");
        exit(1); 
    }
    return pstack->items[pstack->top];
}

void Push(Stack *pstack, Data item) {
    if (IsFull(pstack)) {
        fprintf(stderr, "Stack full error\n");
        exit(1);
    }
    pstack->items[++(pstack->top)] = item;
}

Data Pop(Stack *pstack) {
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
Converting Infix to Prefix
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

int EvalPostfix(char* exp, int len){
    Stack stack;
    int op1, op2;
    InitStack(&stack);
    
    for (int i=0; i< len; i++){
        if (isdigit(exp[i])) {
            // Convert char digit to integer value
            Push(&stack, exp[i] - '0');
        } else {
            op2 = Pop(&stack);
            op1 = Pop(&stack);
            
            Data result;
            
            if(exp[i] == '+') result = op1 + op2;
            else if(exp[i] == '-') result = op1 - op2;
            else if(exp[i] == '*') result = op1 * op2;
            else if(exp[i] == '/') result = op1 / op2;
            
            Push(&stack, result);
        }
    }
    
    return Peek(&stack);
}
/*
End Infix 2 Prefix
*/

int main(){
    char exp[100];
    char exp1[100];
    char exp2[100];
    char exp3[100];
    char exp4[100];
    char test_case[] = "(1+2)*3"; // answer 9
    char test_case1[] = "(1+2)*3+2"; // answer 11
    char test_case2[] = "(1+6/3+1)*3+7"; // answer 19
    char test_case3[] = "3+5*(9+2)*3/(3*(4+7))"; // answer 8
    char test_case4[] = "(1+2/2+5*(4+1))*3"; // answer 81
        
    printf("\ntest_case\n");    
    ConvInfixToPostfix(test_case, exp, strlen(test_case));
    printf("equation: %s=9\n", test_case);
    printf("postfix: %s\n", exp);
    printf("result: %d\n", EvalPostfix(exp, strlen(exp)));
    
    printf("\ntest_case1\n");
    ConvInfixToPostfix(test_case1, exp1, strlen(test_case1));
    printf("equation: %s=11\n", test_case1);
    printf("postfix: %s\n", exp1);
    printf("result: %d\n", EvalPostfix(exp1, strlen(exp1)));
    
    printf("\ntest_case2\n");
    ConvInfixToPostfix(test_case2, exp2, strlen(test_case2));
    printf("equation: %s=19\n", test_case2);
    printf("postfix: %s\n", exp2);
    printf("result: %d\n", EvalPostfix(exp2, strlen(exp2)));
    
    printf("\ntest_case3\n");
    ConvInfixToPostfix(test_case3, exp3, strlen(test_case3));
    printf("equation: %s=8\n", test_case3);
    printf("postfix: %s\n", exp3);
    printf("result: %d\n", EvalPostfix(exp3, strlen(exp3)));
    
    printf("\ntest_case4\n");
    ConvInfixToPostfix(test_case4, exp4, strlen(test_case4));
    printf("equation: %s=81\n", test_case4);
    printf("postfix: %s\n", exp4);
    printf("result: %d\n", EvalPostfix(exp4, strlen(exp4)));
    return 0;
}