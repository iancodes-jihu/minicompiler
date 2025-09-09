#!/bin/bash
set -e

BIN_DIR=bin
TEST_DIR=tests

COMPILER=$BIN_DIR/compiler
VM=$BIN_DIR/vm

make > /dev/null

echo "Running test...."

for src in $TEST_DIR/*.src; do
    name=$(basename "$src" .src)
    expected="$TEST_DIR/$name.out" # in which i fogot to add '$' sign
    bytecode="$TEST_DIR/$name.bc" # fixing typo here

    $COMPILER "$src" "$bytecode"

    output=$($VM "$bytecode")

    if diff -q <(echo "$output") "$expected" > /dev/null; then # fixing typo on expected that make the code think im trying to run a file called expected
        echo "[PASS] $name"
    else
        echo "[FAIL] $name"
        echo "$Expected:" #the typo's are here again
        cat "$expected"
        echo "Got: "
        echo "$output"
        exit 1
    fi
done

echo "All test passed!"


