#! /usr/bin/env bash

# This scripts loads the binary for linux-arm by creating a directory, copying
# the binary, and executing the binary

# Display all commands executed in script
set -x

# Make a directory for the binary to be placed
ssh debian@192.168.7.2 'mkdir -p /home/debian/Workspace/ECEN5013'

# Copy the binary into the directory just created 
scp out/linux-arm/main debian@192.168.7.2:/home/debian/Workspace/ECEN5013

# Log directory for kl25z
log_dir="logs/linux-arm"

# If log dir exists erase logs else create dir 
if [ -d "${log_dir}" ] ; then
  rm -rf ${log_dir}/* 
else
  mkdir -p ${log_dir} 
fi

# Kill gdbserver if one is running
gdbserver=`ssh debian@192.168.7.2 'ps -ef | grep gdbserver | grep -v grep'`
if [ "${gdbserver}" != "" ] ; then
  # Execute binary
  ssh debian@192.168.7.2 'pkill gdbserver'
fi

# Start new server
ssh debian@192.168.7.2 'gdbserver localhost:2345 /home/debian/Workspace/ECEN5013/main ' > ${log_dir}/`date +%s`.log &

sleep 5

gdb-multiarch --command=tools/linux-arm/gdb_commands.txt
