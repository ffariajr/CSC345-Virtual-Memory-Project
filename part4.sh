#!/bin/bash


./sim -t sim >  Part4/part4results

if [ ! -e Part4 ]; then
  mkdir Part4
fi

for a in manysmall fewlarge mixed ; do
  if [ ! -e $(echo "Part4/"$a) ]; then
    mkdir $(echo "Part4/"$a)
  fi
  for b in spatial temporal both random ; do
    if [ ! -e $(echo "Part4/"$a"/"$b) ]; then
      mkdir $(echo "Part4/"$a"/"$b)
    fi
    for c in manypages fewpages ; do
      if [ ! -e $(echo "Part4/"$a"/"$b"/"$c) ]; then
        mkdir $(echo "Part4/"$a"/"$b"/"$c)
      fi
      if [ "$a" == "manysmall" ]; then
        dl=1
        dh=99
        e=250
      elif [ "$a" == "fewlarge" ]; then
        dl=1
        dh=25
        e=7500
      else
        dl=1
        dh=50
        e=2500
      fi
      if [ "$c" == "manypages" ]; then
        f=100
      else
        f=35
      fi
      echo "" > $(echo "Part4/"$a"/"$b"/"$c"/strings.ref")
      for d in $(seq $dl $dh); do
        if [ ! -e $(echo "Part4/"$a"/"$b"/"$c"/strings.ref") ]; then
          touch $(echo "Part4/"$a"/"$b"/"$c"/strings.ref")
        fi
        ./refstr $(echo $b) -refSize $(echo $e) -pageLimit $(echo $f) $(echo "-o") $(echo "Part4/"$a"/"$b"/"$c"/strings.ref") a 
        sleep 0.1
      done
      for h in 2c-10 2c-3 fifo lru ; do
        if [ ! -e $(echo "Part4/"$a"/"$b"/"$c"/"$h) ]; then
          mkdir $(echo "Part4/"$a"/"$b"/"$c"/"$h)
        fi
        for i in highmemory lowmemory ; do
          if [ ! -e $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i) ]; then
            mkdir $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i)
          fi
          for j in hightq lowtq ; do
            if [ ! -e $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i"/"$j) ]; then
              mkdir $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i"/"$j)
            fi
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


            if [ ! -e $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i"/"$j"/inpu.txt") ]; then
              touch $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i"/"$j"/input.txt")
            fi

            ./genInputFile.sh $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i"/"$j"/input.txt") -sim YES --algorithm $(echo $harg) -tq $(echo $tq) --frames $(echo $mem) -sc RR -ref $(echo "Part4/"$a"/"$b"/"$c"/strings.ref") $(echo "-t") $(seq -f "0" -s " " $d)
            sleep 0.1
            ./sim $(echo "-loc-"$b) $(echo "Part4/"$a"/"$b"/"$c"/"$h"/"$i"/"$j"/input.txt") >> Part4/part4results
          done
        done
      done
    done
  done
done
        




