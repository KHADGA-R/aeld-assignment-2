
#!/bin/bash

# Author : Khadga Parajuli

if [ $# -ne 2 ] 
then 
	echo "Error : two arguments are required"
	exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d "$filesdir" ]
then
	echo "Error : $filesdir is not a directory"
	exit 1

fi

numfiles=$(find "$filesdir" -type f | wc -l)
num_matching_lines=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $numfiles and the  number of matching lines are $num_matching_lines"
