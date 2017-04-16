CC := gcc
AR := ar
BUILD_DIR := build
CHALLENGES_DIRS := $(shell find ./ -maxdepth 1 -type d -name "challenge*")
VENDOR_DIR := vendor
LIBS_DIR := libs

UNITY_DIR := Unity
UNITY_GIT := https://github.com/ThrowTheSwitch/Unity.git
UNITY_PATH := $(VENDOR_DIR)/$(UNITY_DIR)
UNITY_LIB := libunity.a
UNITY_SRC_DIRS := $(UNITY_PATH)/src $(UNITY_PATH)/extras/fixture
UNITY_SRC = $(shell find $(UNITY_SRC_DIRS) -type f -name "*.c")
UNITY_OBJ = $(patsubst %.c,%.o, $(UNITY_SRC))
UNITY_OBJ_PATHS = $(addprefix $(BUILD_DIR)/, $(UNITY_OBJ))
UNITY_INCLUDE := $(UNITY_SRC_DIRS)

CFLAGS_BASE := -Wall
AR_FLAGS := rcs

UNITY_DIR_EXISTS=$(shell [ -e $(UNITY_PATH) ] && echo 1 || echo 0 )

all: post-build

pre-build:
	mkdir -p $(LIBS_DIR)

main-build: pre-build
	for dir in $(CHALLENGES_DIRS) ; do \
		cd $$dir && $(MAKE) ; \
	done

post-build: main-build

build-libs: build-unity-lib
	-rm -rf $(BUILD_DIR)

build-unity-lib: $(UNITY_OBJ) pre-build
	$(AR) $(AR_FLAGS) $(LIBS_DIR)/$(UNITY_LIB) $(UNITY_OBJ_PATHS)

build-dirs:
	mkdir -p $(LIBS_DIR)
	mkdir -p $(VENDOR_DIR)
	mkdir -p $(BUILD_DIR)


$(UNITY_PATH)/%.o: CFLAGS := $(CFLAGS_BASE) -I $(UNITY_INCLUDE)
$(UNITY_PATH)/%.o: $(UNITY_PATH)/%.c 
	mkdir -p $(BUILD_DIR)/$(dir $@)
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@


.PHONY: clean purge cleanbuild purgebuild

clean:
	for dir in $(CHALLENGES_DIRS) ; do \
		cd $$dir && $(MAKE) clean ; \
	done
	-rm -rf $(BUILD_DIR)

purge: clean
	-rm -rf $(LIBS_DIR)

cleanbuild: clean
	$(MAKE) all

purgebuild: purge
	$(MAKE) all
