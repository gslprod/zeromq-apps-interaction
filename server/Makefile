OUT = time_server
SRC = src/time_server.c
ZEROMQ = libs/zeromq

CC = gcc
CFLAGS = -Wall -g -I./$(ZEROMQ)/include
LDFLAGS = -L./$(ZEROMQ)/.libs -lzmq

.PHONY: all build run clean

all: build

build: $(OUT)

$(OUT): $(SRC)
	cd $(ZEROMQ) && make
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

run:
	./$(OUT)

clean:
	rm -f $(OUT)
	cd $(ZEROMQ) && make clean