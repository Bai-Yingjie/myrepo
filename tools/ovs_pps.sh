#!/bin/bash

PATH=/usr/local/bin:$PATH

ovs-appctl dpctl/show > /dev/null
if [ $? -ne 0 ]; then
	printf "execution failed, you may need sudo?\n"
	exit 1
fi

prep () { #string
	echo "$1" | grep -Eo "port [0-9]*: [[:alnum:]]*|RX packets.*|TX packets.*" | tr "?" "0" \
		| awk -F'[ :]' '{if(NR%3==1) port=$4; else{for(i=2;i<=NF;i+=2){a[port,$1,$i]=$(i+1)}}} END {for(k in a) {split(k,se,SUBSEP);printf "%s %s %s:%s\n",se[1],se[2],se[3],a[k]}}'
}

cmd='ovs-appctl dpctl/show --statistics'

for t in t1 t2 t3; do
	test $t = t1 && v1=$(eval $cmd) && d1=$(date +%s%6N)
	test $t = t2 && sleep 1 && v2=$(eval $cmd) && d2=$(date +%s%6N)
	if test $t = t3; then
		((td=$d2 - $d1))
		#echo $td

		v1=$(prep "$v1")
		v2=$(prep "$v2")
		o=$(echo -e "$v1 \n$v2" | awk -F':' -v td="$td" '{a[$1]=$2-a[$1]} END {for(k in a) printf "%s %d pps\n",k,a[k]*1000000/td}')
		echo "$o" | grep -v " 0" | sort | awk '{printf "%s:\n\t%s %s\t%s\t%s\n",$1,$2,$3,$4,$5}'
	fi
done 
