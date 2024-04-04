BIN_DIR=bin

$(BIN_DIR)/main: $(BIN_DIR)/main.o $(BIN_DIR)/life.o
	mkdir -p $(BIN_DIR)
	cc $^ -o $@ -g

$(BIN_DIR)/main.o: src/main.c
	mkdir -p $(BIN_DIR)
	cc -c $< -o $@

$(BIN_DIR)/life.o: src/life.c
	mkdir -p $(BIN_DIR)
	cc -c $< -o $@

clean:
	rm -rf *.o main

.PHONY: clean