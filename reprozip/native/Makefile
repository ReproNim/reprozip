CC = cc
AR = ar
CFLAGS = -g -O2 -Wall
LDFLAGS = -L/usr/lib/x86_64-linux-gnu
LDLIBS = -lsqlite3 -ldl -lreadline -lm

rztracer: rztracer.c libtracer.a
	$(CC) $(CFLAGS) -o $@ $^ -static $(LDFLAGS) $(LDLIBS) -pthread

libtracer.a: log.o utils.o tracer.o database.o syscalls.o ptrace_utils.o
	$(AR) cr $@ $^

.PHONY: clean
clean:
	$(RM) *.o *.a rztracer
