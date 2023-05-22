#!/bin/bash

k=$1
rm dane/heap_priority_k$k.txt > /dev/null
echo "n przestawienia  porównania" >> dane/heap_priority_k$k.txt

for n in {10000..100000..10000}
do
	for i in $( eval echo {1..$k} )
    do
        ./rtab $n | ./heap_p >> dane/heap_priority_k$k.txt
    done
done
