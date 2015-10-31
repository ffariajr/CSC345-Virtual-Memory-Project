#!/bin/bash


"" > SystemResults.txt
"" > ProcessResults.txt


for a in manysmall fewlarge mixed ; do
  for b in mixed spatial temporal both random ; do
    for c in manypages fewpages ; do
      if [ "$a" == "manysmall" ]; then
        dl=1
        dh=24
        el=250
      elif [ "$a" == "fewlarge" ]; then
        dl=1
        dh=6
        e=7500
      else
        dl=1
        dh=10
        e=2500
      fi
      if [ "$c" == "manypages" ]; then
        f=100
      else
        f=35
      fi
      "" > $(echo "part4testing/"$a"/"$b"/"$c"/strings.ref")
      for d in $(seq $dl $dh); do
        if [ "$b" == "mixed" ]; then
          ./refstr spatial -refSize $e -pageLimit $f -o $(echo "part4testing/"$a"/"$b"/"$c"/strings.ref") a 
          ./refstr temporal -refSize $e -pageLimit $f -o $(echo "part4testing/"$a"/"$b"/"$c"/strings.ref") a 
          ./refstr both -refSize $e -pageLimit $f -o $(echo "part4testing/"$a"/"$b"/"$c"/strings.ref") a 
          ./refstr random -refSize $e -pageLimit $f -o $(echo "part4testing/"$a"/"$b"/"$c"/strings.ref") a 
        else
          for g in 1 2 3 4 ; do
            ./refstr $b -refSize $e -pageLimit $f -o $(echo "part4testing/"$a"/"$b"/"$c"/strings.ref") a 
          done
        fi
      done
      for h in 2c-10 2c-3 fifo lru ; do
        for i in highmemory lowmemory ; do
          for j in hightq lowtq ; do
            if [ "$h" == "fifo" ]; then
              harg="FIFO"
            elif [ "$h" == "lru" ]; then
              harg="LRU"
            elif [ "$h" == "2c-10" ]; then
              harg="2C 10"
            else
              harg="2C 3"
            fi
            if [ "$j" == "hightq" ]; then
              tq=25
            else
              tq=8
            fi
            if [ "$i" == "highmemory" ]; then
              mem=1000
            else
              mem=150
            fi

            ./genInputFile.sh $(echo "part4testing/"$a"/"$b"/"$c"/"$h"/"$i"/"$j"/input.txt") -sim YES --algorithm $harg -tq $tq --frames $mem -sc RR -ref $(echo "part4testing/"$a"/"$b"/"$c"/strings.ref") $(echo "-t") 

            $a >> ProcessResults.txt
            $b >> ProcessResults.txt
            $c >> ProcessResults.txt
            $h >> ProcessResults.txt
            $i >> ProcessResults.txt
            $j >> ProcessResults.txt
            ./sim $(echo "-s") $(echo "part4testing/"$a"/"$b"/"$c"/"$h"/"$i"/"$j"/input.txt") >> ProcessResults.txt
            "" >> ProcessResults.txt

            $a >> SystemResults.txt
            $b >> SystemResults.txt
            $c >> SystemResults.txt
            $h >> SystemResults.txt
            $i >> SystemResults.txt
            $j >> SystemResults.txt
            ./sim $(echo "-o") $(echo "part4testing/"$a"/"$b"/"$c"/"$h"/"$i"/"$j"/input.txt") >> SystemResults.txt
            "" >> SystemResults.txt

          done
        done
      done
    done
  done
done
        




