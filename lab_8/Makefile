CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

all: server client

server:$(BUILD_PATH) $(BUILD_PATH)server
$(BUILD_PATH)server:$(SRC_PATH)server.c
	@$(CC) -o $@ $(SRC_PATH)server.c -I $(SRCS_HEDR)

client:$(BUILD_PATH) $(BUILD_PATH)client
$(BUILD_PATH)client:$(SRC_PATH)client.c
	@$(CC) -o $@ $(SRC_PATH)client.c -I $(SRCS_HEDR)


$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
