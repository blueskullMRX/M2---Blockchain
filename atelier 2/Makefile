CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2

SOURCES = automate_cellulaire.cpp hash.cpp merkle_tree.cpp block.cpp blockchain.cpp main.cpp
HEADERS = automate_cellulaire.h hash.h merkle_tree.h block.h blockchain.h transaction.h

COMPARISON_SOURCES = simple_comparison.cpp automate_cellulaire.cpp hash.cpp
COMPARISON_TARGET = simple_comparison

TARGET = minichain_ac

.PHONY: all clean run test comparison

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

$(COMPARISON_TARGET): $(COMPARISON_SOURCES)
	$(CXX) $(CXXFLAGS) $(COMPARISON_SOURCES) -o $@ -lssl -lcrypto

run: $(TARGET)
	./$(TARGET)

test: $(COMPARISON_TARGET)
	./$(COMPARISON_TARGET)

comparison: test

clean:
	rm -f $(TARGET) $(TARGET).exe $(COMPARISON_TARGET) $(COMPARISON_TARGET).exe *.o
