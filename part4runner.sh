#!/bin/bash


for i in 1 to 9 ; do
  ./refstr -refSize 250 -pageLimit 50 -o $( echo "strings"$i".ref" ) w random
  ./refstr -refSize 250 -pageLimit 50 -o $( echo "strings"$i".ref" ) a spatial
  ./refstr -refSize 250 -pageLimit 50 -o $( echo "strings"$i".ref" ) a temporal
  ./refstr -refSize 250 -pageLimit 50 -o $( echo "strings"$i".ref" ) a both
done

for j in 1 to 3; do
  for i in 1 to 9; do
    ./genInputFile $( echo "inputFIFO"$j"-"$i".txt" ) -sim YES -a FIFO -tq 10 -f $( 15*j ) -ref $( echo "strings"$i".ref" ) 
    ./genInputFile $( echo "inputLRU"$j"-"$i".txt" )  -sim YES -a LRU  -tq 10 -f $( 15*j ) -ref $( echo "strings"$i".ref" ) 
    ./genInputFile $( echo "input2C"$j"-"$i".txt" )   -sim YES -a 2C   -tq 10 -f $( 15*j ) -ref $( echo "strings"$i".ref" ) 
  done
done

for k in 1 to 10; do
  for j in 1 to 3; do
    for i in 1 to 9; do
      echo "10x Sim, FIFO Replacement, 15x$j Frames for 50 Pages, 250 Reference Size, 10 Time Quantum
      time ./sim $( echo "inputFIFO"$j"-"$i".txt" ) 
      time ./sim $( echo "inputLRU"$j"-"$i".txt" )
      time ./sim $( echo "input2C"$j"-"$i".txt" )
    done
  done
done


