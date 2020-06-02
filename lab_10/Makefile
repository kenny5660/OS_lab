CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

hard_link_test:$(BUILD_PATH) $(BUILD_PATH)hard_link_test
$(BUILD_PATH)hard_link_test:$(SRC_PATH)hard_link_test.c
	@$(CC) -o $@ $(SRC_PATH)hard_link_test.c -I $(SRCS_HEDR)


$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
