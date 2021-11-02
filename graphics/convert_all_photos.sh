#!/bin/bash

# Check number of parameters.
if [ $# -eq 1 ]
then
	# Retrieve compressing pourcentage.
	pourcentage=$1
	# Loop on all files of the current folder.
	for file in *
	do
		name="${file%%.*}"
		extension="${file##*.}"
		# Select photos.
		if [ $extension = "jpg" ] || [ $extension = "JPG" ] || [ $extension = "png" ]
		then
			# Compress file.
			newfilename="$name.jpg"
			echo "Compressing $file by $pourcentage. Creating $newfilename."
			convert -resize $pourcentage $file $newfilename
			# Remove old file if required.
			if [ $file != $newfilename ]
			then
				rm $file
			fi
		fi
	done
else
	echo "Wrong number of parameters."
fi
