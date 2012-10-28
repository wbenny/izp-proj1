# Staci upravit... :)
EXE     = proj1

#####################
CC      = gcc
CFLAGS  = -c -std=c99 -pedantic -Wall -Wextra
LDFLAGS = 
SRCS    = $(wildcard *.c)
OBJS    = $(patsubst %.c,%.o,$(SRCS))

all: $(SOURCES) $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(EXE) xbenes35-fit.tar.gz

tarball:
	tar -zcvf xbenes35-fit.tar.gz *
