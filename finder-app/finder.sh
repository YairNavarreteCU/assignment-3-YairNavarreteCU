#!/bin/sh

filesDirectory=$1
searchString=$2

if [ -z $filesDirectory ] || [ -z $searchString ];
then
	echo "Missing inputs"
	exit 1
fi 

if [ ! -d "$filesDirectory" ]; 
then
	echo "Directory not found"
	exit 1
fi

numberOfFiles=$(find "$filesDirectory" -type f | wc -l) 
numberOfMatchingLines=$(grep -r  "$searchString" "$filesDirectory" | wc -l)

echo "The number of files are $numberOfFiles and the number of matching lines are $numberOfMatchingLines" 
