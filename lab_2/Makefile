CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/

SRCS_HEDR=src/

fork_test:$(BUILD_PATH)fork_test

$(BUILD_PATH)fork_test:$(SRC_PATH)fork_test.c
	@$(CC) -o $@ $(SRC_PATH)fork_test.c -I $(SRCS_HEDR)


fork_exec:$(BUILD_PATH)fork_exec

$(BUILD_PATH)fork_exec:$(SRC_PATH)fork_exec.c
	@$(CC) -o $@ $(SRC_PATH)fork_exec.c -I $(SRCS_HEDR)

fork_before:$(BUILD_PATH)fork_before

$(BUILD_PATH)fork_before:$(SRC_PATH)fork_before.c
	@$(CC) -o $@ $(SRC_PATH)fork_before.c -I $(SRCS_HEDR)

fork_stdout:$(BUILD_PATH)fork_stdout

$(BUILD_PATH)fork_stdout:$(SRC_PATH)fork_stdout.c
	@$(CC) -o $@ $(SRC_PATH)fork_stdout.c -I $(SRCS_HEDR)

fork_pipe:$(BUILD_PATH)fork_pipe

$(BUILD_PATH)fork_pipe:$(SRC_PATH)fork_pipe.c
	@$(CC) -o $@ $(SRC_PATH)fork_pipe.c -I $(SRCS_HEDR)



$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
