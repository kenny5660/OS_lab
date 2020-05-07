CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

simplewrite:$(BUILD_PATH) $(BUILD_PATH)simplewrite
$(BUILD_PATH)simplewrite:$(SRC_PATH)simplewrite.c
	@$(CC) -o $@ $(SRC_PATH)simplewrite.c -I $(SRCS_HEDR)

onebytewrite:$(BUILD_PATH) $(BUILD_PATH)onebytewrite
$(BUILD_PATH)onebytewrite:$(SRC_PATH)onebytewrite.c
	@$(CC) -o $@ $(SRC_PATH)onebytewrite.c -I $(SRCS_HEDR)

mytail:$(BUILD_PATH) $(BUILD_PATH)mytail
$(BUILD_PATH)mytail:$(SRC_PATH)mytail.c
	@$(CC) -o $@ $(SRC_PATH)mytail.c -I $(SRCS_HEDR)

mystat:$(BUILD_PATH) $(BUILD_PATH)mystat
$(BUILD_PATH)mystat:$(SRC_PATH)mystat.c
	@$(CC) -o $@ $(SRC_PATH)mystat.c -I $(SRCS_HEDR)

myls:$(BUILD_PATH) $(BUILD_PATH)myls
$(BUILD_PATH)myls:$(SRC_PATH)myls.c
	@$(CC) -o $@ $(SRC_PATH)myls.c -I $(SRCS_HEDR)

alltree:$(BUILD_PATH) $(BUILD_PATH)alltree
$(BUILD_PATH)alltree:$(SRC_PATH)alltree.c
	@$(CC) -o $@ $(SRC_PATH)alltree.c -I $(SRCS_HEDR)


$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
