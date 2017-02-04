#! /usr/bin/env bash

# Display commands executed
set -x

# Ensure pegdb server is running
server=`ps -ef | grep pegdb`
if [ "${server}" = "" ] ; then
  echo "pegdb server is not started"
  exit 1
fi

# Start gdb session
arm-none-eabi-gdb --command=tools/kl25z/gdb_commands.txt
