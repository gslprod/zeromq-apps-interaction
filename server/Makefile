OUT = time_server
SRC = src/time_server.c
ZEROMQ = libs/zeromq
STDCPP = libs/stdc++

CC = gcc
CFLAGS = -Wall -g -I$(ZEROMQ)/include
LDFLAGS = $(ZEROMQ)/src/.libs/libzmq.a $(STDCPP)/.libs/libstdc++.a

.PHONY: all build run clean

all: build

build: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

run:
	./$(OUT)

clean:
	rm -f $(OUT)