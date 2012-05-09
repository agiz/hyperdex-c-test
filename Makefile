CFLAGS := -O2 -Wall -Wextra -lhyperclient

all: test_hyperdex

test_hyperdex:

clean:
	rm -f ${OBJ} test_hyperdex
