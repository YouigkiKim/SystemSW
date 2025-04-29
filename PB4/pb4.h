



// pb4.h — Graph ADT & traversal prototypes
#ifndef PB4_H
#define PB4_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* -------------------- Constants -------------------- */
#define MAX_STACK 100
#define MAX_QUEUE 100

/* -------------------- Graph ------------------------ */

typedef struct _GNode {
    int id;
    struct _GNode *next;
} GNode;

typedef struct {
    int num;          /* number of vertices */
    GNode **heads;    /* adjacency list heads (dummy node) */
} Graph;

/* -------------------- Stack (for DFS) -------------- */
typedef struct {
    int items[MAX_STACK];
    int top;
} Stack;

/* -------------------- Queue (for BFS) -------------- */
typedef struct {
    int items[MAX_QUEUE];
    int front;
    int rear;
} Queue;

/* -------------------- Stack API -------------------- */
void InitStack(Stack *s);
bool IsSFull(const Stack *s);
bool IsSEmpty(const Stack *s);
void Push(Stack *s, int item);
int  Pop(Stack *s);
int  SPeek(const Stack *s);

/* -------------------- Queue API -------------------- */
void InitQueue(Queue *q);
bool IsQFull(const Queue *q);
bool IsQEmpty(const Queue *q);
void EnQueue(Queue *q, int item);
int  DeQueue(Queue *q);
int  QPeek(const Queue *q);

/* -------------------- Graph API -------------------- */
void CreateGraph(Graph *g, int num_vertices);
void DestroyGraph(Graph *g);
void AddEdge(Graph *g, int src, int dest);    /* undirected */
void PrintGraph(const Graph *g);

/* -------------------- Traversal -------------------- */
void DFS(Graph *g);
void BFS(Graph *g);

#endif /* PB4_H */