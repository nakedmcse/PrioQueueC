// Priority Queue test
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 10000000

// Priority Queue Items
typedef struct {
    int priority;
    int value;
} PriorityQueueItem;

// Heap implementation
void swap(PriorityQueueItem *a, PriorityQueueItem *b) {
    PriorityQueueItem temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueueItem arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].priority < arr[smallest].priority)
        smallest = left;

    if (right < n && arr[right].priority < arr[smallest].priority)
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void heapPush(PriorityQueueItem **arr, int *n, int priority, int value) {
    *n += 1;
    *arr = realloc(*arr, *n * sizeof(PriorityQueueItem));
    int i = *n - 1;
    (*arr)[i].priority = priority;
    (*arr)[i].value = value;

    while (i != 0 && (*arr)[(i - 1) / 2].priority > (*arr)[i].priority) {
        swap(&(*arr)[i], &(*arr)[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

PriorityQueueItem heapPop(PriorityQueueItem **arr, int *n) {
    if (*n <= 0)
        return (PriorityQueueItem){.priority = 0, .value = 0};

    PriorityQueueItem root = (*arr)[0];
    (*arr)[0] = (*arr)[*n - 1];
    *n -= 1;
    *arr = realloc(*arr, *n * sizeof(PriorityQueueItem));

    heapify(*arr, *n, 0);

    return root;
}

// Main
int main() {
    srand(time(NULL));
    PriorityQueueItem *simple_prio = NULL;
    int n = 0;

    // Ordering Test
    printf("Simple Priority Queue Enqueued: 1:1,2:1,3:1,4:5,5:9\n");
    heapPush(&simple_prio, &n, -1, 1);
    heapPush(&simple_prio, &n, -1, 2);
    heapPush(&simple_prio, &n, -1, 3);
    heapPush(&simple_prio, &n, -5, 4);
    heapPush(&simple_prio, &n, -9, 5);
    printf("Simple Priority Queue Dequeued: ");
    while (n > 0) {
        PriorityQueueItem item = heapPop(&simple_prio, &n);
        printf("%d ", item.value);
    }
    printf("\n");

    // Speed test for enqueue
    clock_t start_time = clock();
    for (int i = 0; i < RANGE; i++) {
        int priority = 0 - (rand() % 11);
        int value = rand() % RANGE;
        heapPush(&simple_prio, &n, priority, value);
    }
    double elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Simple priority queue enqueue time: %f\n", elapsed);

    // Speed test for dequeue
    start_time = clock();
    int count = 0;
    while (n > 0) {
        heapPop(&simple_prio, &n);
        count++;
    }
    elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Simple priority queue dequeued items: %d\n", count);
    printf("Simple priority queue dequeue time: %f\n", elapsed);

    free(simple_prio);
    return 0;
}