# Makefile for the PoS implementation and comparison with PoW

CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lcrypto -lssl

POS_SRC = pos_block.cpp pos_blockchain.cpp
POW_SRC = ../pow/block.cpp ../pow/blockchain.cpp
COMP_SRC = compare_pow_pos.cpp

TARGET = compare_pow_pos

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(POS_SRC) $(POW_SRC) $(COMP_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)