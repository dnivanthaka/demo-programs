#!/bin/sh

format_and_print(){
	#echo "Im here"
	if [ "$1" ]
	then
		#echo "Para - $1"
	fi
}

for file in `ls`
do
	echo $file
	format_and_print $file
done

exit 0
