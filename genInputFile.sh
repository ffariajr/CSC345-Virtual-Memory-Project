#!/bin/bash

if [ $# -lt 1 -o "$1" == "-h" ]; then
  if [ $# -lt 1 ]; then
    echo "Error: Invalid Arguments."
  fi
  echo "Usage is as follows:" 
  echo "  $0 -h"
  echo "      Displays this help message."
  echo ""
  echo "  $0 <destfile> [<options>] [-t <startTimes>]"
  echo ""
  echo "      <destfile>"
  echo "          Must be a file that can be overwritten."
  echo "          The program \"sim\" ignores every character, except a colon (\":\") and the"
  echo "          strings that come after the colon, which are processed in order as they appear."
  echo ""
  echo "      <options>"
  echo "          Can be in any order.  All options default to a default value when omitted."
  echo ""
  echo "          -sim <ans>"
  echo "          --fule-sim <ans>"
  echo "              <ans> must be either \"YES\" or \"NO\"."
  echo "          -a <algo>"
  echo "          --algorithm <algo>"
  echo "              <algo> must be one of: \"FIFO\", \"LRU\", or \"2C\"."
  echo "          -tq <quantum>"
  echo "          --time-quantum <quantum>"
  echo "              <quantum> must be a number greater than 1."
  echo "          -f <num>"
  echo "          --frames <num>"
  echo "              <num> must be a number."
  echo "          -sc <sched>"
  echo "          --scheduler <sched>"
  echo "              Only available value is \"RR\"."
  echo "          -ref <file>"
  echo "          --refstr-file <file>"
  echo "              Specifies where to look for the generated reference strings."
  echo ""
  echo "      -t <startTimes>"
  echo "          Following \"-t\", you may list up to 99 space separated numbers."
  echo "          These numbers correspond to the start time of of reference string"
  echo "          respective to the order they are listed."
  echo ""
  exit
fi

file=$1
shift

fullsim="NO"
repl="FIFO"
tq=10
mframes=20
sched="RR"
reffile="strings.ref"

i=0

while true; do

  if [ $# -eq 0 ]; then
    break
  elif [ "$1" == "-sim" -o "$1" == "--full-sim" ]; then
    shift
    fullsim=$1
    shift
    i=$((i+2))
  elif [ "$1" == "-a" -o "$1" == "--algorithm" ]; then
    shift
    repl=$1
    shift
    i=$((i+2))
  elif [ "$1" == "-tq" -o "$1" == "--time-quantum" ]; then
    shift
    tq=$1
    shift
    i=$((i+2))
  elif [ "$1" == "-f" -o "$1" == "--frames" ]; then
    shift
    mframes=$1
    shift
    i=$((i+2))
  elif [ "$1" == "-sc" -o "$1" == "--scheduler" ]; then
    shift
    sched=$1
    shift
    i=$((i+2))
  elif [ "$1" == "-ref" -o "$1" == "--refstr-file" ]; then
    shift
    reffile=$1
    shift
    i=$((i+2))
  elif [ "$1" == "-t" ]; then
    shift
    break
  fi
done


echo "Input file for Virtual Memory Simulator Project" > $file
echo "If any of the pre-formatting of this file is changed, please remake the file." >> $file
echo "" >> $file
echo "Run Full Simulation." >> $file
echo "        If set to \"NO\", then only part 3 of the project requirements" >> $file
echo "        will be run.  If set to \"YES\", then part 4 will be included." >> $file
echo ":$fullsim" >> $file
echo "" >> $file
echo "Replacement Algorithm." >> $file
echo "        Must be \"FIFO\", \"LRU\", or \"2C\"" >> $file
echo ":$repl" >> $file
echo "" >> $file
echo "Time Quantum." >> $file
echo "        Must be a number between 1 and MAXINT." >> $file
echo ":$tq" >> $file
echo "" >> $file
echo "Memory Frames." >> $file
echo "        Must be a number from 10 to 1000." >> $file
echo ":$mframes" >> $file
echo "" >> $file
echo "Scheduler." >> $file
echo "        Currently, can only be set to \"RR\"" >> $file
echo ":$sched" >> $file
echo "" >> $file
echo "Reference String File." >> $file
echo "        The name of a file that contains the reference strings." >> $file
echo ":$reffile" >> $file
echo "" >> $file
echo "Reference String Start Times." >> $file
echo "        Start times can be set here. 1 means 1 time quantum. \"-1\"'s are ignored." >> $file
echo "        The amount of non-\"-1\"'s must match the amount of reference strings." >> $file

for j in $(seq 1 99); do

  if [ $# -gt 0 ]; then
    t=$1
    shift
  elif [ $j -eq 1 ]; then
    t=0
  else
    t=-1
  fi

  if [ $j -gt 9 ]; then
    echo "$j:$t" >> $file
  else
    echo "0$j:$t" >> $file
  fi
done

