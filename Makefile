CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Iinclude
SRC_DIR = src
BIN_DIR = bin

# List all source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generate a list of object files to build
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Build the executable
$(BIN_DIR)/my_program: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build object files from source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/terminder
