#!/bin/bash


k=$1
rm dane/quick_k$1.txt > /dev/null
echo "n przestawienia_quick porównania_quick" >> dane/quick_k$k.txt

for n in {50..1000..50}
do
	for i in $( eval echo {1..$k} )
    do
        ./randomtab $n | ./quick >> dane/quick_k$k.txt
    done
done