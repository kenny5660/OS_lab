CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

invcase:$(BUILD_PATH) $(BUILD_PATH)invcase
$(BUILD_PATH)invcase:$(SRC_PATH)invcase.c
	@$(CC) -o $@ $(SRC_PATH)invcase.c -I $(SRCS_HEDR)


$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
