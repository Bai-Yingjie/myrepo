work_dir=`pwd`
dev=${1:-/dev/sdc}
ubuntu_size=${2:-200G}
tar_fedora=${3:-fedora-with-native-kernel-repo-gcc-update-to-20150423.tar.bz2}

if [ ! -b $dev ]; then
	echo "$dev not found"
	exit 1
fi

if [ -b ${dev}3 ]; then
	echo "fedora already exists, nothing to do"
	exit 0
fi

if [ ! -f $tar_fedora ]; then
	echo "file $tar_fedora not found"
	exit 1
fi

echo "resizing ubuntu fs"
e2fsck -f ${dev}2 
resize2fs ${dev}2 $ubuntu_size 

echo "resizing ubuntu partition"
gdisk $dev <<EOF
d
2

n


+$ubuntu_size


n





w
y
EOF

sleep 2

echo "making file system for fedora"
mkfs.ext4 ${dev}3

cd $work_dir
echo "installing grub into defora partition"
cd sdk-master
source env-setup BOARD_TYPE=crb-2s
cd host/bin
#reinstall grub on fedora partition, as well as kernel Image...
./create_disk.sh --install-grub2 ${dev}1 ${dev}3 /boot


cd $work_dir
echo "untaring fedora"
mount ${dev}3 mnt
cd mnt
tar xvf ../$tar_fedora
cd ..
umount mnt


#cd $work_dir
#echo "installing modules on fedora"
#./create_disk.sh --install-modules ${dev}3


#cd $work_dir
#echo "some tuning"
#mount ${dev}3 mnt
#cd mnt
##clear fstab
#echo > etc/fstab
##grub
#sed -i "/set timeout/a\\\nmenuentry 'Thunder Fedora Boot' {\n\tlinux /boot/vmlinuz root=/dev/sda3 console=ttyAMA0,115200n8 earlycon=pl011,0x87e024000000 coherent_pool=16M rootwait rw transparent_hugepage=never\n\tboot\n}\n" boot/grub/grub.cfg
#find lib/modules -name rtc-efi.ko | xargs -i mv {} {}.bak
#cd ..
#umount mnt

