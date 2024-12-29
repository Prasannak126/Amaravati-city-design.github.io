#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 16
#define P 0.5 // Probability to promote a node to a higher level

// Skip List Node
typedef struct node {
    int route_id;          // Unique ID for the route
    int travel_time;       // Travel time (or distance)
    struct node **forward; // Array of forward pointers
} node_t;

// Skip List structure
typedef struct skiplist {
    int level;        // Current level of the skip list
    node_t *header;   // Header node
} skiplist_t;

// Create a new node
node_t* create_node(int level, int route_id, int travel_time) {
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    new_node->route_id = route_id;
    new_node->travel_time = travel_time;
    new_node->forward = (node_t**) malloc(sizeof(node_t*) * (level + 1));
    for (int i = 0; i <= level; i++) {
        new_node->forward[i] = NULL;
    }
    return new_node;
}

// Create a skip list
skiplist_t* create_skiplist() {
    skiplist_t *list = (skiplist_t*) malloc(sizeof(skiplist_t));
    list->level = 0;
    list->header = create_node(MAX_LEVEL, -1, -1); // -1 is a sentinel value for header node
    return list;
}

// Random level generator
int random_level() {
    int level = 0;
    while ((rand() / (double)RAND_MAX) < P && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// Insert a new route into the skip list
void insert(skiplist_t *list, int route_id, int travel_time) {
    node_t *update[MAX_LEVEL + 1];
    node_t *current = list->header;

    // Find the position to insert
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->route_id < route_id) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    // Check if the route already exists and update it if so
    current = current->forward[0];
    if (current != NULL && current->route_id == route_id) {
        current->travel_time = travel_time;
        return;
    }

    // Create a new node
    int new_level = random_level();
    if (new_level > list->level) {
        for (int i = list->level + 1; i <= new_level; i++) {
            update[i] = list->header;
        }
        list->level = new_level;
    }

    node_t *new_node = create_node(new_level, route_id, travel_time);
    for (int i = 0; i <= new_level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
}

// Search for a route by route_id
node_t* search(skiplist_t *list, int route_id) {
    node_t *current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->route_id < route_id) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != NULL && current->route_id == route_id) {
        return current;
    }
    return NULL;
}

// Print the skip list (for debugging)
void print_list(skiplist_t *list) {
    printf("Skip List: \n");
    for (int i = 0; i <= list->level; i++) {
        node_t *current = list->header->forward[i];
        printf("Level %d: ", i);
        while (current != NULL) {
            printf("(%d, %d) ", current->route_id, current->travel_time);
            current = current->forward[i];
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));  // Seed for random level generation
    
    skiplist_t *list = create_skiplist();
    
    // Insert routes with travel times
    insert(list, 101, 30);  // Route 101 with 30 minutes travel time
    insert(list, 202, 20);  // Route 202 with 20 minutes travel time
    insert(list, 303, 25);  // Route 303 with 25 minutes travel time
    insert(list, 404, 15);  // Route 404 with 15 minutes travel time
    
    // Print the skip list structure
    print_list(list);
    
    // Search for a specific route
    int route_id = 202;
    node_t *route = search(list, route_id);
    if (route != NULL) {
        printf("\nFound route %d with travel time %d minutes\n", route->route_id, route->travel_time);
    } else {
        printf("\nRoute %d not found\n", route_id);
    }

    // Update a route's travel time
    insert(list, 202, 18);  // Update Route 202's travel time to 18 minutes
    
    // Print the updated skip list
    print_list(list);
    
    return 0;
}
