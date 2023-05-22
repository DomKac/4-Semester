#!/bin/bash

k=$1
rm dane/desc_dualpivot_k$1.txt > /dev/null
echo "n przestawienia_dpqs porównania_dpqs" >> dane/desc_dualpivot_k$k.txt

for n in {50..1000..50}
do
	for i in $( eval echo {1..$k} )
    do
        ./dectab $n | ./dualpivot >> dane/desc_dualpivot_k$k.txt
    done
done