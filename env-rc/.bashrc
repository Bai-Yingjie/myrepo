PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[01;34m\] \w\n`cat /etc/issue.net` \$\[\033[00m\] '
#LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH

case $TERM in
	xterm*)
		PROMPT_COMMAND='echo -ne "\033]0;$(hostname):$(basename $(pwd))\007"'
		export HISTCONTROL=ignoredups:erasedups  # no duplicate entries
		export HISTSIZE=100000                   # big big history
		export HISTFILESIZE=100000               # big big history
		shopt -s histappend                      # append to history, don't overwrite it
		export PROMPT_COMMAND="history -a;$PROMPT_COMMAND"
		;;
esac


alias rm='rm -i'
alias mv='mv -i'
alias jr='cd ~/repo && ls'
alias jt='cd ~/tmp && ls'
alias a='cd .. && ls'
alias aa='cd ../../ && ls'
alias aaa='cd ../../../ && ls'
alias aaaa='cd ../../../../ && ls'
alias aaaaa='cd ../../../../../ && ls'
alias aaaaaa='cd ../../../../../../ && ls'
alias aaaaaaa='cd ../../../../../../../ && ls'
alias aaaaaaaa='cd ../../../../../../../../ && ls'
alias fg1='fg %1'
alias fg2='fg %2'
alias fg3='fg %3'
alias fg4='fg %4'
alias fg5='fg %5'
alias fg6='fg %6'
alias kj1='kill -9 %1'
alias kj2='kill -9 %2'
alias kj3='kill -9 %3'
alias kj4='kill -9 %4'
alias kj5='kill -9 %5'
alias kj6='kill -9 %6'
alias ls='ls --color=auto'
alias ll='ls -l'
alias la='ls -a'
alias lla='ls -al'
alias llh='ls -lh'
alias llt='ls -lt'
alias lls='ls -lhS'
alias greprn='grep -rn1I --color=auto'
alias usetall='unset MAKECMDGOALS C_INCLUDE_PATH CPLUS_INCLUDE_PATH LIBRARY_PATH LD_LIBRARY_PATH PERL5LIB GCC_EXEC_PREFIX'
alias diff='diff -Naur'
#alias makc='make BUILDROOT_CUSTOM=1'
#alias mklinuxcs='make cscope ARCH=mips COMPILED_SOURCE=compiled'
alias minicom='sudo minicom --color=on -s -C ~/tmp/log/`date +%y%m%d%H%M`.log'
alias sshcv='ssh baiyingjie@cvsh.f3322.net'
alias sshcvx='ssh -X -C -c blowfish-cbc,arcfour baiyingjie@cvsh.f3322.net'
alias sshyun='ssh baiyingjie@cvtech.cn'
alias tmat0='tmux att -t0'
alias tmat1='tmux att -t1'
alias tmat2='tmux att -t2'
alias tmat3='tmux att -t3'
alias tmat4='tmux att -t4'
alias tmat5='tmux att -t5'
alias bc='bc -l'
alias vi=vim
alias em='emacs -nw'

mkcselffiles() {
	${CROSS_COMPILE}gdb -ex="info sources" -ex="quit" $1 | sed -e '1,15d' -e 's/,/\n/g' | sed -e '/^ *$/d' -e 's/^ *//g' > cscope.files.tmp1
	#find -L `cat cscope.files.tmp1 | egrep "/flat/" | sed 's!\(.*/flat/[^/]*\).*!\1!g' | sort -u` -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp" > cscope.files.tmp2
	#cat cscope.files.tmp1 cscope.files.tmp2 | sort -u > cscope.files
	cat cscope.files.tmp1 | sort -u > cscope.files
	rm -f cscope.files.tmp*
}

mkcsfiles() {
	#find -L $* -iname '*.[ch]' -o -iname '*.[ch]pp' -o -iname '*.cc' -o -iname '*.hh' -o -iname '*.s' | sort -u > cscope.files
	find -L $* -type f | sed -n '/\.\([chs]\)\1\{0,1\}\(pp\)\?$/Ip' | sort -u > cscope.files
}

mkcs(){
	if [ "$1" != "" ];then
		cp $1 cscope.files
	fi
	cscope -bkq -i cscope.files
}

common_path_2line() { #(line1, line2)
	local line1=$1
	local line2=$2
	while [[ "$line2" != "$line1"* ]];do
		line1=`dirname $line1`
	done
	echo $line1
}

find_common_path() {
	local csfile=$1
	local common_path=`head -n1 $csfile`
	for line in `cat $csfile`;do
		common_path=`common_path_2line $common_path $line`
	done
	echo $common_path
}

mkgt(){
	if [ "$1" != "" ];then
		cp $1 cscope.files
	fi
	cat cscope.files | egrep "^/repo.*\.c$" > cscope.files.tmp

	if [ -s cscope.files.tmp ];then
		local common_path=`find_common_path cscope.files.tmp`
	fi

	rm -f cscope.files.tmp
	if [ "$common_path" ];then
		mv cscope.files $common_path
		cd $common_path
	fi

	gtags -f cscope.files
}

proxyon() {
	export socks_proxy="socks://localhost:11985/"
	export http_proxy=$socks_proxy
	export https_proxy=$socks_proxy
	export ftp_proxy=$socks_proxy
	export rsync_proxy=$socks_proxy
	export no_proxy="localhost,127.0.0.1,localaddress,.localdomain.com"
	echo -e "\nProxy environment variable set."
}

proxyoff() {
	unset socks_proxy
	unset http_proxy
	unset https_proxy
	unset ftp_proxy
	unset rsync_proxy
	echo -e "\nProxy environment variable removed."
} 

