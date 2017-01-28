#! /usr/bin/env bash

# Display commands executed
set -x

# Ensure pegdb server is running
server=`ps | grep pegdb`
if [ -n ${server} ] ; then
  echo "pegdb server is not started"
  exit 1
fi

# Start gdb session
arm-none-eabi-gdb --command=gdb_commands.txt
