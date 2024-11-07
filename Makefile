# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fno-omit-frame-pointer -g -I./src

# Directories
SRC_DIR = src
APP_DIR = app
BUILD_DIR = build
BUILD_APP_DIR = $(BUILD_DIR)/app

# Source files
SRCS = $(SRC_DIR)/lab.c $(APP_DIR)/main.c
OBJS = $(BUILD_DIR)/lab.o $(BUILD_APP_DIR)/main.o

# Output binary
TARGET = myprogram  # Place executable in root directory

# Create necessary directories
$(BUILD_APP_DIR):
	mkdir -p $(BUILD_APP_DIR)

# Compile the object files
$(BUILD_DIR)/lab.o: $(SRC_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_APP_DIR)/main.o: $(APP_DIR)/main.c | $(BUILD_APP_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -pthread -o $(TARGET)

# Clean the build directory and remove the executable from root
clean:
	rm -rf $(BUILD_DIR) myprogram

# Run the program
run: $(TARGET)
	./$(TARGET) 1000 4  # Example arguments; adjust as needed
