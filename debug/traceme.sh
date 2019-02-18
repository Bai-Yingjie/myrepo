#!/bin/sh 
 
DEBUGFS=/sys/kernel/debug 
 
if test "$1" != "stop"; then 
        #对当前线程tracing 
        echo $$ > $DEBUGFS/tracing/set_ftrace_pid 
        #选择tracing方法 
        #echo function > $DEBUGFS/tracing/current_tracer 
        echo function_graph > $DEBUGFS/tracing/current_tracer 
 
        #开始tracing 
        echo 1 > $DEBUGFS/tracing/tracing_on 
        #执行被trace的命令 
        #用exec不会改变进程号, 但会替换掉当前shell 
        exec $* 
else 
        #关闭tracing 
        echo 0 > $DEBUGFS/tracing/tracing_on 
 
        #清除限定的pid 
        echo > $DEBUGFS/tracing/set_ftrace_pid 
 
        #show trace log 
        cat $DEBUGFS/tracing/trace 
 
        #清空trace log 
        cat $DEBUGFS/tracing/trace_pipe > /dev/null 
fi
