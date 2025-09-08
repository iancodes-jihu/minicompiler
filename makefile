CC = gcc
CFLAGS = -Wall -Wextra -o2

SRC_DIR = src
BIN_DIR = BIN_DIR

VM_SRC = $(SRC_DIR)/vm.c
COMPILER_SRC = $(SRC_DIR)/compiler.c

VM_BIN = $(BIN_DIR)/vm
COMPILER_BIN = $(BIN_DIR)/compiler

.PHONY: all clean dirs

all: dirs $(VM_BIN) $(COMPILER_BIN)

dirs:
	mkdir -p $(BIN_DIR)

$(VM_BIN): $(VM_SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(COMPILER_BIN) : $(COMPILER_SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:

	rm -rf $(BIN_DIR)