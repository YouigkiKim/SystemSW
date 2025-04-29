#include "pb3.h"


int main(){
    // Test Case 1: Basic priority queue operations
    PQueue pq1;
    InitPQueue(&pq1);
    
    printf("Test Case 1: Basic operations\n");
    printf("Enqueue order: A(1), B(2), C(3)\n");
    Enqueue(&pq1, 'A', 1);
    Enqueue(&pq1, 'B', 2);
    Enqueue(&pq1, 'C', 3);
    
    printf("Answer: C, B, A\n");
    printf("Dequeue order: ");
    printf("%c, ", Dequeue(&pq1));  // Should print C (highest priority)
    printf("%c, ", Dequeue(&pq1));  // Should print B
    printf("%c\n", Dequeue(&pq1));  // Should print A
    printf("\n");
    
    // Test Case 2: Same priority elements
    PQueue pq2;
    InitPQueue(&pq2);
    
    printf("Test Case 2: Same priority elements\n");
    printf("Enqueue order: X(5), Y(5), Z(5)\n");
    Enqueue(&pq2, 'X', 5);
    Enqueue(&pq2, 'Y', 5);
    Enqueue(&pq2, 'Z', 5);
    
    printf("Answer: X, Y, Z\n");
    printf("Dequeue order: ");
    printf("%c, ", Dequeue(&pq2));
    printf("%c, ", Dequeue(&pq2));
    printf("%c\n", Dequeue(&pq2));
    printf("\n");
    
    // Test Case 3: Reverse order insertion
    PQueue pq3;
    InitPQueue(&pq3);
    
    printf("Test Case 3: Reverse order insertion\n");
    printf("Enqueue order: P(10), Q(8), R(6), S(4), T(2)\n");
    Enqueue(&pq3, 'P', 10);
    Enqueue(&pq3, 'Q', 8);
    Enqueue(&pq3, 'R', 6);
    Enqueue(&pq3, 'S', 4);
    Enqueue(&pq3, 'T', 2);
    
    printf("Answer: P, Q, R, S, T\n");
    printf("Dequeue order: ");
    printf("%c, ", Dequeue(&pq3));  // Should print P (highest priority)
    printf("%c, ", Dequeue(&pq3));  // Should print Q
    printf("%c, ", Dequeue(&pq3));  // Should print R
    printf("%c, ", Dequeue(&pq3));  // Should print S
    printf("%c\n", Dequeue(&pq3));  // Should print T
    printf("\n");
    
    // Test Case 4: Mixed priority insertion
    PQueue pq4;
    InitPQueue(&pq4);
    
    printf("Test Case 4: Mixed priority insertion\n");
    printf("Enqueue order: E(3), D(7), C(1), B(9), A(5)\n");
    Enqueue(&pq4, 'E', 3);
    Enqueue(&pq4, 'D', 7);
    Enqueue(&pq4, 'C', 1);
    Enqueue(&pq4, 'B', 9);
    Enqueue(&pq4, 'A', 5);
    
    printf("Answer: B, D, A, E, C\n");
    printf("Dequeue order: ");
    printf("%c, ", Dequeue(&pq4));  // Should print B (highest priority)
    printf("%c, ", Dequeue(&pq4));  // Should print D
    printf("%c, ", Dequeue(&pq4));  // Should print A
    printf("%c, ", Dequeue(&pq4));  // Should print E
    printf("%c\n", Dequeue(&pq4));  // Should print C
    printf("\n");
    
    // Test Case 5: Longer sequence with varied priorities
    PQueue pq5;
    InitPQueue(&pq5);
    
    printf("Test Case 5: Longer sequence with varied priorities\n");
    printf("Enqueue order: M(12), N(5), O(8), P(20), Q(3), R(15), S(7), T(10), U(1), V(18)\n");
    Enqueue(&pq5, 'M', 12);
    Enqueue(&pq5, 'N', 5);
    Enqueue(&pq5, 'O', 8);
    Enqueue(&pq5, 'P', 20);
    Enqueue(&pq5, 'Q', 3);
    Enqueue(&pq5, 'R', 15);
    Enqueue(&pq5, 'S', 7);
    Enqueue(&pq5, 'T', 10);
    Enqueue(&pq5, 'U', 1);
    Enqueue(&pq5, 'V', 18);
    
    printf("Answer: P, V, R, M, T, O, S, N, Q, U\n");
    printf("Dequeue order: ");
    printf("%c, ", Dequeue(&pq5));  // Should print P (highest priority)
    printf("%c, ", Dequeue(&pq5));  // Should print V
    printf("%c, ", Dequeue(&pq5));  // Should print R
    printf("%c, ", Dequeue(&pq5));  // Should print M
    printf("%c, ", Dequeue(&pq5));  // Should print T
    printf("%c, ", Dequeue(&pq5));  // Should print O
    printf("%c, ", Dequeue(&pq5));  // Should print S
    printf("%c, ", Dequeue(&pq5));  // Should print N
    printf("%c, ", Dequeue(&pq5));  // Should print Q
    printf("%c\n", Dequeue(&pq5));  // Should print U
    printf("\n");

    return 0;
}