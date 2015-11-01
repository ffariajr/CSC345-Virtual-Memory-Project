#!/bin/bash


echo "" > Part3/part3results

./sim -t sim >> Part3/part3results

for i in spatial temporal both random ; do
  ./refstr -refSize 500 -pageLimit 100 -o Part3/testb w $(echo $i)
  sleep 0.1
  for j in FIFO LRU "2C 10" ; do
    for k in 10 25 50 80 ; do
      ./genInputFile.sh Part3/inf -sim NO -a $(echo $j) -tq 10 -f $(echo $k) -ref Part3/testb
      sleep 0.1
      ./sim $(echo "-loc-"$i) Part3/inf >> Part3/part3results
    done
  done
done


      

