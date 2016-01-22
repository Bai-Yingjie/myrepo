#! /bin/bash

B="\033[1;37;40m"
N="\033[0m"

file=
interval=5
sleepsec=10
title=

while getopts "f:i:s:t:" arg #: needs para 
do
	case $arg in
		f)
			file=$OPTARG #$OPTARG is the para
			;;
		i)
			interval=$OPTARG
			;;
		s)
			sleepsec=$OPTARG
			;;
		t)
			title=$OPTARG
			;;
		?) 
			echo "unkonw argument"
			exit 1
			;;
	esac
done

#exec &> $output #output to file

function do_syscollect()
{
	echo; echo $title
	echo -e $B"start system statistics collecting"$N
	dmesg -c

	while test -f "$file";
	do
		echo; echo  -e $B"========================collecting system status==========================="$N
		echo; echo -e $B"===date"$N
		date
		echo; echo -e $B"===dmesg"$N
		dmesg -c
		echo; echo -e $B"===top"$N
		top -bn1 | head -15
		echo; echo -e $B"===sar"$N
		sar -n DEV -u -dp -r $interval 1 | grep Average
		sleep $sleepsec
	done
}

do_syscollect | ts
