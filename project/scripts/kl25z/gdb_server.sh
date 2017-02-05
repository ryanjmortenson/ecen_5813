#/usr/bin/env bash

# Display all commands executed in script
set -x

# Log directory for kl25z
log_dir="logs/kl25z"

# If log dir exists erase logs else create dir 
if [ -d "${log_dir}" ] ; then
  rm -rf ${log_dir}/* 
else
  mkdir -p ${log_dir} 
fi

pegdb=`ps -ef | grep pegdb | grep -v grep`
if [ "${pegdb}" != "" ] ; then
  pkill -9 pegdb 
fi

# Starts the debug server for KL25Z.  Ensure the directory to the peggbserver_console is added to the PATH environment variable. 
pegdbserver_console -showflashstatus -verbose -device=NXP_KL2x_KL25Z128M4 -startserver -serverport=7222 -gdbmiport=6224 -interface=OPENSDA -speed=5000 -port=USB > ${log_dir}/`date +%s`_console.log &

sleep 2

# Start gdb session
arm-none-eabi-gdb --command=tools/kl25z/gdb_commands.txt
