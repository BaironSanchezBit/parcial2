#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PROCESSES 10
#define NUM_QUEUES 3

typedef struct {
    int id;
    int burst_time;
    int priority;
} Process;

typedef struct {
    Process *queue[MAX_PROCESSES];
    int front, rear;
} Queue;

void initializeQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return (q->front == -1);
}

void enqueue(Queue *q, Process *process) {
    if (q->rear == MAX_PROCESSES - 1) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->queue[++q->rear] = process;
}

Process* dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return NULL;
    }
    Process *temp = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return temp;
}

void adjust_priority(Process *p) {
    if (p->burst_time > 10) {
        p->priority = (p->priority + 1) % NUM_QUEUES;
    } else {
        p->priority = (p->priority - 1 + NUM_QUEUES) % NUM_QUEUES;
    }
}

Queue queues[NUM_QUEUES];

int main() {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    initializeQueue(&queues[0]);
    initializeQueue(&queues[1]);
    initializeQueue(&queues[2]);

    Process p1 = {1, 15, 0}, p2 = {2, 8, 0}, p3 = {3, 12, 0};
    enqueue(&queues[p1.priority], &p1);
    enqueue(&queues[p2.priority], &p2);
    enqueue(&queues[p3.priority], &p3);

    for (int i = 0; i < NUM_QUEUES; i++) {
        while (!isEmpty(&queues[i])) {
            Process *proc = dequeue(&queues[i]);
	    printf("Ejecutando proceso %d con tiempo de ráfaga %d desde la cola %d\n", proc->id, proc->burst_time, i);
            adjust_priority(proc);
            enqueue(&queues[proc->priority], proc);
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de Ejecucion: %f segundos\n", cpu_time_used);

    return 0;
}