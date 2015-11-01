#!/bin/bash


echo "" > part3testing/part3results

./sim -t sim >> part3testing/part3results

for i in spatial temporal both random ; do
  ./refstr -refSize 500 -pageLimit 100 -o part3testing/testb w $(echo $i)
  sleep 0.1
  for j in FIFO LRU "2C 10" ; do
    for k in 10 25 50 80 ; do
      ./genInputFile.sh part3testing/inf -sim NO -a $(echo $j) -tq 10 -f $(echo $k) -ref part3testing/testb
      sleep 0.1
      ./sim $(echo "-loc-"$i) part3testing/inf >> part3testing/part3results
    done
  done
done


      

