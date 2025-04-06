CC := g++
CFLAGS := -Iinclude -std=c++17 #-Wall -Wextra 
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := test
BIN := app

SRCS := $(wildcard $(SRC_DIR)/*.cc) 
OBJS := $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%.cc,$(SRCS))) \

MAIN_OBJ := $(OBJ_DIR)/app.o

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

	
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: clean
