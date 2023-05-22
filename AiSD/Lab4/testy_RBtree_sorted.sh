#!/bin/bash

m=$1
rm dane/sorted_RBtree.txt

echo "size_n, comp_avg,  comp_maks, reads_avg, reads_maks, h_avg,   h_final   h_maks \n" >> dane/sorted_RBtree.txt

for n in {10000..100000..10000}
do
    echo "przejscie $n"
    for i in $( eval echo {1..$m} )
    do
        ./arg $n | ./rb_t >> dane/sorted_RBtree.txt
    done
done
