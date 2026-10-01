
#!/bin/bash

# Check that exactly two command-line arguments were provided.
# Argument 1: Path of the file to create
# Argument 2: String to write into the file
if [ $# -ne 2 ]
then
	echo "Error: two arguments are required"
	exit 1

fi

# Store the first argument as the file path.
writefile=$1

# Store the second argument as the string to write to the file.
writestr=$2

# Create the parent directory if it does not already exist.
# dirname extracts the directory portion of the file path.
# mkdir -p creates the directory and any missing parent directories.
mkdir -p "$(dirname "$writefile")"

# Write the specified string into the file.
# The '>' operator creates the file if it doesn't exist
# or overwrites it if it already exists.
echo "$writestr" > "$writefile"

# Check the exit status of the previous command.
# $? contains the exit status of the last executed command.
# A non-zero status indicates that the command failed.
if [ $? -ne 0 ]
then
	echo "Error: could not create file"
	exit 1

fi

