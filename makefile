CPPC = g++ -std=c++11

INC_DIR = inc
DAT_DIR = dat
SRC_DIR = src
BIN_DIR = bin

build: main
	$(CPPC) $(BIN_DIR)/main.o -o hmm.out

main: $(SRC_DIR)/main.cpp $(INC_DIR)/hmm.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/main.cpp -I$(INC_DIR) -o $(BIN_DIR)/main.o

$(BIN_DIR):
	mkdir $(BIN_DIR)

clear:
	rm -rf $(BIN_DIR)