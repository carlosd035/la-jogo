CFLAGS = -Wall -Wextra -pedantic -O2
LIBS = -lm -lcurses
CC = gcc

BIN_DIR = bin
BUILD_DIR = build
INCLUDES_DIR = includes
SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

PROGRAM = play

.DEFAULT_GOAL = build

build: setup $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -I $(INCLUDES_DIR) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -I $(INCLUDES_DIR) $(CFLAGS) -o $@ $^

.PHONY: setup
setup:
	mkdir -p $(BUILD_DIR)


.PHONY: clean
clean:
	-rm -r $(BUILD_DIR)
	-rm $(PROGRAM)