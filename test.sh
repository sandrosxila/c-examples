#!/bin/bash

# Check if an argument (filename prefix) is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <filename_prefix>"
    exit 1
fi

# Use the provided argument as the filename prefix
FILENAME_PREFIX="$1"

# Set output directory and output file name
OUTPUT_DIR="./output"
OUTPUT_FILE="$OUTPUT_DIR/$FILENAME_PREFIX.exe"

# Create the output directory if it doesn't exist
mkdir -p $OUTPUT_DIR

# Compile the C files with the provided filename prefix
gcc "$FILENAME_PREFIX.c" "$FILENAME_PREFIX.h" "${FILENAME_PREFIX}_test.c" -o $OUTPUT_FILE

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Running program..."
    # Run the executable
    $OUTPUT_FILE
else
    echo "Compilation failed."
fi
