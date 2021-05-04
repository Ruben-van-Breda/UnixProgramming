#!/bin/bash
CAPITAL="DUBLIN"
if [ "$CAPITAL" == "CORK" ]; then
echo "The capital is CORK."
elif [ "$CAPITAL" == "GALWAY" ]; then
echo "The capital is GALWAY."
elif [ "$CAPITAL" == "DUBLIN" ] ; then
echo "The capital is DUBLIN." 
else
	echo "There is no capital ." >&2
	exit 1 
fi
exit