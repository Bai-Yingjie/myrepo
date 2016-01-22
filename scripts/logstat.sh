#! /bin/bash

B="\033[1;37;40m"
N="\033[0m"

logfile=${1:-log}

./statistics.sh | ts | tee $logfile
