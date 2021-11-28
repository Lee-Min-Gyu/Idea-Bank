#!/bin/bash
weight=$1
height=$2
bmi=`expr $weight \* 10000 / \( $height \* $height \)`
if [ $bmi -gt 23 ];then
	echo "과체중"
elif [ $bmi -lt 18 ];then
	echo "저체중"
else
	echo "정상"
fi
exit 0
