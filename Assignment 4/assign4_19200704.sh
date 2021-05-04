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

source=$1
dest=$2

# Define function
searchDir() {
 		
 	
 	echo "searching dir : $1";
 	for file in "$1"/*; do
        FULLNAME=`echo "${file}" | sed "s/.*\///" ` 
        NAME=`echo "${FULLNAME}" | cut -d'.' -f1`  #To remove the extension you can use
        EXTENSION=`echo "$file" | cut -d'.' -f2`
        
        THEPATH="${1/$source}";

       echo "Path : $THEPATH"
        #recursivly look inside inner directories
        if [ -d "$file" ]; then
            searchDir "$file"
        fi

        case  ${EXTENSION} in 
        "png")
           # echo "PNG FILE : $PATH"
            echo "$1/$FULLNAME -> " "$dest$THEPATH/$FULLNAME"
            mkdir -p "$dest$THEPATH/" 
            cp "$1/$FULLNAME" "$dest$THEPATH/$FULLNAME"
            ;;
        
        *)
        echo "$FULLNAME"
        ;;  
    esac
done
 		# Return returns an exit status number between 0 - 255
 		return
}

#cp "assign4_19200704.sh" "$2"
#pwd
for file in "$1"/*; do
    FULLNAME=`echo "${file}" | sed "s/.*\///"`
    NAME=`echo "${FULLNAME}" | cut -d'.' -f1`  #To remove the extension you can use
    EXTENSION=`echo "$file" | cut -d'.' -f2`
    
    #recursivly look inside inner directories
    if [ -d "$file" ]; then
        searchDir "$file"
    fi

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
