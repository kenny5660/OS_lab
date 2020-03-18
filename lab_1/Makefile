CC=gcc
CCFLAGS=-Wall -Wextra -pedantic
EXE=app

SRCS_HEDR=src/
SRCS_GLOB=src/*.c
SRCS=$(wildcard $(SRCS_GLOB))
OBJS=$(SRCS:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJS)
	@$(CC) -o $@ $(OBJS) -I $(SRCS_HEDR)

depend: .depend

.depend: $(SRCS)
	@-rm -f ./.depend
	@$(CC) $(CCFLAGS) -MM $^>>./.depend

clean:
	-rm -f $(EXE)
	-rm $(OBJS)
	-rm *~
	-rm .depend

include .depend