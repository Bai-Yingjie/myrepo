#!/bin/bash

PATH=/usr/local/bin:$PATH

ovs-vsctl list interface > /dev/null
if [ $? -ne 0 ]; then
	printf "ovs-vsctl execution failed, you may need sudo?\n"
	exit 1
fi

cmd='(ovs-vsctl list interface && echo date: $(date +%s%6N)) | grep -E "^name|^statistics|^date" | sed -r -e "s/,|\{|\}//g" -e "s/name *: (.*)/\1:/g" -e "s/statistics *://g"'

for t in t1 t2 t3; do
	test $t = t1 && v1=$(eval $cmd)
	test $t = t2 && sleep 10 && v2=$(eval $cmd)
	if test $t = t3; then
		i=0
		declare -A map1 map2

		v1=$(echo "$v1" | awk -F: '{printf $0; if(NF==1 || $1=="date") print ""}')
		while read k v; do
			map1[$k]=$v
		done <<< "$v1"

		v2=$(echo "$v2" | awk -F: '{printf $0; if(NF==1 || $1=="date") print ""}')
		while read k v; do
			map2[$k]=$v
		done <<< "$v2"

		((TimeDiff=${map2[date:]} - ${map1[date:]}))

		for k in "${!map2[@]}"; do
			if test $k != "date:";then
				echo ==== pps for $k ====
				echo -e "${map1[$k]} \n${map2[$k]}" | tr ' ' '\n' | grep -v "bytes" | awk -F'=' -v td="$TimeDiff" '{a[$1]=$2-a[$1]} END {for(k in a) printf "%s %d pps\n",k,a[k]*1000000/td}' | grep -v " 0 " | sort
			fi
		done
	fi
done 
