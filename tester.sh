#!/bin/bash

# Compile the program
gcc -Wall -O3 -o runparallel runparallel.c
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Test cases
echo "Running tests..."

# Test 1: No arguments
echo -e "\nTest 1: No arguments"
./runparallel

# Test 2: Invalid number of jobs (0)
echo -e "\nTest 2: Invalid number of jobs (0)"
./runparallel 0 echo

# Test 3: Invalid number of jobs (non-numeric)
echo -e "\nTest 3: Invalid number of jobs (non-numeric)"
./runparallel hello echo

# Test 4: Valid execution with echo
echo -e "\nTest 4: Valid execution with echo"
./runparallel 3 echo Hello World

# Test 5: Larger number of jobs with echo
echo -e "\nTest 5: Larger number of jobs with echo"
./runparallel 10 echo Testing Parallel Execution

# Test 6: Valid execution with sleep
echo -e "\nTest 6: Valid execution with sleep (3 seconds)"
./runparallel 3 sleep 3

# Test 7: Invalid executable
echo -e "\nTest 7: Invalid executable"
./runparallel 3 invalid_executable

# Cleanup
rm -f runparallel
echo -e "\nAll tests completed."
