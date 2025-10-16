# Makefile for blockchain PoW implementation

CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lcrypto -lssl

TARGET = test_pow
SOURCES = block.cpp blockchain.cpp test_pow.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)