CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O0

# Target binary
TARGET = build/main

# Source file
SRC = main.c

# Default target
all: $(TARGET)

# Rule to build the binary
$(TARGET): $(SRC) | build
	$(CC) $(CFLAGS) -o $@ $<

# Ensure build directory exists
build:
	mkdir -p build

# Clean up
clean:
	rm -rf build
