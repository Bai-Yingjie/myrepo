#! /bin/bash

B="\033[1;37;40m"
N="\033[0m"

atlocal=F

servers="
yingjie@192.168.85.10
byj@localhost
"

cvmservers="
root@10.97.219.6
root@10.97.219.55
root@10.97.219.21
root@10.97.219.44
root@10.97.219.53
root@10.97.219.50
root@10.97.219.214
root@10.97.219.13
root@10.97.219.47
root@10.97.219.69
"

if [ "$1" = "-l" ]; then
	atlocal=T
	shift
fi

for i in $cvmservers; do
	ip=${i#*@}
	echo
	echo -e $B">>>$i"$N
	if [ "$atlocal" = "T" ]; then
		eval "$*"
	else
		ssh $i "$*"
	fi
done
