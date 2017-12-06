CPPC = g++ -std=c++11

INC_DIR = inc
DAT_DIR = dat
SRC_DIR = src
BIN_DIR = bin

build: main dictionary
	$(CPPC) $(BIN_DIR)/main.o $(BIN_DIR)/dictionary.o -o hmm.out

dictionary: $(SRC_DIR)/dictionary.cpp $(INC_DIR)/dictionary.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/dictionary.cpp -I$(INC_DIR) -o $(BIN_DIR)/dictionary.o

main: $(SRC_DIR)/main.cpp $(INC_DIR)/hmm.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/main.cpp -I$(INC_DIR) -o $(BIN_DIR)/main.o

$(BIN_DIR):
	mkdir $(BIN_DIR)

clear:
	rm -rf $(BIN_DIR)