# Mini Blockchain Implementation

This is a complete mini-blockchain implementation that integrates the components from previous exercises:
- Merkle Trees for transaction aggregation (Exercise 1)
- Proof of Work consensus (Exercise 2)
- Proof of Stake consensus (Exercise 3)

## Features

- **Transaction Management**: Create and verify transactions with sender, receiver, and amount
- **Merkle Tree Integration**: Generate Merkle roots for transaction sets in each block
- **Flexible Consensus**: Support for both PoW and PoS consensus mechanisms
- **Performance Comparison**: Tools to measure and compare PoW vs PoS performance
- **Blockchain Integrity**: Verification of blockchain validity

## Components

### Transaction Class
- Represents a single transaction with ID, sender, receiver, and amount
- Provides methods to convert to string representation for hashing

### Block Class
- Stores block metadata, transactions, and hash
- Calculates Merkle root from transactions
- Supports both mining (PoW) and validation (PoS)
- Provides timing measurements for block processing

### Blockchain Class
- Manages the chain of blocks
- Handles consensus algorithm selection (PoW or PoS)
- Manages stakeholders for PoS consensus
- Verifies blockchain integrity

## Performance Results

Our tests show that Proof of Stake is significantly faster than Proof of Work:

- With PoW difficulty 3, PoW requires ~33ms per block while PoS processes blocks nearly instantly
- With PoW difficulty 4, PoW requires ~200ms per block while PoS still processes blocks nearly instantly

The difference becomes even more pronounced as difficulty increases or as the number of transactions grows.

## Compilation Instructions

```bash
# Compile the minichain program
g++ -std=c++11 block.cpp blockchain.cpp ../merkle/merkle_tree.cpp main.cpp -o minichain -lcrypto -lssl

# Run the program
./minichain
```

## Dependencies

- C++11 compatible compiler
- OpenSSL library for SHA-256 hashing