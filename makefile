CPPC = g++ -std=c++11

INC_DIR = 'inc'
DAT_DIR = 'dat'
SRC_DIR = 'src'
BIN_DIR = 'bin'

build: main
	$(CPPC) $(BIN_DIR)/main.o -o hmm.out

main: $(SRC_DIC)/main.cpp $(INC_DIR)/hmm.h
	$(CPPC) -c $(SRC_DIC)/main.cpp -I$(INC_DIR) -o $(BIN_DIR)/main.o

clear:
	rm -rf $(BIN_DIR)