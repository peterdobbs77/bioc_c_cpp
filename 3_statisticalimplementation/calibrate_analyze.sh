#!/bin/bash
dataStore=../../../lab/bien4290/microarray

cp $dataStore/gene_list.txt gene_list.txt
summary=summary.txt
[ ! -e $summary ] || rm $summary

for((i=0;i<7;i++)); do
  rData=$dataStore/red_$i.dat
  rBackData=$dataStore/red_background_$i.dat
  gData=$dataStore/green_$i.dat
  gBackData=$dataStore/green_background_$i.dat
  processed=./log_ratio_$i.dat
  
  (echo $rData;echo $rBackData;echo $gData;echo $gBackData;echo $processed;wc -l $rData) | (./preproc.exe)

  cp log_ratio_$i.dat log_ratio_input.dat
  wc -l "log_ratio_input.dat" | ./cluster.exe "log_ratio_input.dat" >> $summary
  cp "suppressed_genes.txt" "suppressed_genes_$i.txt"
  cp "stationary_genes.txt" "stationary_genes_$i.txt"
  cp "expressed_genes.txt" "expressed_genes_$i.txt"
done

echo "Done with calibrate_analyze"

#END