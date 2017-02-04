#! /usr/bin/env bash

# This scripts loads the binary for bbb by creating a directory, copying
# the binary, and executing the binary

# Make a directory for the binary to be placed
ssh debian@192.168.7.2 'mkdir -p /home/debian/Workspace/ECEN5013'

# Copy the binary into the directory just created 
scp out/linux-arm/main debian@192.168.7.2:/home/debian/Workspace/ECEN5013

# Execute binary
ssh debian@192.168.7.2 '/home/debian/Workspace/ECEN5013/main'
