CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lcrypto -lssl

MERKLE_DIR = ../merkle
MERKLE_SRC = $(MERKLE_DIR)/merkle_tree.cpp

SOURCES = block.cpp blockchain.cpp main.cpp $(MERKLE_SRC)
HEADERS = block.h blockchain.h transaction.h

TARGET = minichain

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o