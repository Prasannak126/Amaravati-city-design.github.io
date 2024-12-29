#include <stdio.h>
#include <stdlib.h>

// Structure to represent the Fenwick Tree (Binary Indexed Tree)
struct FenwickTree {
    int* tree;  // Array representing the Fenwick Tree
    int n;      // Size of the tree (number of regions or sensors)
};

// Function to create and initialize the Fenwick Tree
struct FenwickTree* createFenwickTree(int n) {
    struct FenwickTree* fenwick = (struct FenwickTree*)malloc(sizeof(struct FenwickTree));
    fenwick->n = n;
    fenwick->tree = (int*)calloc(n + 1, sizeof(int)); // Initialize tree with 0s (1-based indexing)
    return fenwick;
}

// Function to update the Fenwick Tree at a specific index with a given value
void update(struct FenwickTree* fenwick, int index, int value) {
    while (index <= fenwick->n) {
        fenwick->tree[index] += value;
        index += index & -index;  // Move to the next index in the Fenwick Tree
    }
}

// Function to get the sum of values in the Fenwick Tree from index 1 to the given index
int query(struct FenwickTree* fenwick, int index) {
    int sum = 0;
    while (index > 0) {
        sum += fenwick->tree[index];
        index -= index & -index;  // Move to the parent index
    }
    return sum;
}

// Function to get the range sum from index l to r
int rangeQuery(struct FenwickTree* fenwick, int l, int r) {
    return query(fenwick, r) - query(fenwick, l - 1);
}

// Function to print the Fenwick Tree for debugging purposes
void printFenwickTree(struct FenwickTree* fenwick) {
    printf("Fenwick Tree: ");
    for (int i = 1; i <= fenwick->n; i++) {
        printf("%d ", fenwick->tree[i]);
    }
    printf("\n");
}

// Main function
int main() {
    int n, sensorIndex, airQualityReading, choice;

    printf("Enter the number of air quality monitoring regions (sensors): ");
    scanf("%d", &n);

    // Create Fenwick Tree to store air quality data
    struct FenwickTree* fenwick = createFenwickTree(n);

    // Interactive menu for updating and querying air quality data
    do {
        printf("\n1. Update air quality data\n");
        printf("2. Query air quality data for a region\n");
        printf("3. Query range of air quality data (for pollution trend)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the region index (1 to %d): ", n);
                scanf("%d", &sensorIndex);
                printf("Enter the air quality reading for region %d: ", sensorIndex);
                scanf("%d", &airQualityReading);
                // Update the Fenwick Tree with the new air quality reading
                update(fenwick, sensorIndex, airQualityReading);
                printf("Updated air quality data for region %d.\n", sensorIndex);
                break;

            case 2:
                printf("Enter the region index (1 to %d): ", n);
                scanf("%d", &sensorIndex);
                // Query the air quality reading for the specified region
                airQualityReading = rangeQuery(fenwick, sensorIndex, sensorIndex);
                printf("Air quality reading for region %d: %d\n", sensorIndex, airQualityReading);
                break;

            case 3:
                int startRegion, endRegion;
                printf("Enter the start region index (1 to %d): ", n);
                scanf("%d", &startRegion);
                printf("Enter the end region index (1 to %d): ", n);
                scanf("%d", &endRegion);
                // Query the sum of air quality readings for a range of regions
                airQualityReading = rangeQuery(fenwick, startRegion, endRegion);
                printf("Total air quality data for regions %d to %d: %d\n", startRegion, endRegion, airQualityReading);
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Free the allocated memory for the Fenwick Tree
    free(fenwick->tree);
    free(fenwick);

    return 0;
}
