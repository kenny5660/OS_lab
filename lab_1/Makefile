CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
BUILD_PATH=./build/
SRC_PATH=src/
EXE=$(BUILD_PATH)app

SRCS_HEDR=src/

SRCS_GLOB=$(SRC_PATH)*.c
SRCS=$(wildcard $(SRCS_GLOB))
OBJS=$(patsubst $(SRCS_HEDR)%,$(BUILD_PATH)%,$(patsubst %.c,%.o,$(SRCS)))

all: $(EXE)

$(EXE):$(BUILD_PATH) $(OBJS)
#	echo $(OBJS)
	@$(CC) -o $@ $(OBJS) -I $(SRCS_HEDR)

$(BUILD_PATH)%.o: $(SRCS_HEDR)%.c 
	@$(CC) -c -o $@ -I $(SRCS_HEDR) $^

$(BUILD_PATH):
	mkdir $(BUILD_PATH)
clean:
	-rm -f build/*
