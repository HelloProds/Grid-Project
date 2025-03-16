#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to solve the unbounded knapsack problem
int unboundedKnapsack(int W, int n, int *val, int *wt) {
    int *dp = (int *)malloc((W + 1) * sizeof(int));
    for (int i = 0; i <= W; i++) {
        dp[i] = 0;
    }

    #pragma omp parallel for schedule(dynamic)
    for (int w = 1; w <= W; w++) {
        int max_val = 0;
        for (int i = 0; i < n; i++) {
            if (wt[i] <= w) {
                int temp = dp[w - wt[i]] + val[i];
                if (temp > max_val) {
                    max_val = temp;
                }
            }
        }
        dp[w] = max_val;
    }

    int result = dp[W];
    free(dp);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <knapsack_capacity> <num_items> <threads>\n", argv[0]);
        return 1;
    }

    int W = atoi(argv[1]);  // Knapsack capacity
    int n = atoi(argv[2]);  // Number of items
    int threads = atoi(argv[3]);  // Number of threads

    // Set the number of threads for OpenMP
    omp_set_num_threads(threads);

    // Allocate memory for values and weights
    int *val = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));

    // Initialize values and weights (you can modify this part to test different scenarios)
    for (int i = 0; i < n; i++) {
        val[i] = rand() % 100 + 1;  // Random value between 1 and 100
        wt[i] = rand() % 50 + 1;    // Random weight between 1 and 50
    }

    // Print the items (optional)
    printf("Items:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: Value = %d, Weight = %d\n", i + 1, val[i], wt[i]);
    }

    // Solve the unbounded knapsack problem
    double start_time = omp_get_wtime();
    int max_value = unboundedKnapsack(W, n, val, wt);
    double end_time = omp_get_wtime();

    // Print the result
    printf("Maximum value in Knapsack = %d\n", max_value);
    printf("Time taken: %f seconds\n", end_time - start_time);

    // Free allocated memory
    free(val);
    free(wt);

    return 0;
}