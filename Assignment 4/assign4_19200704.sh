#!/bin/bash



# Check that we have the correct arguments
if [ "$#" != 2 ] 
then
    echo "Invalid arguments"
    exit 1;
fi

# Check that the source directory is valid
if [ -d $1 ]; then
    echo "Invalid source directory: $1"
    exit -1
fi
# Check that the destination directory is valid
if [ -d $2 ]; then
    echo "Invalid destination directory: $2"
    exit -1
fi

for file in "$1"/*; do
    case  ${file: -4} in 
    ".png")
        echo "$file"
        ;;
    *)
    echo "unknown";;  
    esac
done

