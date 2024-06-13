#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int order_number;
    int arrival_time;
    int duration;
} Order;


typedef struct {
    Order* order;
    int completion_time;
} MinHeapNode;


typedef struct {
    MinHeapNode* heap_array;
    int size;
} MinHeap;


void swapMinHeapNodes(MinHeapNode* a, MinHeapNode* b) {
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}


void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && (minHeap->heap_array[left].completion_time < minHeap->heap_array[smallest].completion_time ||
                                 (minHeap->heap_array[left].completion_time == minHeap->heap_array[smallest].completion_time &&
                                  minHeap->heap_array[left].order->order_number < minHeap->heap_array[smallest].order->order_number)))
        smallest = left;

    if (right < minHeap->size && (minHeap->heap_array[right].completion_time < minHeap->heap_array[smallest].completion_time ||
                                  (minHeap->heap_array[right].completion_time == minHeap->heap_array[smallest].completion_time &&
                                   minHeap->heap_array[right].order->order_number < minHeap->heap_array[smallest].order->order_number)))
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNodes(&minHeap->heap_array[idx], &minHeap->heap_array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

MinHeap* buildMinHeap(Order* orders, int n) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = n;
    minHeap->heap_array = (MinHeapNode*)malloc(n * sizeof(MinHeapNode));
int i;
    for ( i = 0; i < n; i++) {
        minHeap->heap_array[i].order = &orders[i];
        minHeap->heap_array[i].completion_time = orders[i].arrival_time + orders[i].duration;
    }

    for (i = n / 2 - 1; i >= 0; i--)
        minHeapify(minHeap, i);

    return minHeap;
}


MinHeapNode extractMin(MinHeap* minHeap) {
    MinHeapNode root = minHeap->heap_array[0];
    minHeap->heap_array[0] = minHeap->heap_array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return root;
}


void printOrderCompletion(Order* orders, int n) {
    MinHeap* minHeap = buildMinHeap(orders, n);

    printf("Order of completion:\n");
    while (minHeap->size > 0) {
        MinHeapNode root = extractMin(minHeap);
        printf("Order %d completed at time %d\n", root.order->order_number, root.completion_time);
    }

    free(minHeap->heap_array);
    free(minHeap);
}


int main() {
    int n,i;
    printf("Enter the number of orders: ");
    scanf("%d", &n);

    Order orders[n];

    
    for (i = 0; i < n; i++) {
        printf("Enter order number, arrival time and duration for order %d: ", i + 1);
        scanf("%d %d %d", &orders[i].order_number, &orders[i].arrival_time, &orders[i].duration);
    }

    // Printing the order of completion
    printOrderCompletion(orders, n);

    return 0;
}