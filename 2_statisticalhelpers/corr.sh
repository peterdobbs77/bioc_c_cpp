#!/bin/bash

echo "Enter concentration level to analyze, either 0 (0.0%) or 5 (0.5%):"
read concentration

if [ $concentration -eq 0 ]
  then  # perform correlation on files for concentration of 0.0% halothane
    dataDir=ERP00
  elif [ $concentration -eq 5 ]
    then  # peform correlation on files for concentration of 0.5% halothane
      dataDir=ERP05
  else
    echo "invalid input character"
    exit
fi
unset concentration

path="./EEG_DATA"
xData="$path/xinput.dat"
yData="$path/yinput.dat"
output=$path/"$dataDir"_corr.txt
[ ! -e $output ] || rm $output

# loop through files in "./EEG_DATA/ERPO#"
for file in "$path"/"$dataDir"/*.txt; do
  [ -e "$file" ] || continue	# handle the no match case
  cat $yData> $xData
  cat $file> $yData
  (echo $xData; echo $yData;) | (~/lib/corr.exe)>> $output
done

echo "Done with bash"

#END
