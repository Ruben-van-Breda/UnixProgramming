#!/bin/bash



# Check that we have the correct arguments
if [ "$#" != 2 ] 
then
    echo "Invalid arguments"
    exit 1;
fi

# # Check that the source directory is valid
# if [ -d $1 ]; then
#     echo "Invalid source directory: $1"
#     exit -1
# fi
# # Check that the destination directory is valid
# if [ -d $2 ]; then
#     echo "Invalid destination directory: $2"
#     exit -1
# fi

#cp "assign4_19200704.sh" "$2"
#pwd
for file in "$1"/*; do
    FULLNAME=`echo "${file}" | sed "s/.*\///" ` 
    NAME=`echo "${FULLNAME}" | cut -d'.' -f1`  #To remove the extension you can use
    EXTENSION=`echo "$file" | cut -d'.' -f2`
    case  ${EXTENSION} in 
    "png")
        echo "PNG FILE : $FULLNAME";
        cp "$1/$FULLNAME" "$2"
        ;;
    *)
    echo "$FULLNAME"
    ;;  
    esac
done

