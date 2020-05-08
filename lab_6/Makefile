CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

check-xor:$(BUILD_PATH) $(BUILD_PATH)check-xor
$(BUILD_PATH)check-xor:$(SRC_PATH)check-xor.c
	@$(CC) -o $@ $(SRC_PATH)check-xor.c -I $(SRCS_HEDR)

check_fletcher:$(BUILD_PATH) $(BUILD_PATH)check_fletcher
$(BUILD_PATH)check_fletcher:$(SRC_PATH)check_fletcher.c
	@$(CC) -o $@ $(SRC_PATH)check_fletcher.c -I $(SRCS_HEDR)

crc:$(BUILD_PATH) $(BUILD_PATH)crc
$(BUILD_PATH)crc:$(SRC_PATH)crc.c
	@$(CC) -o $@ $(SRC_PATH)crc.c -I $(SRCS_HEDR)

check_csum:$(BUILD_PATH) $(BUILD_PATH)check_csum
$(BUILD_PATH)check_csum:$(SRC_PATH)check_csum.c
	@$(CC) -o $@ $(SRC_PATH)check_csum.c -I $(SRCS_HEDR)

create_csum:$(BUILD_PATH) $(BUILD_PATH)create_csum
$(BUILD_PATH)create_csum:$(SRC_PATH)create_csum.c
	@$(CC) -o $@ $(SRC_PATH)create_csum.c -I $(SRCS_HEDR)

speed_test:$(BUILD_PATH) $(BUILD_PATH)speed_test
$(BUILD_PATH)speed_test:$(SRC_PATH)speed_test.c
	@$(CC) -o $@ $(SRC_PATH)speed_test.c -I $(SRCS_HEDR)

$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
