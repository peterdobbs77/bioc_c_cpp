# HIST.SH

# prompt user for input
echo "Enter concentration level to analyze, either 0 (0.0%) or 5 (0.5%):"
read concentration

if [ $concentration -eq 0 ]
  then  #concatenate files for concentration of 0.0% halothane
    dataDir=ERP00
  elif [ $concentration -eq 5 ]
    then  # concatenate files for concentration of 0.5% halothane
      dataDir=ERP05
  else
    echo "invalid input character sequence"
    exit
fi
unset concentration

# Concatenate all 60 data files from appropriate
#  concentration level into one data file
path="./EEG_DATA"
aggregatedData="$path/input.dat"
# check to see if aggreggated data file already exists
if [ -e $aggregatedData ]
  then
    rm $aggregatedData
fi
# loop through files in "./EEG_DATA/ERPO#"
for file in "$path/$dataDir/*"
  do
    cat $file >> $aggregatedData
  done

output=$path/"$dataDir"_hist.txt
(echo $path/input.dat) | (~/lib/hist.exe) > $output

echo "Output is stored in $output"

echo "Done with bash"

#END
