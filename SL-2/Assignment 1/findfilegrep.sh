#!/bin/sh

if [ -f $1 ]
then
	grep -i '' $1
else
	echo "Not found"
fi

