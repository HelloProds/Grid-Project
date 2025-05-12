import csv
import random

# Parameters
knapsack_capacity = 50
num_items = 10

# Generate items with weight and value within the specified ranges
items = []
for _ in range(num_items):
    # Weight between 1 and capacity
    weight = random.randint(1, knapsack_capacity)
    # Value between weight and 2 * weight - 1
    value = random.randint(weight, 2 * weight - 1)
    items.append([weight, value])

# Sort the items by weight
sorted_items = sorted(items, key=lambda x: x[0])

# Define the file path for the sorted CSV
file_path = 'test_data_1.csv'

# Write the sorted data to a CSV file
with open(file_path, mode='w', newline='') as file:
    writer = csv.writer(file)
    # First row with knapsack capacity and number of items
    writer.writerow([knapsack_capacity])
    writer.writerow([num_items])
    # Write item weights and values
    for item in sorted_items:
        writer.writerow(item)

print(f"Data has been written to {file_path}")