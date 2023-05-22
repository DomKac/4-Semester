#!/bin/bash

k=$1
rm dane/insort_k$1.txt > /dev/null
echo "n przestawienia_insort porównania_insort" >> dane/insort_k$k.txt

for n in {50..1000..50}
do
	for i in $( eval echo {1..$k} )
    do
        ./randomtab $n | ./insort >> dane/insort_k$k.txt
    done
done