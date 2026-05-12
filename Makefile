CXX = g++
CC = gcc

CXXFLAGS = -std=c++20 -Wall -Wextra
CFLAGS = -Wall -Wextra

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Include paths
INCLUDES = -I$(INCLUDE_DIR) \
           -I$(INCLUDE_DIR)/glm-master \
           -I/opt/homebrew/include/SDL2

# Libraries
LIBS = -L/opt/homebrew/lib -lSDL2

# Source files
CPP_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
C_SRCS   = $(wildcard $(SRC_DIR)/*.c)

# Object files
CPP_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
C_OBJS   = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))

OBJS = $(CPP_OBJS) $(C_OBJS)

# Output executable
TARGET = $(BUILD_DIR)/main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $(TARGET)

# Compile C++ files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(TARGET)

.PHONY: all clean run
