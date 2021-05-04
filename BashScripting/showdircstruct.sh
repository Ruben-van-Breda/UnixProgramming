#!/bin/bash

varPNG=".png"

# Check that we have the correct arguments
if [ "$#" != 2 ] 
then
    echo "Invalid arguments"
    exit 1
fi
#cd $1
#pwd

# list he files in the source directory
for file in "$1"/*; do
    echo "File $file"
    if [ "${file: -4}" == ".png" ]       #  check if .png file
    then
        echo "Convert png to jpg "
    fi
done;

#ls *"$varPNG"


