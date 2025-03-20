CC = gcc
CFLAGS = -fopenmp -g
TARGET = knapsack

all: $(TARGET)

$(TARGET): knapsack.o
	$(CC) $(CFLAGS) knapsack.o -o $(TARGET)

knapsack.o: unbounded_knapsack.c
	$(CC) $(CFLAGS) -c unbounded_knapsack.c -o knapsack.o

clean:
	rm -f $(TARGET) knapsack.o

valgrind:
	valgrind -s --leak-check=full --show-leak-kinds=all ./$(TARGET) $(ARGS)