CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

fork_test:$(BUILD_PATH) $(BUILD_PATH)memory-user 

$(BUILD_PATH)memory-user:$(SRC_PATH)memory-user.c
	@$(CC) -o $@ $(SRC_PATH)memory-user.c -I $(SRCS_HEDR)

$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
