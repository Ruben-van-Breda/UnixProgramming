#!/bin/bash



INFO="Created by Ruben van Breda, 19200704, email: ruben.vanbreda@ucdconnect.ie

This bash script takes 2 arguments a source folder and a destination folder
It will copy all the .png files and convert it to jpg into the destination maintainning the source hierarchy
Dependencies
* imagemagick - convert a png to jpg
* 'brew install imagemagick'

EXECUTION:
./assign4_19200704 [source directory] [destination directory]
"
source=$1
dest=$2

# Check if a file is a .png if so convert it to .jpg and copy it into destination corrosponding directory
ConvertAndMoveFile(){
    # Parse data
    FULLNAME=`echo "${1}" | sed "s/.*\///" ` 
    NAME=`echo "${FULLNAME}" | cut -d'.' -f1`  #To remove the extension you can use
    EXTENSION=`echo "$1" | cut -d'.' -f2`
    THEPATH="${1/$source}";
    THEPATH="${THEPATH/$FULLNAME}"

    # Check if the file extension is png
    case  ${EXTENSION} in 
        "png")
            #Check if the directory doesn't exits (basicly any sub dir's)
            [ -d "$dest$THEPATH" ] || mkdir -p "$dest$THEPATH" 
            # Convert .png to .jpg and store in destination
            convert "$1" "$dest$THEPATH/$NAME.jpg";
            ;;
        *)
            # if not a .png do nothing
        ;;  
    esac
    return;
}
# Search Directors function
searchDir() {
 		
 	
 	echo "searching dir : $1";
 	for file in "$1"/*; do
        FULLNAME=`echo "${file}" | sed "s/.*\///" ` 
        NAME=`echo "${FULLNAME}" | cut -d'.' -f1`  #To remove the extension you can use
        EXTENSION=`echo "$file" | cut -d'.' -f2`
        THEPATH="${1/$source}";
        #recursivly look inside inner directories
        if [ -d "$file" ]; then
            searchDir "$file"

        else
            ConvertAndMoveFile "$file"
        fi
done
# Return returns an exit status number between 0 - 255
return 1
}



#________________________MAIN CODE________________________#


# display script info
if [ "$#" == 1 ] && [ "$1" == "-i" ] ; then
    echo "Information: $INFO"
    exit 1
fi
if [ "$#" != 2 ] 
then
    echo "Invalid arguments"
    exit 1;
fi

#Check that the source directory is valid
if [ ! -d $1 ]; then
    echo "Invalid source directory: $1"
    exit -1
fi
# Check that the destination directory is valid
if [ ! -d $2 ]; then
    echo "Invalid destination directory: $2"
    exit -1
fi

# loop through the source folders content
for file in "$source"/*; do
    #recursivly look inside inner directories
    if [ -d "$file" ]; then
        searchDir "$file"
    fi

    if [ -f "$file" ]; then
        ConvertAndMoveFile "$file"
    fi

done


