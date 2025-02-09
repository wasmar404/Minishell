#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: ./show_tree.sh <program>"
  exit 1
fi

program="$1"

# Start the program in the background
"./$program" &
pid=$!

if [ $? -ne 0 ]; then
  echo "Error: Failed to run $program"
  exit 1
fi

# Wait a short time for the process to start
sleep 0.5

# Display process tree for the program
echo "Process tree for PID $pid:"
pstree -p "$pid"

# Wait for the process to complete (optional)
wait $pid
