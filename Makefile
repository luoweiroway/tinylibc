CC = gcc
AR = ar
LD = ld
ARCH = x86-64

TINY_LIB_SRC = $(sort $(wildcard stdio/*.c string/*.c))
TINY_LIB_OBJS = $(TINY_LIB_SRC:%.c=%.o)
ENTRY_OBJ = _start/start.o
STATIC_LIBS = tinylibc.a

CFLAGS = -fno-builtin -nostdlib
CFLAGS += -I./include -I./arch/$(ARCH)
ARFLAGS = -rs

TEST_SRC = example/test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_LD_OBJS = $(ENTRY_OBJ) $(TEST_OBJ) $(STATIC_LIBS)
TEST_CFLAGS = -ggdb -fno-builtin -nostdlib
TEST_CFLAGS += -I./include -I./arch/$(ARCH)
TEST_LDFLAGS = -static
TEST_LD_ENTRY_FLAGS = -e tinylibc_start

ifeq ($(SHOW),)
hide := @
else
hide :=
endif

all: $(STATIC_LIBS) test

test: $(TEST_LD_OBJS)
	$(hide) $(LD) $(TEST_LDFLAGS) $(TEST_LD_ENTRY_FLAGS) $^ -o $@

$(TEST_OBJ): $(TEST_SRC)
	$(hide) $(CC) -c $(TEST_CFLAGS) -o $@ $<

lib: $(STATIC_LIBS)

$(STATIC_LIBS): $(TINY_LIB_OBJS)
ifeq ($(SHOW),)
	$(hide) $(AR) $(ARFLAGS) $@ $^ >/dev/null 2>&1
else
	$(hide) $(AR) $(ARFLAGS) $@ $^
endif

%.o : %.c
	$(hide) $(CC) -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	$(hide) find -type f 	\
		\( -name '*.o' -o 	\
		-name '*.a' -o      \
		-name 'test' \)|xargs rm -f

help:
	@echo "Usage:"
	@echo "	help 			: show help messages"
	@echo "	all  			: build tinylibc.a and test"
	@echo "	lib  			: only build tinylibc.a"
	@echo "	test 			: build test examples"
	@echo "	clean			: clean all object files"
	@echo "	make SHOW=1 [target]	: print out all build commands, ex: make SHOW=1 lib"

