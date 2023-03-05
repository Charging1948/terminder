CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# List all source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generate a list of object files to build
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Build the executable
$(BIN_DIR)/terminder: $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create bin directory
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up object files and executable
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/terminder
	rmdir $(OBJ_DIR) $(BIN_DIR) 2>/dev/null || true