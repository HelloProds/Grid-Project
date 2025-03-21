#!/bin/bash
# Number of times the program will be executed
ITERATIONS=30
# The executable
EXECUTABLE=$1
# The path to the test data
FILE_PATH=$2
# The number of threads used for parallelization
THREADS=$3
# Extract the test data file name from the path
FILE_NAME=$(basename "$FILE_PATH" | cut -d. -f1)
# Define file path for results
RESULTS_PATH=$(printf "./results/results_%s_threads_%s.txt" "$FILE_NAME" "$THREADS")
# Execute the program
for i in $(seq 1 $ITERATIONS) ; do
 ./$EXECUTABLE $FILE_PATH $THREADS >> $RESULTS_PATH
done