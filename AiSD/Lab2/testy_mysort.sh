#!/bin/bash

k=$1
rm dane/mysort_k$1.txt > /dev/null
echo "n przestawienia_mysort porównania_mysort" >> dane/mysort_k$k.txt

for n in {50..1000..50}
do
	for i in $( eval echo {1..$k} )
    do
        ./randomtab $n | ./mysort >> dane/mysort_k$k.txt
    done
done