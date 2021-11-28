#!/bin/bash
num1=$1
str=$2
num2=$3
num3=`expr $num1 $str $num2`

echo $num3
exit 0
