#!/bin/bash

# Variables
PIPEX_EXEC=./pipex
INPUT_FILE=test
OUTPUT_FILE=output
EXPECTED_FILE=expected.txt

# Test function
run_test() {
    local cmd1="$1"
    local cmd2="$2"
    local input="$3"
    local expected_output="$4"

    # Prepare input file
    echo -n "$input" > "$INPUT_FILE"

    # Run pipex
    $PIPEX_EXEC "$INPUT_FILE" "$cmd1" "$cmd2" "$OUTPUT_FILE"

    # Prepare expected output
    echo -n "$expected_output" > "$EXPECTED_FILE"

    # Compare output
    if diff -q "$OUTPUT_FILE" "$EXPECTED_FILE" > /dev/null; then
        echo "Test passed: $cmd1 | $cmd2"
    else
        echo "Test failed: $cmd1 | $cmd2"
        echo "Expected:"
        cat "$EXPECTED_FILE"
        echo ""
	echo "Got:"
        cat "$OUTPUT_FILE"
    fi

    # Cleanup
}

# Tests
run_test "echo hello" "wc -c" "hello" "6"
run_test "echo hello world" "grep hello" "hello world" "hello world"
run_test "echo abc" "tr a z" "abc" "zbc"

