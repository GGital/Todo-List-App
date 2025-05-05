# Compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -IC:\SFML-2.6.2\include -DSFML_STATIC

# SFML static libraries and required dependencies
LDFLAGS := -LC:\SFML-2.6.2\lib \
           -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s \
		   -lfreetype -lopengl32 -lwinmm -lgdi32

# Directories
SRC_DIR := src
BUILD_DIR := build
P_DIR := -p

# Find all .cpp files using wildcard (Windows-compatible)
SOURCES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)

# Convert .cpp filenames into corresponding .o object file paths in build/
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Output binary name
TARGET := app

# Default target
all: $(TARGET)

# Link all object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile .cpp files into .o object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean build files
clean:
	@if exist $(BUILD_DIR) ( rmdir /s /q $(BUILD_DIR) ) || rm -rf $(BUILD_DIR)
	@if exist $(P_DIR) ( rmdir /s /q $(P_DIR) ) || rm -rf $(P_DIR)
	@if exist $(TARGET).exe ( del /f /q $(TARGET).exe ) || rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
