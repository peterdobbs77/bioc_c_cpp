#!/bin/bash
results_lr=./results_lr.txt
results=./results.txt
[ ! -e $results ] || rm $results
[ ! -e $results_lr ] || rm $results_lr
tmp=IFS
IFS=$'\n'
for i in YOR100C YDR374C YPR192W YNL013C YLR227C YDR403W YKL050C; do
  echo $i >> $results
  bash data_retrieval.sh $i >> $results
  lineNum=$(grep -n $i gene_list.txt | grep -Eo '^[^:]+')
  let tailNum=$lineNum-1
  
  #echo $i >> $results_lr
  for((j=0;j<7;++j)); do
    lines=($(cat log_ratio_$j.dat))
    #echo "$j: ${lines[$tailNum]}" >> $results_lr
    echo ${lines[$tailNum]}
  done
done
IFS=tmp