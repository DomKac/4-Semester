#!/bin/bash

k=$1
rm dane/merge_k$1.txt > /dev/null
echo "n przestawienia_merge porównania_merge" >> dane/merge_k$k.txt

for n in {50..1000..50}
do
	for i in $( eval echo {1..$k} )
    do
        ./randomtab $n | ./merge >> dane/merge_k$k.txt
    done
done