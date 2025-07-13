REBAR=rebar3

.PHONY: all build run clean

all: build

build:
	$(REBAR) get-deps
	$(REBAR) compile

run: build
	$(REBAR) shell

clean:
	$(REBAR) clean