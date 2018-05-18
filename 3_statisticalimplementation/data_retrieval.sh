#!/bin/bash
if [ $# -ne 1 ]; then
  echo "Must enter only 1 gene"
  exit
fi
for((i=0;i<7;i++)); do
  if [ $(grep $1 expressed_genes_$i.txt | wc -l) -gt 0 ]; then
    echo "$i: expressed"
  elif [ $(grep $1 suppressed_genes_$i.txt | wc -l) -gt 0 ]; then
    echo "$i: suppressed"
  elif [ $(grep $1 stationary_genes_$i.txt | wc -l) -gt 0 ]; then
    echo "$i: stationary"
  else
    echo "status of $1 not found for time point $i"
  fi
done