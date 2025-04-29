#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pb4.h"


/* #############################################
    Stack Structure
################################################# */
void InitStack(Stack *s) { s->top = -1; }
bool IsSFull(const Stack *s) { return s->top == MAX_STACK - 1; }
bool IsSEmpty(const Stack *s) { return s->top == -1; }
void Push(Stack *s, int item) {
    if (IsSFull(s)) { fprintf(stderr, "Stack full error\n"); exit(EXIT_FAILURE); }
    s->items[++s->top] = item;
}
int Pop(Stack *s) {
    if (IsSEmpty(s)) { fprintf(stderr, "Stack empty error\n"); exit(EXIT_FAILURE); }
    return s->items[s->top--];
}
int SPeek(const Stack *s) {
    if (IsSEmpty(s)) { fprintf(stderr, "Stack empty error\n"); exit(EXIT_FAILURE); }
    return s->items[s->top];
}

/* #############################################
    Queue Structure
################################################# */
void InitQueue(Queue *q) { q->front = q->rear = 0; }
bool IsQFull(const Queue *q) { return (q->rear + 1) % MAX_QUEUE == q->front; }
bool IsQEmpty(const Queue *q) { return q->front == q->rear; }
void EnQueue(Queue *q, int item) {
    if (IsQFull(q)) { fprintf(stderr, "Queue full error\n"); exit(EXIT_FAILURE); }
    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % MAX_QUEUE;
}
int DeQueue(Queue *q) {
    if (IsQEmpty(q)) { fprintf(stderr, "Queue empty error\n"); exit(EXIT_FAILURE); }
    int item = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    return item;
}
int QPeek(const Queue *q) {
    if (IsQEmpty(q)) { fprintf(stderr, "Queue empty error\n"); exit(EXIT_FAILURE); }
    return q->items[q->front];
}

/* #############################################
    Graph Structure
################################################# */
void CreateGraph(Graph *g, int num_vertices) {
    g->num = num_vertices;
    g->heads = (GNode **)malloc(sizeof(GNode *) * num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        g->heads[i] = (GNode *)malloc(sizeof(GNode));
        g->heads[i]->next = NULL;
    }
}

void DestroyGraph(Graph *g) {
    for (int i = 0; i < g->num; ++i) {
        GNode *cur = g->heads[i];
        while (cur) { GNode *tmp = cur; cur = cur->next; free(tmp); }
    }
    free(g->heads);
}

void AddEdge(Graph *g, int src, int dest) {
    GNode *new1 = (GNode *)malloc(sizeof(GNode));
    new1->id = dest; new1->next = NULL;
    GNode *cur = g->heads[src];
    while (cur->next) cur = cur->next;
    cur->next = new1;

    GNode *new2 = (GNode *)malloc(sizeof(GNode));
    new2->id = src; new2->next = NULL;
    cur = g->heads[dest];
    while (cur->next) cur = cur->next;
    cur->next = new2;
}

void PrintGraph(const Graph *g) {
    for (int i = 0; i < g->num; ++i) {
        printf("%d:", i);
        for (GNode *cur = g->heads[i]->next; cur; cur = cur->next) printf(" %d", cur->id);
        printf("\n");
    }
}

/* #############################################
    DFS (Using Stack)
################################################# */
void DFS(Graph *g) {
    Stack st; InitStack(&st);
    bool *visited = (bool *)malloc(sizeof(bool) * g->num);
    for (int i = 0; i < g->num; ++i) visited[i] = false;

    Push(&st, 0);
    while (!IsSEmpty(&st)) {
        int vtx = SPeek(&st); Pop(&st);
        if (visited[vtx]) continue;
        visited[vtx] = true; printf("%d ", vtx);

        for (GNode *cur = g->heads[vtx]->next; cur; cur = cur->next) {
            if (!visited[cur->id]) Push(&st, cur->id);
        }
    }
    free(visited);
    printf("\n");
}

/* #############################################
    BFS (Using Queue)
################################################# */
void BFS(Graph *g) {
    Queue q; InitQueue(&q);
    bool *visited = (bool *)malloc(sizeof(bool) * g->num);
    for (int i = 0; i < g->num; ++i) visited[i] = false;

    EnQueue(&q, 0);
    while (!IsQEmpty(&q)) {
        int vtx = QPeek(&q); DeQueue(&q);
        if (visited[vtx]) continue;
        visited[vtx] = true; printf("%d ", vtx);

        for (GNode *cur = g->heads[vtx]->next; cur; cur = cur->next) {
            if (!visited[cur->id]) EnQueue(&q, cur->id);
        }
    }
    free(visited);
    printf("\n");
}


void run_case(const char *title, Graph *g) {
    printf("\n==== %s ====\n", title);
    PrintGraph(g);
    printf("DFS: "); 
    DFS(g);
    printf("BFS: "); 
    BFS(g);
}


int main(void) {
    Graph g1;
    CreateGraph(&g1, 6);
    AddEdge(&g1, 0, 1);
    AddEdge(&g1, 0, 2);
    AddEdge(&g1, 1, 3);
    AddEdge(&g1, 1, 4);
    AddEdge(&g1, 2, 5);
    
    Graph g2;
    CreateGraph(&g2, 10);
    AddEdge(&g2, 0, 1);
    AddEdge(&g2, 0, 2);
    AddEdge(&g2, 1, 3);
    AddEdge(&g2, 1, 4);
    AddEdge(&g2, 2, 5);
    AddEdge(&g2, 2, 6);
    AddEdge(&g2, 3, 7);
    AddEdge(&g2, 3, 8);
    AddEdge(&g2, 4, 9);

    Graph g3;
    CreateGraph(&g3, 5);
    AddEdge(&g3, 0, 1);
    AddEdge(&g3, 0, 2);
    AddEdge(&g3, 0, 3);
    AddEdge(&g3, 0, 4);
    AddEdge(&g3, 1, 2);
    AddEdge(&g3, 1, 3);
    AddEdge(&g3, 1, 4);
    AddEdge(&g3, 2, 3);
    AddEdge(&g3, 2, 4);
    AddEdge(&g3, 3, 4);

    Graph g4;
    CreateGraph(&g4, 8);
    AddEdge(&g4, 0, 1);
    AddEdge(&g4, 1, 2);
    AddEdge(&g4, 3, 4);
    AddEdge(&g4, 6, 7);

    Graph g5;
    CreateGraph(&g5, 7);
    AddEdge(&g5, 0, 1);
    AddEdge(&g5, 0, 2);
    AddEdge(&g5, 1, 3);
    AddEdge(&g5, 2, 4);
    AddEdge(&g5, 2, 5);
    AddEdge(&g5, 5, 6);

    run_case("Test_Case 1", &g1);
    printf("Test_Case 1 정답:\n");
    printf("BFS answer: 0 1 2 3 4 5\n");
    printf("DFS answer: 0 2 5 1 4 3\n");

    run_case("Test_Case 2", &g2);
    printf("\nTest_Case 2 정답:\n");
    printf("BFS answer: 0 1 2 3 4 5 6 7 8 9\n");
    printf("DFS answer: 0 2 6 5 1 4 9 3 8 7\n");

    run_case("Test_Case 3", &g3);
    printf("\nTest_Case 3 정답:\n");
    printf("BFS answer: 0 1 2 3 4\n");
    printf("DFS answer: 0 4 3 2 1\n");

    run_case("Test_Case 4", &g4);
    printf("Test_Case 4 정답:\n");
    printf("BFS answer: 0 1 2\n");
    printf("DFS answer: 0 1 2\n");
    
    run_case("Test_Case 5", &g5);
    printf("Test_Case 5 정답:\n");
    printf("BFS answer: 0 1 2 3 4 5 6\n");
    printf("DFS answer: 0 1 3 2 4 5 6\n");
    
    DestroyGraph(&g1); 
    DestroyGraph(&g2); 
    DestroyGraph(&g3); 
    DestroyGraph(&g4);
    DestroyGraph(&g5);
    return 0;
}
