#!/bin/bash

# Variables
infile="infile.txt"
outfile="outfile.txt"
cmd1="cat"
cmd2="echo "test""
cmd3="cat"

# Create infile with some content
echo "Creating infile with some content..."
echo -e "Hello World\nThis is a test file\npipex project" > $infile

# Run pipex
echo "Running pipex..."
./pipex $infile "$cmd1" "$cmd2" "$cmd3" $outfile

# Display the output
echo "Output:"
cat $outfile

# Clean up
rm -f $infile $outfile
