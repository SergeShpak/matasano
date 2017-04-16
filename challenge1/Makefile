CC := gcc
INCLUDE_DIR := ./include
INCLUDE_DIR_PATH := $(realpath $(INCLUDE_DIR))
BUILD_DIR := build
BIN_DIR := bin
OUT := challenge1
OUT_PATH := $(BIN_DIR)/$(OUT)
LIBS_DIR := $(realpath ../libs)
SRC_DIR := src
SRC_WITH_DIR := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ_FILES := $(patsubst %.c,%.o, $(SRC_WITH_DIR))
OBJ_PATH := $(addprefix $(BUILD_DIR)/, $(OBJ_FILES))

TEST_DIR := tests
TESTS_SRC_DIRS := $(TEST_DIR)/tests $(TEST_DIR)/tests_runners
TEST_ROOT_SRC := $(shell find $(TEST_DIR) -maxdepth 1 -type f -name "*.c")
TEST_SRC := \
	$(shell find $(TESTS_SRC_DIRS) -type f -name "*.c") $(TEST_ROOT_SRC)
TEST_OBJ := $(patsubst %.c,%.o, $(TEST_SRC))
TEST_OBJ_PATH := $(addprefix $(BUILD_DIR)/, $(TEST_OBJ))
TEST_INCLUDE_DIR := $(TEST_DIR)/unity_include
TEST_INCLUDE_DIR_PATH := $(realpath $(TEST_INCLUDE_DIR))
TEST_OUT := tests_$(OUT)
TEST_OUT_PATH := $(BIN_DIR)/$(TEST_OUT)
SRC_NO_MAIN := $(shell find $(SRC_DIR) -not -name "main.c" -type f -name "*.c")
OBJ_FILES_NO_MAIN := $(patsubst %.c,%.o, $(SRC_NO_MAIN))
OBJ_PATH_NO_MAIN := $(addprefix $(BUILD_DIR)/, $(OBJ_FILES_NO_MAIN))
UNITY_LIB_NAME := unity

CFLAGS_BASE := -Wall -g
LINKER_FLAGS := -L$(LIBS_DIR) -l$(UNITY_LIB_NAME)

all: post-build test-build

pre-build:
	mkdir -p $(BIN_DIR)	

main-build: CFLAGS := $(CFLAGS_BASE) -I $(INCLUDE_DIR_PATH)
main-build: pre-build $(OBJ_FILES)
	$(CC) $(CFLAGS_BASE) $(OBJ_PATH) -o $(OUT_PATH)

post-build: main-build

test-build: libs pre-build $(TEST_OBJ) $(OBJ_FILES_NO_MAIN)
	$(CC) $(CFLAGS_BASE) $(TEST_OBJ_PATH) $(OBJ_PATH_NO_MAIN) \
		-o $(TEST_OUT_PATH) $(LINKER_FLAGS) 

libs:
	cd .. && $(MAKE) build-libs

$(TEST_DIR)/%.o: CFLAGS := $(CFLAGS_BASE) -I $(INCLUDE_DIR_PATH) \
	-I $(TEST_INCLUDE_DIR_PATH) -c
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(BUILD_DIR)/$(dir $@)
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

%.o: CFLAGS := $(CFLAGS_BASE) -I $(INCLUDE_DIR_PATH) -c
%.o: %.c
	mkdir -p $(BUILD_DIR)/$(dir $@)
	$(CC) $(CFLAGS) $< -o $(BUILD_DIR)/$@

.PHONY: clean cleanbuild

clean:
	-rm -rf $(BUILD_DIR)
	-rm -rf $(BIN_DIR)

cleanbuild: clean
	$(MAKE) all
