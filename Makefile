CC := g++
CFLAGS := -Iinclude -std=c++17
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

APP_BIN := $(BIN_DIR)/app
SERVER_BIN := $(BIN_DIR)/server_handler
CLIENT_BIN := $(BIN_DIR)/client_handler

SRCS := $(wildcard $(SRC_DIR)/*.cc)
COMMON_SRCS := $(filter-out $(SRC_DIR)/app.cc $(SRC_DIR)/server_handler.cc $(SRC_DIR)/client_handler.cc, $(SRCS))

COMMON_OBJS := $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(COMMON_SRCS))
APP_OBJ := $(OBJ_DIR)/app.o
SERVER_OBJ := $(OBJ_DIR)/server_handler.o
CLIENT_OBJ := $(OBJ_DIR)/client_handler.o

all: $(APP_BIN) $(SERVER_BIN) $(CLIENT_BIN)

$(APP_BIN): $(COMMON_OBJS) $(APP_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER_BIN): $(COMMON_OBJS) $(SERVER_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_BIN): $(COMMON_OBJS) $(CLIENT_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean all
