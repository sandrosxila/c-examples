#!/bin/bash

# Check if a required argument (filename prefix) is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <filename_prefix> [optional_files...]"
    exit 1
fi

# Use the first argument as the filename prefix
FILENAME_PREFIX="$1"
shift  # Shift arguments so optional arguments can be accessed as "$@"

# Set output directory and output file name
OUTPUT_DIR="./output"
OUTPUT_FILE="$OUTPUT_DIR/$FILENAME_PREFIX.exe"

# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

# Collect all files for compilation
FILES="$FILENAME_PREFIX.c $FILENAME_PREFIX.h ${FILENAME_PREFIX}_test.c"
for OPTIONAL_FILE in "$@"; do
    FILES+=" $OPTIONAL_FILE.c $OPTIONAL_FILE.h"
done

# Compile the collected files
gcc $FILES -o "$OUTPUT_FILE"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Running program..."
    # Run the executable
    "$OUTPUT_FILE"
else
    echo "Compilation failed."
fi
