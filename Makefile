SRC_DIR = src
BIN_DIR = bin
COMPILER = gcc
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(GFLAGS) $(DFLAG) -c
LFLAGS = $(GFLAGS) $(DFLAG)
TARGET = interactiveshell
TARGET_PATH = $(BIN_DIR)/$(TARGET)

# Default rule
all: $(TARGET_PATH)

$(TARGET_PATH): $(BIN_DIR)/main.o $(BIN_DIR)/processing.o $(BIN_DIR)/parsing.o $(BIN_DIR)/utils.o | $(BIN_DIR)
	$(COMPILER) $(LFLAGS) $^ -lreadline -o $@
# $< is first dependency and $0 is target name.

$(BIN_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/colours.h $(SRC_DIR)/processing.h | $(BIN_DIR)
	$(COMPILER) $(CFLAGS) $< -o $@

$(BIN_DIR)/processing.o: $(SRC_DIR)/processing.c $(SRC_DIR)/processing.h | $(BIN_DIR)
	$(COMPILER) $(CFLAGS) $< -o $@

$(BIN_DIR)/parsing.o: $(SRC_DIR)/parsing.c $(SRC_DIR)/parsing.h | $(BIN_DIR)
	$(COMPILER) $(CFLAGS) $< -o $@

$(BIN_DIR)/utils.o: $(SRC_DIR)/utils.c $(SRC_DIR)/utils.h | $(BIN_DIR)
	$(COMPILER) $(CFLAGS) $< -o $@


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
