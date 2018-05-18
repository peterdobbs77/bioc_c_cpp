if [ $# -ne 2 ]; then
  echo "Must enter 2 file names"
  exit
fi

input=$1
output=$2

[ -e $input ] || exit 1   #ensure that inputfile does exists
[ ! -e $output ] || rm $output  #ensure that outputfile does not exist

offset=$(sed -n 1p $input)
lineNumThickness=$(($offset+5))
lineNumIndeces=$(($offset+6))
lineNumData=$(($offset+7))

slice_thickness=$(sed -n "$lineNumThickness"p $input)
slice_indeces=$(sed -n "$lineNumIndeces"p $input)
slice_index1=$(echo $slice_indeces | cut -d ' ' -f 1)
slice_index2=$(echo $slice_indeces | cut -d ' ' -f 2)
total_slices=$(($(ls -l $(dirname $input)|wc -l) - 1)) #number of files in the directory

slice_coord1=$(echo "scale=3; $slice_index1*$slice_thickness-$total_slices*$slice_thickness/2"|bc)
slice_coord2=$(echo "scale=3; $slice_index2*$slice_thickness-$total_slices*$slice_thickness/2"|bc)

for((i=1;i<$lineNumThickness;i++)); do
  echo $(sed -n "$i"p $input) >> $output
done
echo "$slice_coord1  $slice_coord2" >> $output
echo $(sed -n "$lineNumData"p $input) >> $output

#Extra Credit: replace Lung with LungInhale
sed -i -e 's/Lung/LungInhale/g' $output
# and replace Adipose with AdiposeTissue
sed -i -e 's/Adipose/AdiposeTissue/g' $output