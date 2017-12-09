CPPC = g++ -std=c++11

INC_DIR = inc
DAT_DIR = dat
SRC_DIR = src
BIN_DIR = bin

build: main dictionary unigram bigram mfcc cell machine
	$(CPPC) $(BIN_DIR)/main.o $(BIN_DIR)/machine.o $(BIN_DIR)/cell.o $(BIN_DIR)/mfcc.o $(BIN_DIR)/bigram.o $(BIN_DIR)/unigram.o $(BIN_DIR)/dictionary.o -o hmm.out

machine: $(SRC_DIR)/machine.cpp $(INC_DIR)/machine.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/machine.cpp -I$(INC_DIR) -o $(BIN_DIR)/machine.o

cell: $(SRC_DIR)/cell.cpp $(INC_DIR)/cell.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/cell.cpp -I$(INC_DIR) -o $(BIN_DIR)/cell.o

mfcc: $(SRC_DIR)/mfcc.cpp $(INC_DIR)/mfcc.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/mfcc.cpp -I$(INC_DIR) -o $(BIN_DIR)/mfcc.o

bigram: $(SRC_DIR)/bigram.cpp $(INC_DIR)/bigram.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/bigram.cpp -I$(INC_DIR) -o $(BIN_DIR)/bigram.o

unigram: $(SRC_DIR)/unigram.cpp $(INC_DIR)/unigram.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/unigram.cpp -I$(INC_DIR) -o $(BIN_DIR)/unigram.o

dictionary: $(SRC_DIR)/dictionary.cpp $(INC_DIR)/dictionary.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/dictionary.cpp -I$(INC_DIR) -o $(BIN_DIR)/dictionary.o

main: $(SRC_DIR)/main.cpp $(INC_DIR)/hmm.h $(BIN_DIR)
	$(CPPC) -c $(SRC_DIR)/main.cpp -I$(INC_DIR) -o $(BIN_DIR)/main.o

$(BIN_DIR):
	mkdir $(BIN_DIR)

clear:
	rm -rf $(BIN_DIR)