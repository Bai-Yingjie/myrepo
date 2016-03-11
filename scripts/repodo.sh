#!/bin/bash
B="\033[1;37;40m"
N="\033[0m"

top_dir=`pwd`
remote=`git remote -v | grep fetch | awk '{print $2}'`
repos_branch='./master bdk/master sdk/master sdk/bootloader/edk2/thunder-stable sdk/bootloader/grub2/grub/master sdk/bootloader/trusted-firmware/atf/thunder-stable sdk/bootloader/u-boot/thunder-stable sdk/linux/kernel/linux-aarch64/thunder-stable'

function reset_current()
{
	remote_branch=`git branch -vv | grep "\*" | sed -r 's/.*\[(.*)\].*/\1/g' | cut -d: -f1`
	echo ===reseting with $remote_branch
	git reset --hard $remote_branch
}

for repo_branch in $repos_branch; do
	repo=`dirname $repo_branch`
	branch=`basename $repo_branch`
	cd $top_dir

	if [ ! -d $repo ]; then 
		echo cloning $repo 
		cd `dirname $repo`
		if [ $repo == bdk ]; then
			git clone $remote/$repo
		else
			git clone -b fae $remote/$repo
		fi
	fi

	cd $top_dir/$repo

	echo -e $B">>>`pwd`"$N
	case "$1" in
		purge)
			echo ==deep cleaning...
			git clean -fdx
			;;
		fetch)
			echo ==fetching from remote...
			git fetch --all
			;;
		merge|rebase)
			echo ==merging/rebasing workspace with $branch...
			git rebase origin/$branch
			;;
		#upsync MUST be only used on my mint mechine
		upsync)
			echo ==fetching all
			git fetch --all
			echo ==reseting with remote master
			reset_current
			echo ==chekouting $branch
			git checkout $branch
			echo ==reseting with remote stable 
			reset_current
			echo ==going back to master
			git checkout -
			;;
		*)
			echo ==doing ["$@"]
			"$@"
			;;
	esac
	echo
done
