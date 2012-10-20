#!/bin/bash

# Iterate until we have 200,000 elements
echo "Dynamic Array"
for (( i = 1000; i <= 256000; i = i * 2 ))
    do
    echo $i
    ./prog $i >> dynamic_results.txt
    done

echo "Linked list"
for (( i = 1000; i <= 256000; i = i * 2 ))
    do
    echo $i
    ../1problem/prog $i >> linked_results.txt
    done
