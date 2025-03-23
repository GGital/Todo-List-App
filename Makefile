# Compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

# Directories
SRC_DIR := src
BUILD_DIR := build

# Find all .cpp files using wildcard (Works in Windows)
SOURCES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

# Convert .cpp filenames into corresponding .o object file paths in build/
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Output binary name
TARGET := app

# Default target
all: $(TARGET)

# Link all object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile .cpp files into .o object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets to avoid conflicts with files named 'all', 'clean', etc.
.PHONY: all clean run
