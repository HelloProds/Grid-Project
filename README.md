# Knapsack Problem

Algorithm in C for solving the knapsack problem, using OpenMP parallelization. The task was executed on Grid'5000.

### Files

```data/``` - Contains the test data for the knapsack program.

```data/data_generator.py``` - Contains a Python script for generating test data for the knapsack problem.

```results-grid/``` - Contains results for the execution of the knapsack problem on Grid'5000.

```results-local/``` - Contains results for the execution of the knapsack problem on the local machine.

```executor.sh``` - Bash script for executing a program multiple times with the same arguments and storing the results in a text file.

```Makefile``` - Contains commands for compiling, validating and cleaning the knapsack problem executable.

```unbounded_knapsack.c``` - The implementation of the knapsack problem in C.

```.gitignore``` - List of files that should be ignored when pushing to GitHub.

```README.md``` - This file.

### Commands for running

Compile the C program:
```shell
make
```

Delete the object files and the executable:
```shell
make clean
```

Check the program for memory leaks:
```shell
make valgrind knapsack <data-file-name> <number-of-threads>
```

### Commands in Grid'5000

Login to Grid'5000:
```shell
ssh <login>@access.grid5000.fr
```

Login to Grenoble site in Grid'5000:
```shell
ssh grenoble.grid5000.fr
```

Reserve a machine:
```shell
oarsub -I
```

Copy files from local machine to Grenoble site (from CLI of local machine):
```shell
scp <files> <login>@access.grid5000.fr:~/grenoble
```

Copy files from Grenoble site to local machine (from CLI of local machine):
```shell
scp <login>@access.grid5000.fr:~/grenoble/path-to-files ./
```

### Other commands

You can generate test data with a Python script, located in `data` folder. Open the script and modify the knapsack capacity, number of items and file name for the data.

After that, execute the following commands:
```shell
cd data
python data_generator.py
```