sysctl vm.min_free_kbytes=$((1<<21))

for i in b c d e f g h i j k l;
do
    echo deadline > /sys/block/sd${i}/queue/scheduler
	echo 64 > /sys/block/sd${i}/queue/iosched/fifo_batch
	echo 16384 > /sys/block/sd${i}/queue/nr_requests
	echo 1 > /sys/block/sd${i}/queue/rq_affinity
done
