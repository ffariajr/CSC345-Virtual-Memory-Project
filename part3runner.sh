#!/bin/bash


for i in 1 to 8 ; do
  ./refstr -refSize $( 100 * $i * $i ) -pageLimit 50 -o $( echo "str-1l-"$i"s.ref" ) w random
  ./refstr -refSize $( 100 * $i * $i ) -pageLimit 50 -o $( echo "str-2l-"$i"s.ref" ) a spatial
  ./refstr -refSize $( 100 * $i * $i ) -pageLimit 50 -o $( echo "str-3l-"$i"s.ref" ) a temporal
  ./refstr -refSize $( 100 * $i * $i ) -pageLimit 50 -o $( echo "str-4l-"$i"s.ref" ) a both
done

for k in 1 to 3; do
  for j in 1 to 4; do
    for i in 1 to 8; do
      ./genInputFile $( echo "in-1a-"$k"f-"$j"l-"$i"s.txt" ) -sim NO -a FIFO -tq 10 -f $( 15 * $k ) -ref $( echo "str-"$j"l-"$i"s.ref" ) 
      ./genInputFile $( echo "in-2a-"$k"f-"$j"l-"$i"s.txt" ) -sim NO -a LRU  -tq 10 -f $( 15 * $k ) -ref $( echo "str-"$j"l-"$i"s.ref" ) 
      ./genInputFile $( echo "in-3a-"$k"f-"$j"l-"$i"s.txt" ) -sim NO -a 2C   -tq 10 -f $( 15 * $k ) -ref $( echo "str-"$j"l-"$i"s.ref" ) 
    done
  done
done

for m in 1 to 10; do
  for l in 1 to 3; do
    for k in 1 to 3; do
      for j in 1 to 4; do
        for i in 1 to 8; do
          echo "Sim: $m"
          echo "Replacement: $l"
          echo "Frames: $( 15 * $k )"
          echo "Locality: $j"
          echo "References: $( $i * $i * 100 )"
          echo "Pages: 50"
          echo "Time Quantum: 10"
          echo "Locality: $j"
          time ./sim $( echo "in-"$l"a-"$k"f-"$j"l-v"$i".txt" ) 
        done
      done
    done
  done
done
