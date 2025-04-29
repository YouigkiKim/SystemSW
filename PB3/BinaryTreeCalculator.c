#include "BinaryTreeCalculator.h"


int CalculateExpTree(BTreeNode *root){
    int op1, op2;
    if(root == NULL) return 0;
    if ( root->left_child == NULL && root->right_child == NULL)
        return root->item;

    op1 = CalculateExpTree(root->left_child);
    op2 = CalculateExpTree(root->right_child);

    switch(root->item){
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
    }
    return 0;
}
BTreeNode *MakeExpTree(char* exp, int len){
    Stack stack;
    BTreeNode *node, *right_node, *left_node;

    InitStack(&stack);
    for(int i=0; i<len; i++){
        if('0'<=exp[i] && exp[i] <='9'){
            node = CreateNode(exp[i]-'0');
        }
        else{
            right_node = Peek(&stack),Pop(&stack);
            left_node = Peek(&stack),Pop(&stack);
            node = CreateNode(exp[i]);
            CreateRightSubtree(node, right_node);
            CreateLeftSubtree(node, left_node);
        }
        Push(&stack, node);
    } 
    return Peek(&stack);
}

int main(){

    // Test1
    char exp1[] = "7+2*3";
    int len1 = strlen(exp1);
    printf("Equation: %s, answer: %d\n", exp1, 7+2*3);
    char convExp1[len1];
    ConvInfixToPostfix(exp1, convExp1, len1);
    printf("Postfix: %s\n", convExp1);
    BTreeNode *root1 = MakeExpTree(convExp1, len1);
    printf("Result: %d\n", CalculateExpTree(root1));
    
    // Test2
    char exp2[] = "5*4-3+8/2";
    int len2 = strlen(exp2);
    printf("Equation: %s, answer: %d\n", exp2, 5*4-3+8/2);
    char convExp2[len2];
    ConvInfixToPostfix(exp2, convExp2, len2);
    printf("Postfix: %s\n", convExp2);
    BTreeNode *root2 = MakeExpTree(convExp2, len2);
    printf("Result: %d\n", CalculateExpTree(root2));
    
    // Test3
    char exp3[] = "9/3+2*5-1";
    int len3 = strlen(exp3);
    printf("Equation: %s, answer: %d\n", exp3, 9/3+2*5-1);
    char convExp3[len3];
    ConvInfixToPostfix(exp3, convExp3, len3);
    printf("Postfix: %s\n", convExp3);
    BTreeNode *root3 = MakeExpTree(convExp3, len3);
    printf("Result: %d\n", CalculateExpTree(root3));
    
    // Test4
    char exp4[] = "8-4/2+7*3-1";
    int len4 = strlen(exp4);
    printf("Equation: %s, answer: %d\n", exp4, 8-4/2+7*3-1);
    char convExp4[len4];
    ConvInfixToPostfix(exp4, convExp4, len4);
    printf("Postfix: %s\n", convExp4);
    BTreeNode *root4 = MakeExpTree(convExp4, len4);
    printf("Result: %d\n", CalculateExpTree(root4));
    
    // Test5
    char exp5[] = "1+2+3*4-5/2+9";
    int len5 = strlen(exp5);
    printf("Equation: %s, answer: %d\n", exp5, 1+2+3*4-5/2+9);
    char convExp5[len5];
    ConvInfixToPostfix(exp5, convExp5, len5);
    printf("Postfix: %s\n", convExp5);
    BTreeNode *root5 = MakeExpTree(convExp5, len5);
    printf("Result: %d\n", CalculateExpTree(root5));

    char input[100];
    printf("\nEnter an expression: ");
    scanf("%s", input);
    int input_len = strlen(input);
    printf("Equation: %s\n", input);
    char userConvExp[input_len];
    ConvInfixToPostfix(input, userConvExp, input_len);
    printf("Postfix: %s\n", userConvExp);
    BTreeNode *userRoot = MakeExpTree(userConvExp, input_len);
    int result = CalculateExpTree(userRoot);
    printf("Result: %d\n", result);
    return 0;
}