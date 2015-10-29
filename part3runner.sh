#!/bin/bash


for i in $(seq 1 8) ; do
  ./refstr -refSize $(( 100 * $i * $i )) -pageLimit 50 -o $( echo "testing/str-1l-"$i"s.ref" ) w random
  ./refstr -refSize $(( 100 * $i * $i )) -pageLimit 50 -o $( echo "testing/str-2l-"$i"s.ref" ) w spatial
  ./refstr -refSize $(( 100 * $i * $i )) -pageLimit 50 -o $( echo "testing/str-3l-"$i"s.ref" ) w temporal
  ./refstr -refSize $(( 100 * $i * $i )) -pageLimit 50 -o $( echo "testing/str-4l-"$i"s.ref" ) w both
done

for k in $(seq 1 3) ; do
  for j in $(seq 1 4) ; do
    for i in $(seq 1 8) ; do
      ./genInputFile.sh $( echo "testing/in-1a-"$k"f-"$j"l-"$i"s.txt" ) -sim NO -a FIFO -tq 10 -f $(( 15 * $k )) -ref $( echo "testing/str-"$j"l-"$i"s.ref" ) 
      ./genInputFile.sh $( echo "testing/in-2a-"$k"f-"$j"l-"$i"s.txt" ) -sim NO -a LRU  -tq 10 -f $(( 15 * $k )) -ref $( echo "testing/str-"$j"l-"$i"s.ref" ) 
      ./genInputFile.sh $( echo "testing/in-3a-"$k"f-"$j"l-"$i"s.txt" ) -sim NO -a 2C   -tq 10 -f $(( 15 * $k )) -ref $( echo "testing/str-"$j"l-"$i"s.ref" ) 
    done
  done
done

for m in $(seq 1 10) ; do
  for l in $(seq 1 3) ; do
    for k in $(seq 1 3) ; do
      for j in $(seq 1 4) ; do
        for i in $(seq 1 8) ; do
          echo "Sim: $m"
          echo "Replacement: $l"
          echo "Frames: $(( 15 * $k ))"
          echo "Locality: $j"
          echo "References: $(( $i * $i * 100 ))"
          echo "Pages: 50"
          echo "Time Quantum: 10"
          echo "Locality: $j"
          time ./sim $( echo "testing/in-"$l"a-"$k"f-"$j"l-"$i"s.txt" ) 
        done
      done
    done
  done
done
