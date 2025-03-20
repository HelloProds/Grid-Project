#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

typedef struct {
    int weight;
    int value;
} Item;

// Function to solve the unbounded knapsack problem
int unboundedKnapsack(int capacity, int num_items, Item *items) {
    int *dp = (int *)malloc((capacity + 1) * sizeof(int));
    for (int i = 0; i <= capacity; i++) {
        dp[i] = 0;
    }

    #pragma omp parallel for schedule(dynamic)
    for (int w = 1; w <= capacity; w++) {
        int max_val = 0;
        for (int i = 0; i < num_items; i++) {
            int item_weight = items[i].weight;
            int item_value = items[i].value;
            if (item_weight <= w) {
                int temp = dp[w - item_weight] + item_value;
                if (temp > max_val) {
                    max_val = temp;
                }
            }
        }
        dp[w] = max_val;
    }

    int result = dp[capacity];
    free(dp);
    return result;
}

// Function to open file and read knapsack data
void read_knapsack_csv(const char *filename, int *capacity, int *num_items, Item **items) {
    // Open file
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    // Read capacity and number of items
    fscanf(file, "%d", capacity);
    fscanf(file, "%d", num_items);

    // Allocate memory for items
    *items = (Item *)malloc((*num_items) * sizeof(Item));
    if (!*items) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    // Read item weight and value
    for (int i = 0; i < *num_items; i++) {
        fscanf(file, "%d,%d", &((*items)[i].weight), &((*items)[i].value));
    }
    
    // Close file
    fclose(file);
}

// Function to generate random knapsack data
void rand_knapsack_data(char *argv[], int *capacity, int *num_items, Item **items) {
    // Define random seed
    srand(time(NULL));

    // Define capacity and number of items
    *capacity = atoi(argv[1]);
    *num_items = atoi(argv[2]);

    // Define array for items
    *items = (Item *)malloc((*num_items) * sizeof(Item));
    if (!*items) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize limits for max_value and knapsack capacity
    int max_item_weight = *capacity;
    int max_item_value = *capacity * 2;

    // Initialize values and weights (you can modify this part to test different scenarios)
    for (int i = 0; i < *num_items; i++) {
	    (*items)[i].weight = rand() % max_item_weight + 1;    // Random weight between 1 and num_items
        (*items)[i].value = rand() % max_item_value + 1;  // Random value between 1 and 2*num_items
    }
}

int main(int argc, char *argv[]) {
    int capacity, num_items, threads;
    Item *items;

    if (argc == 3) {
        // Read from CSV
	    read_knapsack_csv(argv[1], &capacity, &num_items, &items);

	    // Get amount of threads
	    threads = atoi(argv[2]);
    }
    else if (argc == 4) {
	    // Generate random
	    rand_knapsack_data(argv, &capacity, &num_items, &items);

	    // Get amount of threads
	    threads = atoi(argv[3]);
    }
    else {
        printf("Usage: %s <filename> <threads>\n", argv[0]);
        printf("or\n");
        printf("Usage: %s <knapsack_capacity> <num_items> <threads>\n", argv[0]);
        return 1;
    }

    // Set the number of threads for OpenMP
    omp_set_num_threads(threads);

    // Print the items
    printf("Items:\n");
    for (int i = 0; i < num_items; i++) {
        printf("Item %d: Weight = %d, Value = %d\n", i + 1, items[i].weight, items[i].value);
    }

    // Solve the unbounded knapsack problem
    double start_time = omp_get_wtime();
    int max_value = unboundedKnapsack(capacity, num_items, items);
    double end_time = omp_get_wtime();

    // Print the result
    printf("Maximum value in Knapsack = %d\n", max_value);
    printf("Time taken: %f seconds\n", end_time - start_time);

    // Free allocated memory
    free(items);

    return 0;
}
