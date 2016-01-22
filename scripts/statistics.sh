#! /bin/bash

B="\033[1;37;40m"
N="\033[0m"

echo -e $B"start system statistics collecting"$N

./alldo.sh dmesg -c
while true;
do
	echo -e $B"========================collecting system status==========================="$N
	echo; echo -e $B"===date"$N
	./alldo.sh 'date'
	echo; echo -e $B"===dmesg"$N
	./alldo.sh 'dmesg'
	echo; echo -e $B"===top"$N
	./alldo.sh 'top -bn1 | head -15'
	echo; echo -e $B"===pangu"$N
	./alldo.sh "ps -ef | egrep 'pangu|tubo|nuwa_agent|deploy_agent|chunkserver'"
	echo; echo -e $B"===sar"$N
	./alldo.sh 'sar -n DEV -u -dp -r 5 1 | grep Average'
	sleep $((60*1))
done
