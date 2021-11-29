#!/bin/bash

mkdir $1
cd $1
mkdir file0 file1 file2 file3 file4
touch file0.txt file1.txt file2.txt file3.txt file4.txt
ln -s file0.txt file0
ln -s file1.txt file1
ln -s file2.txt file2
ln -s file3.txt file3
ln -s file4.txt file4
exit 0
