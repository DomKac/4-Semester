#!/bin/bash

k=$1
rm dane/lcs_k$k.txt > /dev/null
echo "n wpisania_do_tablic_c_lub_b  porównania  długość_nwp" >> dane/lcs_k$k.txt

for n in {1000..5000..1000}
do
	for i in $( eval echo {1..$k} )
    do
        ./rrg $n | ./nwp >> dane/lcs_k$k.txt
    done
done
