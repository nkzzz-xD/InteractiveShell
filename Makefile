SRC_DIR = src
BIN_DIR = bin
COMPILER = gcc
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(DFLAG) $(GFLAGS) -c
LFLAGS = $(DFLAG) $(GFLAGS)
TARGET = interactiveshell
TARGET_PATH = $(BIN_DIR)/$(TARGET)

# Default rule
all: $(TARGET_PATH)

$(TARGET_PATH): $(SRC_DIR)/main.c $(SRC_DIR)/colours.h | $(BIN_DIR)
	@$(COMPILER) $(COMPILER_FLAGS) $< -o $@ 
# $< is first dependency and $0 is target name.

# Make sure the bin directory exists
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

run: $(TARGET_PATH)
	@$(TARGET_PATH)
# @ to prevent command being echoed to terminal

# Clean up binaries
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
