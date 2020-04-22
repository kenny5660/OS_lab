CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

aspace:$(BUILD_PATH) $(BUILD_PATH)aspace
$(BUILD_PATH)aspace:$(SRC_PATH)aspace.c
	@$(CC) -o $@ $(SRC_PATH)aspace.c -I $(SRCS_HEDR)

null:$(BUILD_PATH) $(BUILD_PATH)null
$(BUILD_PATH)null:$(SRC_PATH)null.c
	@$(CC) -o $@ $(SRC_PATH)null.c -g -I $(SRCS_HEDR)

bad_malloc:$(BUILD_PATH) $(BUILD_PATH)bad_malloc
$(BUILD_PATH)bad_malloc:$(SRC_PATH)bad_malloc.c
	@$(CC) -o $@ $(SRC_PATH)bad_malloc.c -g -I $(SRCS_HEDR)

data:$(BUILD_PATH) $(BUILD_PATH)data
$(BUILD_PATH)data:$(SRC_PATH)data.c
	@$(CC) -o $@ $(SRC_PATH)data.c -g -I $(SRCS_HEDR)

data_free:$(BUILD_PATH) $(BUILD_PATH)data_free
$(BUILD_PATH)data_free:$(SRC_PATH)data_free.c
	@$(CC) -o $@ $(SRC_PATH)data_free.c -g -I $(SRCS_HEDR)

$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
