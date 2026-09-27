.POSIX:
.SUFFIXES: .c .o

CC ?= cc
AR ?= ar

CFLAGS ?= -Wall -Wextra -ggdb3 -std=c89 -pedantic
LDFLAGS ?=

EXE=test
TEST_SRC = src/test/test.c
TEST_OBJ = $(TEST_SRC:.c=.o)

LIB=wba.a
LIB_SRC = src/wba_pool.c
LIB_OBJ = $(LIB_SRC:.c=.o)

all: $(EXE)

$(EXE): $(TEST_OBJ) $(LIB)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIB): $(LIB_OBJ)
	$(AR) rcs $@ $^

.c.o:
	$(CC) $(CFLAGS) -Iinclude -o $@ -c $<

clean:
	rm -rf $(EXE) $(LIB) $(TEST_OBJ) $(LIB_OBJ)
