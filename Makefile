SRC_DIR := src/
INCLUDE_DIR := include/

OUT_DIR := build

CC=gcc

TARGET=main

all: clean compile run

clean:
	rm -rf $(OUT_DIR)/*

compile:
	@mkdir -p $(OUT_DIR)
	$(CC) $$(find ./src -name "*.c") -I$(INCLUDE_DIR) -o $(OUT_DIR)/$(TARGET)

run:
	$(OUT_DIR)/$(TARGET)
	@$(OUT_DIR)/$(TARGET)
