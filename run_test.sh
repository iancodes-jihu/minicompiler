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
    expected="TEST_DIR/$name.out"
    bytecode="TEST_DIR/$name.bc"

    $COMPILER "$src" "$bytecode"

    output=$($VM "$bytecode")

    if diff -q <(echo "$output") "expected" > /dev/null; then
        echo "[PASS] $name"
    else
        echo "[FAIL] $name"
        echo "Expected:"
        cat "$expected"
        echo "Got: "
        echo "$output"
        exit 1
    fi
done

echo "All test passed!"


