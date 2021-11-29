#!/bin/bash
fnmae=$1
if [ ! -e $fname ]
then
	mkdir $fname
	cd $fname
	touch file0.txt file1.txt file2.txt file3.txt file4.txt
	tar cvf file.tar *
	mkdir $fname
	tar xvf file.tar -C ./files/

fi
exit 0
