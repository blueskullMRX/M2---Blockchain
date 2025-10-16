# Blockchain Consensus Algorithms Comparison

This repository contains implementations of Merkle Trees, Proof of Work (PoW), and Proof of Stake (PoS) consensus algorithms in C++.

## Project Structure

- **merkle/**: Implementation of a basic Merkle Tree
- **pow/**: Implementation of Proof of Work consensus algorithm
- **pos/**: Implementation of Proof of Stake consensus algorithm and comparison tools

## Compilation Instructions

### Merkle Tree

```bash
cd merkle
g++ -std=c++11 merkle_tree.cpp test_merkle_tree.cpp -o test_merkle -lcrypto -lssl
./test_merkle
```

### Proof of Work

```bash
cd pow
make
./test_pow
```

### Proof of Stake and Comparison

```bash
cd pos
make
./compare_pow_pos
```

## Performance Comparison Results

The performance comparison between PoW and PoS shows significant differences in execution time:

### With PoW Difficulty = 4:
- PoW Total Time: ~675 ms (135 ms per block)
- PoS Total Time: ~4 ms (0.8 ms per block)
- PoS is approximately 169 times faster than PoW

### With PoW Difficulty = 5:
- PoW Total Time: ~14,292 ms (2,858 ms per block)
- PoS Total Time: ~2 ms (0.4 ms per block)
- PoS is approximately 7,146 times faster than PoW

## Key Observations

1. **Scalability**: PoW difficulty scaling is exponential - increasing difficulty from 4 to 5 increased mining time by more than 20 times.

2. **Energy Efficiency**: PoS is significantly more energy-efficient as it doesn't require the computational work of PoW.

3. **Validator Selection**: PoS selects validators based on their stake in the system, which is proportional to their wealth in the cryptocurrency.

4. **Latency**: PoS produces blocks much faster, leading to lower confirmation times for transactions.

## Implementation Notes

- Both implementations use SHA-256 for cryptographic hashing.
- The PoS implementation uses a weighted random selection based on stake amounts.
- The PoW implementation allows configurable difficulty levels.
- Performance tests were conducted on the same machine for fair comparison.

## Dependencies

- C++11 compatible compiler
- OpenSSL library for SHA-256 hashing

## Known Issues

- OpenSSL 3.0 deprecation warnings (these don't affect functionality)