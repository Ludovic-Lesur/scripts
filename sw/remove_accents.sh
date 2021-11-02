#!/bin/bash

# Check number of parameters.
if [ $# -eq 0 ]
then
	# Loop on all files of the current folder.
	for file in *
	do
		extension="${file##*.}"
		# Select code files.
		if [ $extension = "java" ]
		then
			# Convert to us-ascii encoding.
			iconv -f ISO-8859-1 -t ascii//TRANSLIT $file -o $file
			# Replace all accents.
			echo "Removing all accents in file $file."
			sed -i "y/àâéèêëîôùû/aaeeeeiouu/" $file
		fi
	done
else
	echo "Wrong number of parameters."
fi
