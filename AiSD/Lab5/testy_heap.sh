#!/bin/bash

k=$1
rm dane/heapsort_k$k.txt > /dev/null
echo "n przestawienia_heap  porównania_heap" >> dane/heapsort_k$k.txt

for n in {50..1000..50}
do
	for i in $( eval echo {1..$k} )
    do
        ./rtab $n | ./heap >> dane/heapsort_k$k.txt
    done
done
