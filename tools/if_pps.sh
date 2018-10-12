#!/bin/bash

if [ -z $1 ] && [ -x /usr/bin/ibdev2netdev ]; then
	NETIF=$(ibdev2netdev | awk '/mlx/{print $5}')
else
	NETIF=$@
fi

if [ -z "$NETIF" ]; then
	printf "No interface can't be found\n"
	exit 1
fi

cmd='for f in /sys/class/net/$name/statistics/*;do echo -n "$(basename $f): "; cat $f;done | grep -E -v ": 0|bytes" && echo date: $(date +%s%6N)'

for t in t1 t2 t3; do
	i=0
	test $t = t2 && sleep 1
	for name in $NETIF; do 
		test $t = t1 && v1[$i]=$(eval $cmd)
		test $t = t2 && v2[$i]=$(eval $cmd)
		if test $t = t3; then
			echo "==== pps for $name ===="
			echo -e "${v1[$i]} \n${v2[$i]}" | awk '{a[$1]=$2-a[$1]} END {for(k in a) printf "%s %d pps\n",k,a[k]*1000000/a["date:"]}' | grep -v ": 0" | sort | tail -n+2
			echo 
		fi
		((i++))
	done
done 
