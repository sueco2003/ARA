# Makefile for ARA project

# Compiler
CC = gcc

# Compiler flags
#CFLAGS = -g -Ofast -march=native -funroll-loops -flto -fprefetch-loop-arrays
CFLAGS = -g -Wall -Wextra -O0
# Output executable name
TARGET = ara

# Source files (find all .c files)
SRCS = $(wildcard *.c)

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Header files (for dependency generation)
HDRS = $(wildcard *.h)

# Default target to build the project
all: $(TARGET)

# Rule to link object files and create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to clean and rebuild the project
rebuild: clean all

# Phony targets to avoid collision with files named 'all', 'clean', etc.
.PHONY: all clean rebuild