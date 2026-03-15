# Makefile for Unix System Monitor

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = monitor
SOURCE = src/main.c
OBJ = src/main.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(TARGET)

# Install to system (requires root)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Uninstall from system
uninstall:
	rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean install uninstall