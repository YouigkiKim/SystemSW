// • Implement inorder, preorder, 
// and postorder traversals 
// of a binary tree  without using recursion

#include "pb2.h"
typedef int BData;

// Binary Tree
BTreeNode* CreateNode(BData item){
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

// Traversal
void Inorder(BTreeNode* root){
    /*
    스택에 좌측 leaf까지 쌓는다
    while 
        하나씩 꺼내면서 우측자식노드 확인 -> 자식노드 있으면 들어가서 Stack에 쌓음
        자식노드 없으면 출력
    */
    Stack stack;
    InitStack(&stack);
    BTreeNode* current = root;

    while(current != NULL || !IsEmpty(&stack)){
        while(current != NULL){
            Push(&stack, current);
            current = current->left_child;
        }
        
        current = Peek(&stack);
        Pop(&stack);
        
        printf("%d ", current->item);
        
        current = current->right_child;  // 오른쪽 자식 노드로 이동
    }
    printf("\n");
}
void Preorder(BTreeNode* root){
    Stack stack;
    InitStack(&stack);
    BTreeNode* current = root;

    while(current != NULL || !IsEmpty(&stack)){
        while(current != NULL){
            printf("%d ", current->item);
            
            if(current->right_child != NULL)
                Push(&stack, current->right_child);
            
            current = current->left_child;
        }
        
        if(!IsEmpty(&stack)){
            current = Peek(&stack);
            Pop(&stack);
        }
    }
    printf("\n");
}
void Postorder(BTreeNode* root){
    Stack stack;
    InitStack(&stack);
    BTreeNode* current = root;
    BTreeNode* last_visited = NULL;

    while(current != NULL || !IsEmpty(&stack)){

        while(current != NULL){
            Push(&stack, current);
            current = current->left_child;
        }
        
        current = Peek(&stack);
        
        if(current->right_child == NULL || current->right_child == last_visited){
            printf("%d ", current->item);
            last_visited = current;
            Pop(&stack);
            current = NULL;
        }
        else{
            current = current->right_child;
        }
    }
    printf("\n");
}

//Binary Tree END




int main(){
    // 테스트용 트리1  -> 깊이 3짜리 트리 Full binary tree
    BTreeNode* root = CreateNode(1);
    BTreeNode* node2 = CreateNode(2);
    BTreeNode* node3 = CreateNode(3);
    BTreeNode* node4 = CreateNode(4);
    BTreeNode* node5 = CreateNode(5);
    BTreeNode* node6 = CreateNode(6);
    BTreeNode* node7 = CreateNode(7);

    CreateLeftSubtree(root, node2);
    CreateRightSubtree(root, node3);
    CreateLeftSubtree(node2, node4);
    CreateRightSubtree(node2, node5);
    CreateLeftSubtree(node3, node6);
    CreateRightSubtree(node3, node7);

    printf("Test full binary tree(depth 3) ###################################### \n");
    /*
          1
        / \
       2  3
      /\ /\
     4 5 6 7
    */
    printf("expected output\n");
    printf("Inorder: 4 2 5 1 6 3 7\n");
    printf("Preorder: 1 2 4 5 3 6 7\n");
    printf("Postorder: 4 5 2 6 7 3 1\n");
    printf("Algorithm output\n");
    printf("Inorder: ");
    Inorder(root);
    
    printf("Preorder: ");
    Preorder(root);
    
    printf("Postorder: ");
    Postorder(root);

    // 메모리 해제
    DestroyNode(node4);
    DestroyNode(node5);
    DestroyNode(node6);
    DestroyNode(node7);
    DestroyNode(node2);
    DestroyNode(node3);
    DestroyNode(root);


    // 테스트 트리 2 -> uncomplete binary tree
    BTreeNode *t2_root = CreateNode(1);
    BTreeNode *t2_node2 = CreateNode(2);
    BTreeNode *t2_node3 = CreateNode(3);
    BTreeNode *t2_node4 = CreateNode(4);
    BTreeNode *t2_node6 = CreateNode(6);
    BTreeNode *t2_node7 = CreateNode(7);
    
    CreateLeftSubtree(t2_root, t2_node2);
    CreateRightSubtree(t2_root, t2_node3);
    CreateLeftSubtree(t2_node2, t2_node4);
    CreateLeftSubtree(t2_node3, t2_node6);
    CreateRightSubtree(t2_node3, t2_node7);

    printf("Test uncomplete binary tree (absent node 5) ########################## \n");
    printf("expected output\n");
    printf("Inorder: 4 2 1 6 3 7\n");
    printf("Preorder: 1 2 4 3 6 7\n");
    printf("Postorder: 4 2 6 7 3 1\n");
    /*
          1
        / \
       2  3
      /  /\
     4  6 7
    */
    printf("Algorithm output\n");
    printf("Inorder: ");
    Inorder(t2_root);
    
    printf("Preorder: ");
    Preorder(t2_root);
    
    printf("Postorder: ");
    Postorder(t2_root);
    
    DestroyNode(t2_node4);
    DestroyNode(t2_node6);
    DestroyNode(t2_node7);
    DestroyNode(t2_node2);
    DestroyNode(t2_node3);
    DestroyNode(t2_root);
    
    // 테스트 트리 3 -> right skewed tree
    BTreeNode *t3_root = CreateNode(1);
    BTreeNode *t3_node2 = CreateNode(2);
    BTreeNode *t3_node3 = CreateNode(3);
    BTreeNode *t3_node4 = CreateNode(4);
    
    CreateRightSubtree(t3_root, t3_node2);
    CreateRightSubtree(t3_node2, t3_node3);
    CreateRightSubtree(t3_node3, t3_node4);
    
    printf("Test right skewed tree ########################## \n");
    printf("expected output\n");
    printf("Inorder: 1 2 3 4\n");
    printf("Preorder: 1 2 3 4\n");
    printf("Postorder: 4 3 2 1\n");
    /*
        1
         \
          2
           \
            3
             \
              4
    */
    printf("Algorithm output\n");
    printf("Inorder: ");
    Inorder(t3_root);
    
    printf("Preorder: ");
    Preorder(t3_root);
    
    printf("Postorder: ");
    Postorder(t3_root);
    
    DestroyNode(t3_node4);
    DestroyNode(t3_node3);
    DestroyNode(t3_node2);
    DestroyNode(t3_root);
    
    // 테스트 트리 4 -> left skewed tree
    BTreeNode *t4_root = CreateNode(1);
    BTreeNode *t4_node2 = CreateNode(2);
    BTreeNode *t4_node3 = CreateNode(3);
    BTreeNode *t4_node4 = CreateNode(4);
    
    CreateLeftSubtree(t4_root, t4_node2);
    CreateLeftSubtree(t4_node2, t4_node3);
    CreateLeftSubtree(t4_node3, t4_node4);
    
    printf("Test left skewed tree ########################## \n");
    printf("expected output\n");
    printf("Inorder: 4 3 2 1\n");
    printf("Preorder: 1 2 3 4\n");
    printf("Postorder: 4 3 2 1\n");
    /*
            1
           /
          2
         /
        3
       /
      4
    */
    printf("Algorithm output\n");
    printf("Inorder: ");
    Inorder(t4_root);
    
    printf("Preorder: ");
    Preorder(t4_root);
    
    printf("Postorder: ");
    Postorder(t4_root);
    
    DestroyNode(t4_node4);
    DestroyNode(t4_node3);
    DestroyNode(t4_node2);
    DestroyNode(t4_root);
    
    // 테스트 트리 5 -> zigzag tree
    BTreeNode *t5_root = CreateNode(1);
    BTreeNode *t5_node2 = CreateNode(2);
    BTreeNode *t5_node3 = CreateNode(3);
    BTreeNode *t5_node4 = CreateNode(4);
    BTreeNode *t5_node5 = CreateNode(5);
    
    CreateLeftSubtree(t5_root, t5_node2);
    CreateRightSubtree(t5_node2, t5_node3);
    CreateLeftSubtree(t5_node3, t5_node4);
    CreateRightSubtree(t5_node4, t5_node5);
    
    printf("Test zigzag tree ########################## \n");
    printf("expected output\n");
    printf("Inorder: 2 4 5 3 1\n");
    printf("Preorder: 1 2 3 4 5\n");
    printf("Postorder: 5 4 3 2 1\n");
    /*
        1
       /
      2
       \
        3
       /
      4
       \
        5
    */
    printf("Algorithm output\n");
    printf("Inorder: ");
    Inorder(t5_root);
    
    printf("Preorder: ");
    Preorder(t5_root);
    
    printf("Postorder: ");
    Postorder(t5_root);
    
    DestroyNode(t5_node5);
    DestroyNode(t5_node4);
    DestroyNode(t5_node3);
    DestroyNode(t5_node2);
    DestroyNode(t5_root);

    return 0;
}