.POSIX:
.PHONY: all clean

CC := gcc
CFLAGS := -O2 -fPIC -Wall -Werror
LDFLAGS :=

all: daysy libdaysy.a libdaysy.so

clean:
	rm -f *.o daysy libdaysy.a libdaysy.so

daysy: main.o libdaysy.a
	$(CC) $(LDFLAGS) -o $@ $^

libdaysy.a: daysy.o
	ar rcs $@ $<

libdaysy.so: daysy.o
	$(CC) $(LDFLAGS) -shared -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<
