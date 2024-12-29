#include <stdio.h>
#include <stdlib.h>

#define MAX_TRAINS 100

// Structure to represent a train
typedef struct {
    int trainNumber;
    int departureTime;  // Time in minutes (e.g., 135 for 2:15 PM)
} Train;

// Function to swap two trains
void swap(Train* a, Train* b) {
    Train temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the heap property (Max Heap)
void heapify(Train arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check if left child exists and is greater than root
    if (left < n && arr[left].departureTime > arr[largest].departureTime)
        largest = left;

    // Check if right child exists and is greater than root
    if (right < n && arr[right].departureTime > arr[largest].departureTime)
        largest = right;

    // If largest is not root, swap and heapify the affected subtree
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to perform heap sort
void heapSort(Train arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to the end
        swap(&arr[0], &arr[i]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Function to print the train schedule
void printSchedule(Train arr[], int n) {
    printf("Train Number\tDeparture Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d:%02d\n", arr[i].trainNumber, arr[i].departureTime / 60, arr[i].departureTime % 60);
    }
}

int main() {
    int n;

    // Input number of trains
    printf("Enter the number of trains: ");
    scanf("%d", &n);

    // Input train details (train number and departure time)
    Train trains[n];
    for (int i = 0; i < n; i++) {
        printf("Enter train number and departure time (in minutes from midnight): ");
        scanf("%d %d", &trains[i].trainNumber, &trains[i].departureTime);
    }

    // Sort the trains using Heap Sort (based on departure time)
    heapSort(trains, n);

    // Print the sorted train schedule
    printf("\nOptimized Train Schedule:\n");
    printSchedule(trains, n);

    return 0;
}
