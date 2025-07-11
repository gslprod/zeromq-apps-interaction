CLIENT_DIR=client
SERVER_DIR=server

.PHONY: all build run-server run-client clean

all: build

build:
	$(MAKE) -C $(SERVER_DIR)
	$(MAKE) -C $(CLIENT_DIR)

run-server:
	$(MAKE) -C $(SERVER_DIR) run

run-client:
	$(MAKE) -C $(CLIENT_DIR) run

clean:
	$(MAKE) -C $(SERVER_DIR) clean
	$(MAKE) -C $(CLIENT_DIR) clean