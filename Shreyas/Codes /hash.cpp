#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum size of the hash table
#define TABLE_SIZE 100

// Structure for storing feedback or query
struct CitizenQuery {
    int citizenID;              // Unique identifier for each citizen
    char feedback[200];         // Feedback or query text
    struct CitizenQuery* next;  // Pointer to the next query (used for chaining in case of collisions)
};

// Hash table definition
struct HashTable {
    struct CitizenQuery* table[TABLE_SIZE];  // Array of pointers to CitizenQuery
};

// Hash function to generate a hash code for a given citizen ID
int hashFunction(int citizenID) {
    return citizenID % TABLE_SIZE;
}

// Function to create a new citizen query
struct CitizenQuery* createQuery(int citizenID, const char* feedback) {
    struct CitizenQuery* newQuery = (struct CitizenQuery*)malloc(sizeof(struct CitizenQuery));
    newQuery->citizenID = citizenID;
    strncpy(newQuery->feedback, feedback, sizeof(newQuery->feedback) - 1);
    newQuery->feedback[sizeof(newQuery->feedback) - 1] = '\0';  // Null-terminate the string
    newQuery->next = NULL;
    return newQuery;
}

// Function to insert a new query into the hash table
void insertQuery(struct HashTable* table, int citizenID, const char* feedback) {
    int index = hashFunction(citizenID);
    struct CitizenQuery* newQuery = createQuery(citizenID, feedback);

    // Handle collision using chaining (linked list)
    if (table->table[index] == NULL) {
        table->table[index] = newQuery;
    } else {
        struct CitizenQuery* temp = table->table[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newQuery;
    }
    printf("Feedback successfully stored for Citizen ID: %d\n", citizenID);
}

// Function to retrieve feedback by citizen ID
struct CitizenQuery* getQuery(struct HashTable* table, int citizenID) {
    int index = hashFunction(citizenID);
    struct CitizenQuery* query = table->table[index];

    // Traverse the linked list at the hashed index
    while (query != NULL) {
        if (query->citizenID == citizenID) {
            return query;  // Found the query
        }
        query = query->next;
    }

    return NULL;  // Citizen ID not found
}

// Function to delete feedback by citizen ID
void deleteQuery(struct HashTable* table, int citizenID) {
    int index = hashFunction(citizenID);
    struct CitizenQuery* query = table->table[index];
    struct CitizenQuery* prev = NULL;

    // Traverse the linked list and delete the query
    while (query != NULL) {
        if (query->citizenID == citizenID) {
            if (prev == NULL) {
                table->table[index] = query->next;  // Delete from the beginning
            } else {
                prev->next = query->next;  // Delete from the middle or end
            }
            free(query);
            printf("Feedback deleted for Citizen ID: %d\n", citizenID);
            return;
        }
        prev = query;
        query = query->next;
    }

    printf("Feedback not found for Citizen ID: %d\n", citizenID);
}

// Function to display the feedback of a specific citizen
void displayQuery(struct CitizenQuery* query) {
    if (query != NULL) {
        printf("Citizen ID: %d\n", query->citizenID);
        printf("Feedback: %s\n", query->feedback);
    } else {
        printf("No feedback found.\n");
    }
}

// Function to initialize the hash table
void initHashTable(struct HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->table[i] = NULL;
    }
}

// Main function to demonstrate the Digital Governance Platform
int main() {
    struct HashTable table;
    initHashTable(&table);

    int choice, citizenID;
    char feedback[200];

    do {
        printf("\n1. Store Citizen Feedback\n");
        printf("2. Retrieve Citizen Feedback\n");
        printf("3. Delete Citizen Feedback\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Citizen ID: ");
                scanf("%d", &citizenID);
                getchar();  // Consume the newline character left by scanf
                printf("Enter Feedback: ");
                fgets(feedback, sizeof(feedback), stdin);
                feedback[strcspn(feedback, "\n")] = '\0';  // Remove trailing newline
                insertQuery(&table, citizenID, feedback);
                break;

            case 2:
                printf("Enter Citizen ID to retrieve feedback: ");
                scanf("%d", &citizenID);
                struct CitizenQuery* query = getQuery(&table, citizenID);
                displayQuery(query);
                break;

            case 3:
                printf("Enter Citizen ID to delete feedback: ");
                scanf("%d", &citizenID);
                deleteQuery(&table, citizenID);
                break;

            case 4:
                printf("Exiting Digital Governance Platform.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
