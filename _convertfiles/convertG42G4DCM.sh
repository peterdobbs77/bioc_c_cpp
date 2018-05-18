if [ $# -ne 2 ]; then
  echo "Must enter 2 directory names"
  exit
fi

input=$1
output=$2

[ -e $input ] || exit 1   #ensure that inputdir exists
[ -e $output ] || mkdir $output  #ensure that outputdir exists

IFS=' ' read -r -a arr <<< "$(echo $input/*.g4)"

for f in "${arr[@]}"; do
   file=$(basename "$f")
   filename="${file%.*}"
   bash ./convertG42G4DCM.sh "$f" "$output/$filename.g4dcm"
done